/**
 * @brief Patient TAD implementation
 *
 * @file        Patient.c
 * @author      Rafael
 * @version     1.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#include "../Headers/Patient.h"

struct _Patient {
    char*       name;
    double      health;
    SocialClass social_class;
    int         stock_foodCert;
    int         stock_food;
    double      salary;
};

/* ---- Create / Destroy ---- */

Patient* patient_create()
{
    Patient* p = (Patient*)malloc(sizeof(Patient));
    if (!p) return NULL;

    p->name           = NULL;
    p->health         = MAX_HEALTH;
    p->social_class   = CLASS_UNKNOW;
    p->stock_foodCert = 0;
    p->stock_food     = 0;

    return p;
}

Status patient_destroy(Patient* p)
{
    if (!p) return ERROR;
    free(p->name);
    free(p);
    return OK;
}

/* ---- Name ---- */

Status patient_set_name(Patient* p, const char* name)
{
    char* dup;
    if (!p || !name) return ERROR;
    dup = strdup(name);
    if (!dup) return ERROR;
    free(p->name);
    p->name = dup;
    return OK;
}

const char* patient_get_name(Patient* p)
{
    if (!p) return NULL;
    return p->name;
}

/* ---- Health ---- */

Status patient_set_health(Patient* p, double h)
{
    if (!p) return ERROR;
    if (h < MIN_HEALTH) h = MIN_HEALTH;
    if (h > MAX_HEALTH) h = MAX_HEALTH;
    p->health = h;
    return OK;
}

double patient_get_health(Patient* p)
{
    if (!p) return ERROR_HEALTH;
    return p->health;
}

/* ---- Social class ---- */

Status patient_set_social_class(Patient* p, SocialClass sc)
{
    if (!p) return ERROR;
    p->social_class = sc;
    return OK;
}

SocialClass patient_get_social_class(Patient* p)
{
    if (!p) return CLASS_UNKNOW;
    return p->social_class;
}

/* ---- Purchasing power (derived) ---- */

double patient_get_purchasing_power(Patient* p)
{
    if (!p) return 0.0;
    return p->salary;
}

Status patient_set_purchasing_power(Patient* p, double salary)
{
    if (!p || salary<0.0) return ERROR;
    p->salary = salary;
    return OK;
}

/* ---- Stock certified ---- */

Status patient_set_stock_foodCert(Patient* p, int stock)
{
    if (!p || stock < 0) return ERROR;
    p->stock_foodCert = stock;
    return OK;
}

int patient_get_stock_foodCert(Patient* p)
{
    if (!p) return ERROR_INT;
    return p->stock_foodCert;
}

/* ---- Stock non-certified ---- */

Status patient_set_stock_food(Patient* p, int stock)
{
    if (!p || stock < 0) return ERROR;
    p->stock_food = stock;
    return OK;
}

int patient_get_stock_food(Patient* p)
{
    if (!p) return ERROR_INT;
    return p->stock_food;
}

/* ---- Debug ---- */

Status patient_debug(Patient* p, FILE* out)
{
    if (!p || !out) return ERROR;
    fprintf(out, "[Patient] %s | HP: %.1f | Class: %d | CertStock: %d | FoodStock: %d | Power: %.0f\n",
            p->name ? p->name : "???",
            p->health,
            p->social_class,
            p->stock_foodCert,
            p->stock_food,
            patient_get_purchasing_power(p));
    return OK;
}