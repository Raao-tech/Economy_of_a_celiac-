/**
 * @brief It defines the interface for the Economy module.
 *
 * @file        Economy.h
 * @author      Rafael
 * @version     0.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 *
 * Economy models the macroeconomic context of a simulated city.
 * It tracks GDP history, inflation, productivity gap, and
 * food market prices relevant to celiac patients.
 */
 
#ifndef ECONOMY_H
#define ECONOMY_H
 
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
 
/**
 * @brief Opaque type representing the economic context of a city.
 *
 * Fields are private — access only through the functions below.
 */
typedef struct _Economy Economy;
 
 
/* -------------------------------------------------------
 *  Create / Destroy
 * ------------------------------------------------------- */
 
/**
 * @brief  Allocates and initialises a new Economy.
 *
 * All numeric fields are set to 0.0.  A one-element GDP history
 * is allocated automatically (n_months = 1).
 *
 * @return Pointer to the new Economy, or NULL on allocation failure.
 */
Economy* economy_create(void);
 
/**
 * @brief  Frees all memory owned by an Economy (name, gdp_history, struct).
 *
 * @param  economy  Pointer to the Economy to destroy.
 * @return OK on success, ERROR if economy is NULL.
 */
Status economy_destroy(Economy* economy);
 
 
/* -------------------------------------------------------
 *  Name
 * ------------------------------------------------------- */
 
/**
 * @brief  Sets the name of the economy (e.g. city name).
 *
 * Duplicates the string internally.  A previous name is freed first.
 *
 * @param  economy  Target Economy.
 * @param  name     Null-terminated source string.
 * @return OK on success, ERROR on NULL arguments or allocation failure.
 */
Status economy_set_name(Economy* economy, const char* name);
 
/**
 * @brief  Returns a heap-allocated copy of the economy's name.
 *
 * The caller is responsible for freeing the returned string.
 *
 * @param  economy  Source Economy.
 * @return strdup'd name, or NULL if economy/name is NULL.
 */
char* economy_get_name(Economy* economy);
 
 
/* -------------------------------------------------------
 *  Stabilization speed
 * ------------------------------------------------------- */
 
/**
 * @brief  Sets the speed at which the economy stabilizes toward its target GDP.
 *
 * Used by the simulator to model how quickly the economy recovers
 * from or converges to its long-run equilibrium.
 *
 * @param  economy     Target Economy.
 * @param  stab_speed  Stabilization speed value.
 * @return OK on success, ERROR if economy is NULL.
 */
Status economy_set_stabilization_speed(Economy* economy, const double stab_speed);
 
/**
 * @brief  Returns the stabilization speed.
 *
 * @param  economy  Source Economy.
 * @return Stabilization speed, or MIN on error.
 */
double economy_get_stabilization_speed(Economy* economy);
 
 
/* -------------------------------------------------------
 *  Inflation — current and future
 * ------------------------------------------------------- */
 
/**
 * @brief  Sets the current inflation rate.
 *
 * Values outside [-99999, 99999] are clamped to MIN+1 / MAX-1.
 *
 * @param  economy   Target Economy.
 * @param  inflation New inflation rate.
 * @return OK on success, ERROR if economy is NULL.
 */
Status economy_set_inflation_current(Economy* economy, const double inflation);
 
/**
 * @brief  Returns the current inflation rate.
 *
 * @param  economy  Source Economy.
 * @return Inflation rate, or MIN (-99999.0) on error.
 */
double economy_get_inflation_current(Economy* economy);
 
/**
 * @brief  Sets the projected future inflation rate.
 *
 * Values outside [-99999, 99999] are clamped to MIN / MAX.
 *
 * @param  economy   Target Economy.
 * @param  inflation Projected inflation rate.
 * @return OK on success, ERROR if economy is NULL.
 */
Status economy_set_inflation_future(Economy* economy, const double inflation);
 
