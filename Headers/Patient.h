/**
 * @brief It define struct type Patient
 *
 * @file        Patient.h
 * @author      Rafael
 * @version     0.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#include "types.h"


typedef struct _Patient Patient;


/*---------- (Create/Destroy) -------- */
Patient* patient_create();
Status   patient_destroy(Patient* patient);

/*---------- (set/get)  Name -------- */
Status  patient_set_name(Patient* patient,const char* name);
char*	patient_get_name(Patient* patient);

/*---------- (set/get)  Inflation -------- */
Status  patient_set_Inflation(Patient* patient,const double inlfation);
double	patient_get_Inflation(Patient* patient);


/*=================== DEBUG ==========================*/

int patient_debug(Patient* patient, char* output);