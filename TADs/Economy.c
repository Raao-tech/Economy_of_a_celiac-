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
#include <string.h>
#define MAX 99999.00
#define MIN -99999.00


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
Status   economy_destroy(Economy* economy)
{
    if(!economy) return ERROR;
    free(economy->name);
    free(economy);
    return OK;
}

/*---------- (set/get)  Name -------- */
Status  economy_set_name(Economy* economy,const char* name)
{
    int str_name = 0;
    if(!economy || !name) return ERROR;
    if(economy->name) free(economy->name);
    str_name = strlen(name); /*"HOLA" devolvera 4 chars, pero existe el null que no lo cuenta*/    
    economy->name = (char*) calloc(str_name + 1, sizeof(char));
    if(!economy->name) return ERROR;
    strcpy(economy->name, name);

    return OK;
}
char*	economy_get_name(Economy* economy)
{
    if(!economy) return NULL;
    if(!economy->name) return NULL;
    return strdup(economy->name);
}

/*---------- (set/get)  Inflation -------- */
Status  economy_set_Inflation(Economy* economy,const double inlfation)
{
    if(!economy || (inlfation >= MAX) || (inlfation <= MIN)) return ERROR;
    economy->inflation = inlfation;
    return OK;
}
double	economy_get_Inflation(Economy* economy)
{
    if(!economy) return MAX;
    return economy->inflation;
}

/*---------- (set/get)  Price FoodCert -------- */
Status  economy_set_price_foodCert(Economy* economy,const double price)
{
    if(!economy || (price <= MIN) || (price >= MAX) ) return ERROR;
    economy->price_foodCert = price;
    return OK;
}
double	economy_get_price_foodCert(Economy* economy)
{
    if(!economy) return MAX;
    return economy->price_foodCert;
}

/*---------- (set/get)  Price Food -------- */
Status  economy_set_price_food(Economy* economy,const double price)
{
    if(!economy || (price <= MIN) || (price >= MAX) ) return ERROR;
    economy->price_food = price;
    return OK;
}
double	economy_get_price_food(Economy* economy)
{
    if(!economy) return MAX;
    return economy->price_food;
}


/*=================== DEBUG ==========================*/
int economy_debug(Economy* economy, char* output)
{
    printf("Esto todavia falta hacerlo\n");
    return OK;
}