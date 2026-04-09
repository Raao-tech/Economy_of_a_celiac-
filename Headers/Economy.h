/**
 * @brief Economy TAD - models economic environment of a city
 *
 * @file        Economy.h
 * @author      Rafael
 * @version     1.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#ifndef ECONOMY_H
#define ECONOMY_H

#include "types.h"

typedef struct _Economy Economy;

/* ---- Create / Destroy ---- */
Economy* economy_create();
Status   economy_destroy(Economy* economy);

/* ---- Name ---- */
Status       economy_set_name(Economy* e, const char* name);
const char*  economy_get_name(Economy* e);

/* ---- Inflation ---- */
Status  economy_set_inflation_current(Economy* e, double inf);
double  economy_get_inflation_current(Economy* e);
Status  economy_set_inflation_future(Economy* e, double inf);
double  economy_get_inflation_future(Economy* e);

/* ---- Food prices ---- */
Status  economy_set_price_food(Economy* e, Price p);
Price   economy_get_price_food(Economy* e);
Status  economy_set_price_foodCert(Economy* e, Price p);
Price   economy_get_price_foodCert(Economy* e);

/* ---- Factor celiaco ---- */
Status  economy_set_factor_celiaco(Economy* e, double factor);
double  economy_get_factor_celiaco(Economy* e);

/* ---- Stabilization speed (Phillips curve param) ---- */
Status  economy_set_stabilization_speed(Economy* e, double s);
double  economy_get_stabilization_speed(Economy* e);

/* ---- GDP history ---- */
Status  economy_push_gdp(Economy* e, Gdp value);
Gdp     economy_get_gdp_last(Economy* e);
int     economy_get_n_months(Economy* e);
double  economy_get_growth_rate(Economy* e);
double  economy_get_growth_average(Economy* e);
Gdp     economy_get_gdp_max(Economy* e);

/* ---- Debug ---- */
Status  economy_debug(Economy* e, FILE* out);

#endif /* ECONOMY_H */