/**
 * @brief Engine TAD - simulation loop coordinator
 *
 * @file        Engine.h
 * @author      Rafael
 * @version     1.1
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#ifndef ENGINE_H
#define ENGINE_H

#include "types.h"
#include "Economy.h"
#include "Patient.h"

typedef struct _Engine Engine;

/* ---- Create / Destroy ---- */
Engine* engine_create();
Status  engine_destroy(Engine* engine);

/* ---- Accessors ---- */
Economy*  engine_get_economy(Engine* engine);
Patient*  engine_get_patient(Engine* engine);
int       engine_get_month(Engine* engine);
int       engine_get_year(Engine* engine);

/* ---- Event log from last month ---- */
const char* engine_get_last_event(Engine* engine);

/* ---- Core simulation step (now uses player's action) ---- */
Status  engine_next_month(Engine* engine, PlayerAction action, int seed);

/* ---- Print ---- */
Status  engine_print(Engine* engine, FILE* out);

#endif /* ENGINE_H */