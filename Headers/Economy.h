/**
 * @brief It define struct type Economy
 *
 * @file        Economy.h
 * @author      Rafael
 * @version     0.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#include "types.h"

typedef struct _Economy Economy;

/*---------- (Create/Destroy) -------- */
Economy* economy_create();
Status   economy_destroy(Economy* economy);

/*---------- (set/get)  Name -------- */
Status  economy_set_name(Economy* economy,const char* name);
char*	economy_get_name(Economy* economy);

/*---------- (set/get)  Inflation -------- */
Status  economy_set_Inflation(Economy* economy,const double inlfation);
double	economy_get_Inflation(Economy* economy);

/*---------- (set/get)  Price FoodCert -------- */
Status  economy_set_price_foodCert(Economy* economy,const double price);
double	economy_get_price_foodCert(Economy* economy);

/*---------- (set/get)  Price Food -------- */
Status  economy_set_price_food(Economy* economy,const double price);
double	economy_get_price_food(Economy* economy);


/*=================== DEBUG ==========================*/

int economy_debug(Economy* economy, char* output);