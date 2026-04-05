/**
 * @brief It define struct public Engine of the simulator
 *
 * @file        Engine.h
 * @author      Rafael
 * @version     0.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#include "types.h"
#include "Economy.h"
#include "Patient.h"

typedef struct _Engine Engine;

/*----- (Create/Destroy) Engine ------ */
Engine* engine_create();
Status  engine_destroy(Engine* engine);

/*----- (set/get) Economy ------ */
Economy*	engine_get_economy(Engine* engine);

/*----- (set/get) Patient ------*/
Patient*	engine_get_patient(Engine* engine);

/*----- (set/get) Month ------*/
Status		engine_set_month(Engine* engine, Months month);
Months		engine_get_month(Engine* engine);

Status      engine_next_month(Engine* engine);

/*========== PRINT ==========*/
int		engine_print(Engine* engine);