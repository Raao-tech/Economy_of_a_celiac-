/**
 * @brief Patient TAD - celiac patient state
 *
 * @file        Patient.h
 * @author      Rafael
 * @version     1.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#ifndef PATIENT_H
#define PATIENT_H

#include "types.h"

typedef struct _Patient Patient;

/* ---- Create / Destroy ---- */
Patient* patient_create();
Status   patient_destroy(Patient* patient);

/* ---- Name ---- */
Status       patient_set_name(Patient* p, const char* name);
const char*  patient_get_name(Patient* p);

/* ---- Health ---- */
Status  patient_set_health(Patient* p, double h);
double  patient_get_health(Patient* p);

/* ---- Social class ---- */
Status      patient_set_social_class(Patient* p, SocialClass sc);
SocialClass patient_get_social_class(Patient* p);

/* ---- Purchasing power (derived from social class) ---- */
double  patient_get_purchasing_power(Patient* p);

/* ---- Stock certified ---- */
Status  patient_set_stock_foodCert(Patient* p, int stock);
int     patient_get_stock_foodCert(Patient* p);

/* ---- Stock non-certified ---- */
Status  patient_set_stock_food(Patient* p, int stock);
int     patient_get_stock_food(Patient* p);

/* ---- Debug ---- */
Status  patient_debug(Patient* p, FILE* out);

#endif /* PATIENT_H */