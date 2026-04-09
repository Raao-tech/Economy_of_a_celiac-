/**
 * @brief Economy TAD implementation
 *
 * @file        Economy.c
 * @author      Rafael
 * @version     1.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#include "../Headers/Economy.h"

#define INIT_GDP_CAP 24

struct _Economy {
    char*   name;
    double  inflation_current;
    double  inflation_future;
    Price   price_food;
    Price   price_foodCert;
    double  factor_celiaco;
    double  stabilization_speed;

    Gdp*    gdp_history;
    int     n_months;
    int     gdp_cap;
};

/* ================================================================
 *  Create / Destroy
 * ================================================================ */

Economy* economy_create()
{
    Economy* e = (Economy*)malloc(sizeof(Economy));
    if (!e) return NULL;

    e->name = NULL;
    e->inflation_current = 0.0;
    e->inflation_future  = 0.0;
    e->price_food     = 0.0;
    e->price_foodCert = 0.0;
    e->factor_celiaco = 1.0;
    e->stabilization_speed = 0.3;

    e->gdp_cap  = INIT_GDP_CAP;
    e->n_months = 0;
    e->gdp_history = (Gdp*)calloc(e->gdp_cap, sizeof(Gdp));
    if (!e->gdp_history) { free(e); return NULL; }

    return e;
}

Status economy_destroy(Economy* e)
{
    if (!e) return ERROR;
    free(e->name);
    free(e->gdp_history);
    free(e);
    return OK;
}

/* ================================================================
 *  Name
 * ================================================================ */

Status economy_set_name(Economy* e, const char* name)
{
    char* dup;
    if (!e || !name) return ERROR;
    dup = strdup(name);
    if (!dup) return ERROR;
    free(e->name);
    e->name = dup;
    return OK;
}

const char* economy_get_name(Economy* e)
{
    if (!e) return NULL;
    return e->name;
}

/* ================================================================
 *  Inflation
 * ================================================================ */

Status economy_set_inflation_current(Economy* e, double inf)
{
    if (!e || inf < MIN_INFLATION || inf > MAX_INFLATION) return ERROR;
    e->inflation_current = inf;
    return OK;
}

double economy_get_inflation_current(Economy* e)
{
    if (!e) return MIN_INFLATION - 1;
    return e->inflation_current;
}

Status economy_set_inflation_future(Economy* e, double inf)
{
    if (!e || inf < MIN_INFLATION || inf > MAX_INFLATION) return ERROR;
    e->inflation_future = inf;
    return OK;
}

double economy_get_inflation_future(Economy* e)
{
    if (!e) return MAX_INFLATION + 1;
    return e->inflation_future;
}

/* ================================================================
 *  Prices
 * ================================================================ */

Status economy_set_price_food(Economy* e, Price p)
{
    if (!e || p < MIN_PRICE || p > MAX_PRICE) return ERROR;
    e->price_food = p;
    return OK;
}

Price economy_get_price_food(Economy* e)
{
    if (!e) return MAX_PRICE;
    return e->price_food;
}

Status economy_set_price_foodCert(Economy* e, Price p)
{
    if (!e || p < MIN_PRICE || p > MAX_PRICE) return ERROR;
    e->price_foodCert = p;
    return OK;
}

Price economy_get_price_foodCert(Economy* e)
{
    if (!e) return MAX_PRICE;
    /* If factor is set and price_foodCert hasn't been set directly,
       derive it. Otherwise return stored value. */
    if (e->price_foodCert <= 0.0 && e->factor_celiaco > 0.0)
        return e->price_food * e->factor_celiaco;
    return e->price_foodCert;
}

/* ================================================================
 *  Factor celiaco
 * ================================================================ */

Status economy_set_factor_celiaco(Economy* e, double factor)
{
    if (!e || factor <= 0.0) return ERROR;
    e->factor_celiaco = factor;
    return OK;
}

double economy_get_factor_celiaco(Economy* e)
{
    if (!e) return 1.0;
    return e->factor_celiaco;
}

/* ================================================================
 *  Stabilization speed
 * ================================================================ */

Status economy_set_stabilization_speed(Economy* e, double s)
{
    if (!e || s < 0.0 || s > 1.0) return ERROR;
    e->stabilization_speed = s;
    return OK;
}

double economy_get_stabilization_speed(Economy* e)
{
    if (!e) return 0.0;
    return e->stabilization_speed;
}

/* ================================================================
 *  GDP history
 * ================================================================ */

Status economy_push_gdp(Economy* e, Gdp value)
{
    if (!e) return ERROR;

    if (e->n_months >= e->gdp_cap) {
        int new_cap = e->gdp_cap * 2;
        Gdp* tmp = realloc(e->gdp_history, new_cap * sizeof(Gdp));
        if (!tmp) return ERROR;
        e->gdp_history = tmp;
        e->gdp_cap = new_cap;
    }

    e->gdp_history[e->n_months] = value;
    e->n_months++;
    return OK;
}

Gdp economy_get_gdp_last(Economy* e)
{
    if (!e || e->n_months == 0) return -1.0;
    return e->gdp_history[e->n_months - 1];
}

int economy_get_n_months(Economy* e)
{
    if (!e) return ERROR_INT;
    return e->n_months;
}

double economy_get_growth_rate(Economy* e)
{
    if (!e || e->n_months < 2) return 0.0;
    Gdp prev = e->gdp_history[e->n_months - 2];
    Gdp curr = e->gdp_history[e->n_months - 1];
    if (prev == 0.0) return 0.0;
    return ((curr - prev) / prev) * 100.0;
}

double economy_get_growth_average(Economy* e)
{
    if (!e || e->n_months < 2) return 0.0;
    double sum = 0.0;
    for (int i = 1; i < e->n_months; i++) {
        Gdp prev = e->gdp_history[i - 1];
        if (prev != 0.0)
            sum += ((e->gdp_history[i] - prev) / prev) * 100.0;
    }
    return sum / (e->n_months - 1);
}

Gdp economy_get_gdp_max(Economy* e)
{
    if (!e || e->n_months == 0) return -1.0;
    Gdp max = e->gdp_history[0];
    for (int i = 1; i < e->n_months; i++) {
        if (e->gdp_history[i] > max) max = e->gdp_history[i];
    }
    return max;
}

/* ================================================================
 *  Debug
 * ================================================================ */

Status economy_debug(Economy* e, FILE* out)
{
    if (!e || !out) return ERROR;
    fprintf(out, "[Economy] %s | Inf: %.2f%% -> %.2f%% | Food: %.2f | Cert: %.2f (x%.1f) | GDP(%d): %.1f\n",
            e->name ? e->name : "???",
            e->inflation_current,
            e->inflation_future,
            e->price_food,
            economy_get_price_foodCert(e),
            e->factor_celiaco,
            e->n_months,
            economy_get_gdp_last(e));
    return OK;
}