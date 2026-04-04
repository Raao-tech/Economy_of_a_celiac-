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

Status		engine_next_month(Engine* engine)
{
	if(!engine) return ERROR;

	/*Aca ira la lgica para actualizar el estado de la economia y el paciente*/
}
/*========== PRINT ==========*/
int		engine_print(Engine* engine);
