/**
 * @brief It define struct type Economy
 *
 * @file        Economy.c
 * @author      Rafael
 * @version     0.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */

#include "../Headers/Economy.h"

/*La comida siempre dira libre de gluten, 
pero la no ceritiicada tiene un reisgo de 
contaminacion muy alto*/
struct _Economy
{
    char*   name;
    double  inflation;
    double  price_foodCert;
    double  price_food;
};


/*---------- (Create/Destroy) -------- */
Economy* economy_create()
{
    Economy* new_economy = (Economy*) malloc(sizeof(Economy));
    if(!new_economy) return NULL;

    new_economy->inflation =        0.0;
    new_economy->name =             NULL;
    new_economy->price_food =       0.0;
    new_economy->price_foodCert =   0.0;

    return new_economy;
}
void     economy_destroy(Economy* economy)
{
 free(economy->name);
 free(economy);
}

/*---------- (set/get)  Name -------- */
Status  economy_set_name(Economy* economy,char* name);
char*	economy_get_name(Economy* economy);

/*---------- (set/get)  Inflation -------- */
Status  economy_set_Inflation(Economy* economy,double inlfation);
double	economy_get_Inflation(Economy* economy);

/*---------- (set/get)  Price FoodCert -------- */
Status  economy_set_price_foodCert(Economy* economy,double price);
double	economy_get_price_foodCert(Economy* economy);

/*---------- (set/get)  Price Food -------- */
Status  economy_set_price_food(Economy* economy,double price);
double	economy_get_price_food(Economy* economy);


/*=================== DEBUG ==========================*/

int economy_debug(Economy* economy, char* output);