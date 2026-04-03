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