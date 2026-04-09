/**
 * @brief It define struct type Engine of the simulator
 *
 * @file        Engine.c
 * @author      Rafael
 * @version     0.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */

#include "../Headers/Engine.h"

struct _Engine
{
	Economy*	economy;
	Patient*	patient;
	Months		month;

};

//variacion en las tasas de ccriemiento te GDP
#define	MIN_RATIO -0.2
#define	MAX_RATIO  0.2

//Efectos Externos (Eventos)
#define MIN_EXTER  -0.5
#define MAX_EXTER   0.5



/*----- (Create/Destroy) Engine ------ */
Engine* engine_create()
{
	Engine* new_engine = (Engine*) malloc(sizeof(Engine));
	if(!new_engine) return NULL;

	/*Economy*/
	new_engine->economy = engine_create();
	if(!new_engine->economy){
		free(new_engine);
		return NULL;
	}

	/*Patient*/
	new_engine->patient = patient_create();
	if(!new_engine->patient){
		economy_destroy(new_engine->economy);
		free(new_engine);
		return NULL;
	}

	new_engine->month = JANUARY;

	return new_engine;
} 
Status  engine_destroy(Engine* engine)
{
	if(!engine) return ERROR;
	if(engine->economy) economy_destroy(engine->economy);
	if(engine->patient) patient_destroy(engine->patient);
	free(engine);
	return OK;
}

/*----- (get) Economy ------ */
Economy*	engine_get_economy(Engine* engine)
{
	if(!engine || !engine->economy) return NULL;
	return engine->economy;
}

/*----- (get) Patient ------*/
Patient*	engine_get_patient(Engine* engine)
{
	if(!engine || !engine->patient) return NULL;
	return engine->patient;
}

/*----- (set/get) Month ------*/
Status		engine_set_month(Engine* engine, Months month)
{
	if(!engine ||  month == UNKNOW) return ERROR;

	
	engine->month = month;
	return OK;
}
Months		engine_get_month(Engine* engine)
{
	if(!engine) return UNKNOW;
	return engine->month;
}

Status		engine_next_month(Engine* engine, int	seed_time)
{
	Patient*	patient = NULL;
	Economy*	economy = NULL;

	/* Datos tmp para economy*/
	double		economy_inf_fut;	/*inf*/
	double		economy_inf_curr;

	double		economy_gdp_fut;	/*PIB*/
	double		economy_gdp_curr;
	double		economy_gdp_last;
	double		economy_gdp_grate;
	double		economy_gdp_variation;

	double		shock_rate;
	double		shock_velocity;
	double		shock_external;

	if(!engine) return ERROR;
	patient = engine_get_patient(engine);
	economy = engine_get_economy(engine);
	if(!patient || economy) return ERROR;

	//establecemos los valores del GDP
	economy_gdp_curr = economy_get_gdp_current(economy);
	economy_gdp_last = economy_get_gdp_last(economy);
	economy_gdp_grate = economy_calculating_gdp_growth_rate(economy);
	shock_rate = engine_number_ramdon()

	economy_gdp_variation = 



	//la inflacion de mañana, ahora es la de hoy, y la inflacion de mañana, la claculamos a partir de  la de hoy
	economy_inf_curr = economy_get_inflation_future(economy); //inlfacion de mañana es la de hoy


	economy_inf_fut =  
	/**/


	
	
}

double	engine_number_ramdon(double min, double max, unsigned int seed_time){
	srand(seed_time); // inicializamos la semilla aleatoria
	double rand_number = ((double)rand())/RAND_MAX; //nos creamos un numero alatrio entre [seed_time/seed_time+n , 1]
	double tam_set = max - min; //tamaño del rango
	return ((rand_number*tam_set) + min);
}

/*========== PRINT ==========*/
int		engine_print(Engine* engine);
