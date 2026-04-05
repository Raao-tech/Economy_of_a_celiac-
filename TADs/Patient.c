/**
 * @brief It define struct type Patient
 *
 * @file        Patient.c
 * @author      Rafael
 * @version     0.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */

#include "../Headers/Patient.h"
#include <string.h>

/*La comida siempre dira libre de gluten, 
pero la no ceritiicada tiene un reisgo de 
contaminacion muy alto*/
struct _Patient
{
    char*   	name;
    double  	health; /*Puede disminuir  al comer comida no certificada    Y disminuira una unidad cuando Saciety este menor a 33/100*/
	SocialClass	social_classs;
    int     	stock_foodCert; /*Comida certificada acumulada*/
    int     	stock_food; /*Comida No certificada acumulada, se acabara despeus de que se acabe la acumulada*/
};



/*=========== (Create/Destroy) Patient ==========================*/
Patient*    patient_create()
{
	Patient* new_patient = (Patient*) malloc(sizeof(Patient));
	if(!new_patient) return NULL;

	new_patient->name = 			NULL;
	new_patient->health = 			MAX_HEALTH;
	new_patient->social_classs = 	UNKNOW;
	new_patient->stock_food = 		0;
	new_patient->stock_foodCert = 	0;

	return new_patient;
}
Status patient_destroy(Patient* patient)
{
	if(!patient) return ERROR;
	if(patient->name) free(patient->name);
	free(patient);
	return OK;
}

/*============== (Set/Get) Health ==========*/
Status 	patient_set_health(Patient* patient, const double n_healt)
{
	if(!patient || n_healt > MAX_HEALTH || n_healt < MIN_HEALTH ) return ERROR;
	patient->health = n_healt;
	return OK;
}
double	patient_get_health(Patient* patient)
{
	if(!patient) return ERROR_HEALTH;
	return patient->health;
}

/*========== (Set/Get) Name ==============*/
Status patient_set_name(Patient* patient, char* name)
{
	if(!patient || !name) return ERROR;
	if(patient->name){
		free(patient->name);
		patient->name = NULL;
	}

	int	tam_name = strlen(name);
	patient->name = (char*) calloc(tam_name+1, sizeof(char));
	if(!patient->name) return ERROR;

	strcpy(patient->name, name);
	return OK;
}
char* 	patient_get_name(Patient* patient)
{
	if(!patient || !patient->name) return NULL;
	return strdup(patient->name);
}