/**
 * @brief  Returns the projected future inflation rate.
 *
 * A high future inflation reduces expected life quality in the simulator.
 *
 * @param  economy  Source Economy.
 * @return Projected inflation rate, or MAX+1 (100000.0) on error.
 */
double economy_get_inflation_future(Economy* economy);
 
 
/* -------------------------------------------------------
 *  GDP history
 * ------------------------------------------------------- */
 
/**
 * @brief  Allocates an initial one-element GDP history array.
 *
 * Called internally by economy_create().
 *
 * @return Pointer to the array, or NULL on failure.
 */
Gdp* economy_create_gdp_history(void);
 
/**
 * @brief  Frees the GDP history array without destroying the Economy.
 *
 * @param  economy  Target Economy.
 * @return OK on success, ERROR if economy or gdp_history is NULL.
 */
Status economy_destroy_gdp_history(Economy* economy);
 
/**
 * @brief  Appends a new GDP value to the end of the history.
 *
 * Reallocates the internal array.  n_months is incremented.
 * Accumulates the monthly growth rate into growth_average (only when n_months >= 2).
 *
 * @param  economy      Target Economy.
 * @param  gdp_current  GDP value to append.
 * @return OK on success, ERROR on NULL arguments or allocation failure.
 */
Status economy_push_gdp_to_history(Economy* economy, const Gdp gdp_current);
 
/**
 * @brief  Removes and returns the most recent GDP value.
 *
 * If n_months reaches 0, gdp_history is freed and set to NULL.
 * Reallocates the internal array in the general case.
 *
 * @param  economy  Target Economy.
 * @return Last GDP value, or MIN (-99999.0) on error.
 */
Gdp economy_pop_gdp_history(Economy* economy);
 
/**
 * @brief  Returns the most recent (current) GDP value without removing it.
 *
 * Equivalent to gdp_history[n_months - 1].
 *
 * @param  economy  Source Economy.
 * @return Current GDP, or MIN on error.
 */
Gdp economy_get_gdp_current(Economy* economy);
 
/**
 * @brief  Returns the GDP value of the previous month without removing it.
 *
 * Equivalent to gdp_history[n_months - 2].
 * If only one month exists, returns gdp_history[0] (same as current).
 *
 * @param  economy  Source Economy.
 * @return Previous month GDP, or MIN on error.
 */
Gdp economy_get_gdp_last(Economy* economy);
 
/**
 * @brief  Computes the monthly GDP growth rate.
 *
 * Formula:  rate = (gdp_current - gdp_last) / gdp_last
 *
 * Returns MIN if gdp_last is 0 (division undefined) or on any error.
 *
 * @param  economy  Source Economy.
 * @return Growth rate as a fraction (e.g. 0.02 = +2%), or MIN on error.
 */
double economy_calculating_gdp_growth_rate(Economy* economy);
 
/**
 * @brief  Returns the average monthly GDP growth rate over all stored months.
 *
 * Computed as growth_average / (n_months - 1).
 * Returns 0.0 if fewer than 2 months are stored.
 *
 * @param  economy  Source Economy.
 * @return Average growth rate as a fraction, or MIN on error.
 */
double economy_calculating_growth_average(Economy* economy);
 
 
/* -------------------------------------------------------
 *  GDP max (ideal GDP / PIB ideal)
 * ------------------------------------------------------- */
 
/**
 * @brief  Scans the historical GDP array (excluding the current month)
 *         and stores the maximum value in gdp_max.
 *
 * Must be called before economy_get_max_gdp() to get an up-to-date result.
 * If only one month exists, gdp_max is set to that single value.
 *
 * @param  economy  Target Economy.
 * @return OK on success, ERROR on NULL arguments or empty history.
 */
Status economy_calculating_gdp_max(Economy* economy);
 
/**
 * @brief  Returns the cached maximum historical GDP (PIB ideal).
 *
 * Call economy_calculating_gdp_max() first to update the cache.
 *
 * @param  economy  Source Economy.
 * @return Cached gdp_max, or MIN on error.
 */
