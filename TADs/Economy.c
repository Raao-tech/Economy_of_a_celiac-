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

    Gdp* gdp_history;
    Gdp  gdp_max; /*PIB ideal*/
    int  n_months; /*n_pibs registered.   gdp_history[n_month]] = gdp_current*/
	
	double growth_average; 
	double stabilization_speed; 

    double  inflation_current;
    double  inflation_future;

    double  productivity_gap;    /*Calculado a partir del PIB mas alto hisotirco ("PIB ideal")*/
    
    /* Mercado de celiacos*/
    Price  price_foodCert;     
    Price  price_food;
};


/*---------- (Create/Destroy) -------- */
Economy* economy_create()
{
    Economy* new_economy = (Economy*) malloc(sizeof(Economy));
    if(!new_economy) return NULL;
    
	new_economy->name =                     NULL;
	/*Economics Indicators*/
	new_economy->inflation_current =        0.0;
    new_economy->inflation_future =         0.0;
    new_economy->productivity_gap =         0.0;
	new_economy->growth_average   =			0.0;
	new_economy->stabilization_speed   =	0.0;
	/*Market*/
    new_economy->price_food =               0.0;
    new_economy->price_foodCert =           0.0;
	/*GDP*/
    new_economy->gdp_max =                  0.0;
    new_economy->n_months =                  1;
	new_economy->gdp_history = economy_create_gdp_history();
    if(!new_economy->gdp_history){ 
        free(new_economy);   
        return NULL;
    }

    return new_economy;
}
Status   economy_destroy(Economy* economy)
{
    if(!economy)                return ERROR;
    if(economy->name)           free(economy->name);
    if(economy->gdp_history)    free(economy->gdp_history);
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
/*---------- (set/get) Stabilization Speed ------------*/
Status		economy_set_stabilization_speed(Economy* economy, const double stab_speed){
	if(!economy) return ERROR;
	economy->stabilization_speed = stab_speed;
	return OK;
}
double		economy_get_stabilization_speed(Economy* economy){
	if(!economy) return MIN;
	return (economy->stabilization_speed);
}

/*---------- (set/get)  Inflation Current,future  -------- */
/*Current*/
Status  economy_set_inflation_current(Economy* economy,const double inlfation)
{
    if(!economy) return ERROR;
    if(inlfation > MAX) { economy->inflation_current = MAX-1; return  OK;}
    if(inlfation < MIN) { economy->inflation_current = MIN+1; return  OK;}
    economy->inflation_current = inlfation;
    return OK;
}

double	economy_get_inflation_current(Economy* economy)
{
    if(!economy) return (MIN);
    return economy->inflation_current;
}


/*Future*/
Status  economy_set_inflation_future(Economy* economy,const double inlfation)
{
    if(!economy) return ERROR;
    if(inlfation > MAX) { economy->inflation_future = MAX; return  OK;}
    if(inlfation < MIN) { economy->inflation_future = MIN; return  OK;}
    economy->inflation_future = inlfation;
    return OK;
}
double	economy_get_inflation_future(Economy* economy)
{
    if(!economy) return (MAX+1); //si se usa una inflacion alata la esperanza de vida disminuye
    return economy->inflation_future;
}

/*---------- GDP (history, max, n_months) -------- */
/*(Creat/Destroy) gdp_history*/
Gdp  *economy_create_gdp_history(){
    Gdp*    gdp_history = (Gdp*) calloc(1,sizeof(Gdp));
    if(!gdp_history) return NULL;
    return gdp_history;
}
Status economy_destroy_gdp_history(Economy* economy){
    if(!economy)              return ERROR;
    if(!economy->gdp_history) return ERROR;
    free(economy->gdp_history);
    return OK;
}

/*(Push/Pop/current) gdp_history*/
Status  economy_push_gdp_to_history(Economy* economy, const Gdp gdp_current){
    Gdp*    temp = NULL;
    if(!economy)                return ERROR;
    if(!economy->gdp_history)   return ERROR;
    if(economy->n_months <= 0)   return ERROR;

    int n_months = economy->n_months;
    temp = (Gdp*)realloc(economy->gdp_history, sizeof(Gdp)*(n_months+1));
    if(!temp) return    ERROR;


    temp[n_months] = gdp_current;
    economy->gdp_history = temp;
    
    if(!economy->gdp_history)   return ERROR;
    economy->n_months++;

	economy->growth_average += economy_calculating_gdp_growth_rate(economy);
    return OK;
}
Gdp economy_pop_gdp_history(Economy* economy){
    Gdp*    temp;
    Gdp     gdp_last;
    int     n_months;
    if(!economy)                return MIN;
    if(!economy->gdp_history)   return MIN;
    if(economy->n_months < 1)    return MIN;
    if(economy->n_months == 1){
        gdp_last = economy->gdp_history[0];
		free(economy->gdp_history);
		economy->gdp_history = NULL;
		economy->n_months = 0;
        return  gdp_last;
    }  

    n_months = economy->n_months;

    gdp_last = economy->gdp_history[n_months-1];
    temp = (Gdp*) realloc(economy->gdp_history, sizeof(Gdp)*(n_months-1));
    if(!temp) return MIN;

    economy->gdp_history = temp;
    economy->n_months--;
    return gdp_last;
}

double	economy_calculating_gdp_growth_rate(Economy* economy){
	if(!economy || !economy->gdp_history) return MIN;
	Gdp gdp_current = economy_get_gdp_current(economy);
	Gdp gdp_past	= economy_get_gdp_last(economy);
	if(gdp_current == MIN || gdp_past == MIN) return MIN;
	if(gdp_past == 0.0) return MAX;

	double	growth_rate = (gdp_current - gdp_past)/gdp_past;

	return growth_rate;
}

Gdp economy_get_gdp_current(Economy* economy){
	if(!economy || !economy->gdp_history || economy->n_months < 1) return MIN;
	return economy->gdp_history[economy->n_months-1];
}
Gdp economy_get_gdp_last(Economy* economy){
	if(!economy || !economy->gdp_history || economy->n_months < 1) return MIN;
	if(economy->n_months == 1) return economy->gdp_history[0];
	return economy->gdp_history[economy->n_months-2];
}
double	economy_calculating_growth_average(Economy* economy){
	if(!economy || economy->n_months < 1) return MIN;
	return (economy->growth_average/economy->n_months);
}

/* (max) gdp_history*/
Status  economy_calculating_gdp_max(Economy* economy){
    Gdp* 	history_gdp = NULL;
	Gdp		max_gdp;
    int 	n_months;
	int		i;
    if(!economy || !economy->gdp_history || economy->n_months < 1) return ERROR;
	if(economy->n_months == 1){
		economy->gdp_max = economy->gdp_history[0];
		return OK;
	}

    history_gdp =   economy->gdp_history;
    n_months =       economy->n_months;
	max_gdp =  		economy->gdp_history[0];

    for(i = 0; i< (n_months-1); i++){
		if(history_gdp[i] > max_gdp) max_gdp = history_gdp[i];
	}
	economy->gdp_max = max_gdp;
	history_gdp = NULL;
	return OK;
}
Gdp economy_get_max_gdp(Economy* economy){
    if(!economy) return MIN;
	return economy->gdp_max;
}

/*(Set/Get/increment) n_months*/
Status	economy_set_nmonths(Economy* economy, const int n_months){
	if(!economy || n_months < 1) return ERROR;
	economy->n_months = n_months;
	return OK;
}
int	economy_get_nmonths(Economy*	economy){
	if(!economy) return ERROR_INT;
	return	economy->n_months;
}
Status	economy_increase_nmonths(Economy* economy){
	if(!economy) return ERROR;
	economy->n_months++;
	return OK;	
}


/*----------- (calculating/get) productivity gap ----------------*/

Status	economy_calculating_productivity_gap(Economy* economy){
	Gdp gdp_current;
	Gdp gdp_max;
	if(!economy || !economy->gdp_history) return ERROR;

	if(economy_calculating_gdp_max(economy) == ERROR) return ERROR;
	gdp_max = economy_get_max_gdp(economy);
	gdp_current = economy_get_gdp_current(economy);
	if(gdp_max == MIN || gdp_current == MIN || gdp_max == 0.0) return ERROR;
	/*Calculo de la brecha productiva en el año presente*/
	economy->productivity_gap = (gdp_current-gdp_max)/(gdp_max); //estará en [-infintio,infinito]
	return OK;
}
double	economy_get_productivity_gap(Economy*	economy){
	if(!economy) return MIN;
	return	economy->productivity_gap;
}

/*---------- (set/get)  Price FoodCert -------- */
Status  economy_set_price_foodCert(Economy* economy,const Price price)
{
    if(!economy || (price <= MIN) || (price >= MAX) ) return ERROR;
    economy->price_foodCert = price;
    return OK;
}
Price	economy_get_price_foodCert(Economy* economy)
{
    if(!economy) return MAX;
    return economy->price_foodCert;
}

/*---------- (set/get)  Price Food -------- */
Status  economy_set_price_food(Economy* economy,const Price price)
{
    if(!economy || (price <= MIN) || (price >= MAX) ) return ERROR;
    economy->price_food = price;
    return OK;
}
Price	economy_get_price_food(Economy* economy)
{
    if(!economy) return MAX;
    return economy->price_food;
}


/*=================== DEBUG ==========================*/
Status economy_debug(Economy* economy, char* output)
{
    printf("Esto todavia falta hacerlo\n");
    return OK;
}