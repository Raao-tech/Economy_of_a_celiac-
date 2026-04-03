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

/*La comida siempre dira libre de gluten, 
pero la no ceritiicada tiene un reisgo de 
contaminacion muy alto*/
struct _Patient
{
    char*   name;
    int     Health;
    int     Saciety;
    double  salary;

};