Gdp economy_get_max_gdp(Economy* economy);
 
 
/* -------------------------------------------------------
 *  n_months
 * ------------------------------------------------------- */
 
/**
 * @brief  Manually sets the number of registered GDP months.
 *
 * Use with caution — must stay consistent with the actual gdp_history size.
 *
 * @param  economy   Target Economy.
 * @param  n_months  New value (must be >= 1).
 * @return OK on success, ERROR if economy is NULL or n_months < 1.
 */
Status economy_set_nmonths(Economy* economy, const int n_months);
 
/**
 * @brief  Returns the number of GDP months currently stored.
 *
 * @param  economy  Source Economy.
 * @return n_months, or ERROR_INT (-1) if economy is NULL.
 */
int economy_get_nmonths(Economy* economy);
 
/**
 * @brief  Increments n_months by 1.
 *
 * @param  economy  Target Economy.
 * @return OK on success, ERROR if economy is NULL.
 */
Status economy_increase_nmonths(Economy* economy);
 
 
/* -------------------------------------------------------
 *  Productivity gap (brecha productiva)
 * ------------------------------------------------------- */
 
/**
 * @brief  Computes and stores the productivity gap.
 *
 * Formula:  gap = (gdp_current - gdp_max) / gdp_max
 *
 * A gap of 0 means the economy is at its historical peak.
 * Negative values indicate underperformance; positive values indicate
 * the current GDP exceeds the previous historical maximum.
 *
 * Returns ERROR if gdp_max is 0 (division undefined) or if any
 * internal calculation fails.
 *
 * @param  economy  Target Economy.
 * @return OK on success, ERROR on NULL arguments or invalid state.
 */
Status economy_calculating_productivity_gap(Economy* economy);
 
/**
 * @brief  Returns the cached productivity gap.
 *
 * Call economy_calculating_productivity_gap() first to update the cache.
 *
 * @param  economy  Source Economy.
 * @return Productivity gap (unbounded double), or MIN on error.
 */
double economy_get_productivity_gap(Economy* economy);
 
 
/* -------------------------------------------------------
 *  Food market prices
 * ------------------------------------------------------- */
 
/**
 * @brief  Sets the price of gluten-free certified food.
 *
 * Certified food carries no contamination risk for celiac patients.
 *
 * @param  economy  Target Economy.
 * @param  price    New price (must be in (MIN, MAX)).
 * @return OK on success, ERROR on NULL or out-of-range price.
 */
Status economy_set_price_foodCert(Economy* economy, const Price price);
 
/**
 * @brief  Returns the price of gluten-free certified food.
 *
 * @param  economy  Source Economy.
 * @return Price, or MAX (99999.0) on error.
 */
Price economy_get_price_foodCert(Economy* economy);
 
/**
 * @brief  Sets the price of non-certified food.
 *
 * Non-certified food is labelled gluten-free but carries a high
 * contamination risk for celiac patients.
 *
 * @param  economy  Target Economy.
 * @param  price    New price (must be in (MIN, MAX)).
 * @return OK on success, ERROR on NULL or out-of-range price.
 */
Status economy_set_price_food(Economy* economy, const Price price);
 
/**
 * @brief  Returns the price of non-certified food.
 *
 * @param  economy  Source Economy.
 * @return Price, or MAX (99999.0) on error.
 */
Price economy_get_price_food(Economy* economy);
 
 
/* -------------------------------------------------------
 *  Debug
 * ------------------------------------------------------- */
 
/**
 * @brief  Prints a debug representation of the Economy (not yet implemented).
 *
 * @param  economy  Source Economy.
 * @param  output   Optional output buffer (currently unused).
 * @return OK.
 */
Status economy_debug(Economy* economy, char* output);
 
 
#endif /* ECONOMY_H */
 