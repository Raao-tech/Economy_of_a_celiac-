/**
 * @brief Engine TAD implementation
 *
 * @file        Engine.c
 * @author      Rafael
 * @version     1.1
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#include "../Headers/Engine.h"

#define EVENT_BUF_SIZE 512

struct _Engine {
    Economy*  economy;
    Patient*  patient;
    int       month;
    int       year;
    int       total_months;
    char      last_event[EVENT_BUF_SIZE];
};

/* ================================================================ */

Engine* engine_create()
{
    Engine* eng = (Engine*)malloc(sizeof(Engine));
    if (!eng) return NULL;

    eng->economy = economy_create();
    eng->patient = patient_create();

    if (!eng->economy || !eng->patient) {
        economy_destroy(eng->economy);
        patient_destroy(eng->patient);
        free(eng);
        return NULL;
    }

    eng->month = JANUARY;
    eng->year  = 2018;
    eng->total_months = 0;
    eng->last_event[0] = '\0';

    return eng;
}

Status engine_destroy(Engine* eng)
{
    if (!eng) return ERROR;
    economy_destroy(eng->economy);
    patient_destroy(eng->patient);
    free(eng);
    return OK;
}

/* ================================================================ */

Economy* engine_get_economy(Engine* eng)  { return eng ? eng->economy : NULL; }
Patient* engine_get_patient(Engine* eng)  { return eng ? eng->patient : NULL; }
int      engine_get_month(Engine* eng)    { return eng ? eng->month : ERROR_INT; }
int      engine_get_year(Engine* eng)     { return eng ? eng->year : ERROR_INT; }

const char* engine_get_last_event(Engine* eng)
{
    if (!eng) return "";
    return eng->last_event;
}

/* ================================================================
 *  Core simulation step
 *
 *  Each month has 3 phases:
 *    1. PURCHASE — player decides what to buy (or abstain)
 *    2. CONSUME  — patient eats from stock (cert first, then normal)
 *    3. ECONOMY  — inflation advances, prices update
 * ================================================================ */

Status engine_next_month(Engine* engine, PlayerAction action, int seed)
{
    Economy*  eco;
    Patient*  pat;
    double    power, price_cert, price_food;
    double    health;
    int       pos = 0;

    if (!engine) return ERROR;

    eco = engine->economy;
    pat = engine->patient;
    if (!eco || !pat) return ERROR;

    power      = patient_get_purchasing_power(pat);
    price_cert = economy_get_price_foodCert(eco);
    price_food = economy_get_price_food(eco);
    health     = patient_get_health(pat);

    /* Clear event log */
    engine->last_event[0] = '\0';

    /* ---- PHASE 1: PURCHASE (player's decision) ---- */
    switch (action) {
        case BUY_CERTIFIED:
            if (power >= price_cert) {
                patient_set_stock_foodCert(pat, patient_get_stock_foodCert(pat) + 1);
                pos += sprintf(engine->last_event + pos,
                    "[+] Compraste comida certificada (-%.2f EUR)\n", price_cert);
            } else {
                pos += sprintf(engine->last_event + pos,
                    "[!] No puedes permitirte comida certificada (%.2f > %.0f)\n",
                    price_cert, power);
            }
            break;

        case BUY_NONCERTIFIED:
            if (power >= price_food) {
                patient_set_stock_food(pat, patient_get_stock_food(pat) + 1);
                pos += sprintf(engine->last_event + pos,
                    "[+] Compraste comida NO certificada (-%.2f EUR)\n", price_food);
            } else {
                pos += sprintf(engine->last_event + pos,
                    "[!] No puedes permitirte ninguna comida (%.2f > %.0f)\n",
                    price_food, power);
            }
            break;

        case ABSTAIN:
            pos += sprintf(engine->last_event + pos,
                "[-] Decidiste no comprar este mes\n");
            break;
    }

    /* ---- PHASE 2: CONSUME (automatic, always happens) ---- */
    if (patient_get_stock_foodCert(pat) > 0) {
        patient_set_stock_foodCert(pat, patient_get_stock_foodCert(pat) - 1);
        pos += sprintf(engine->last_event + pos,
            "[OK] Comiste comida certificada (seguro)\n");
    } else if (patient_get_stock_food(pat) > 0) {
        patient_set_stock_food(pat, patient_get_stock_food(pat) - 1);

        /* Probabilistic contamination */
        srand(seed);
        double roll = (double)rand() / RAND_MAX;
        if (roll < PROB_CONTAMINATION) {
            health -= DAMAGE_NONCERT;
            pos += sprintf(engine->last_event + pos,
                "[!!] Comiste comida NO certificada -> CONTAMINACION! (salud -%.0f)\n",
                DAMAGE_NONCERT);
        } else {
            pos += sprintf(engine->last_event + pos,
                "[~] Comiste comida NO certificada (sin contaminacion esta vez)\n");
        }
    } else {
        health -= DAMAGE_HUNGER;
        pos += sprintf(engine->last_event + pos,
            "[!!!] No tienes comida -> HAMBRE (salud -%.0f)\n", DAMAGE_HUNGER);
    }

    /* Clamp health */
    if (health < MIN_HEALTH) health = MIN_HEALTH;
    patient_set_health(pat, health);

    /* ---- PHASE 3: ECONOMY (inflation advances) ---- */
    double inf = economy_get_inflation_current(eco);
    double monthly_inf = inf / 12.0 / 100.0;

    double new_price_food = economy_get_price_food(eco) * (1.0 + monthly_inf);
    economy_set_price_food(eco, new_price_food);
    economy_set_price_foodCert(eco, new_price_food * economy_get_factor_celiaco(eco));

    /* Phillips curve: inflation adjusts towards future estimate */
    double stab = economy_get_stabilization_speed(eco);
    double new_inf = inf + stab * (economy_get_inflation_future(eco) - inf);
    economy_set_inflation_current(eco, new_inf);

    /* GDP growth */
    if (economy_get_n_months(eco) > 0) {
        Gdp last_gdp = economy_get_gdp_last(eco);
        double gdp_growth = economy_get_growth_average(eco);
        if (gdp_growth == 0.0) gdp_growth = 2.0;
        Gdp new_gdp = last_gdp * (1.0 + gdp_growth / 12.0 / 100.0);
        economy_push_gdp(eco, new_gdp);
    }

    /* Advance calendar */
    engine->month++;
    if (engine->month > DECEMBER) {
        engine->month = JANUARY;
        engine->year++;
    }
    engine->total_months++;

    return OK;
}

/* ================================================================ */

Status engine_print(Engine* eng, FILE* out)
{
    if (!eng || !out) return ERROR;
    fprintf(out, "=== Month %d / Year %d (total: %d months) ===\n",
            eng->month, eng->year, eng->total_months);
    economy_debug(eng->economy, out);
    patient_debug(eng->patient, out);
    return OK;
}