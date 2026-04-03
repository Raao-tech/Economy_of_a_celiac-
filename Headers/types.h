#include "stdio.h"
#include "stdlib.h"

/*Manejo de Errores*/
typedef enum 
{
    ERROR, 
    OK
}Status;


/*Choose to menu*/
typedef enum 
{ 
    UNKNOW, 
    MADRID, 
    CARACAS, 
    ALMERIA, 
    BARINAS
}EcoChoose;

typedef enum 
{ 
    UNKNOW, 
    UPPER_CLASS, 
    MIDDLE_CLASS, 
    LOWER_CLASS
}PatChoose;


/*Monuths of year*/
typedef enum 
{ 
    UNKNOW, 
    JANUARY, 
    FEBRUARY, 
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
}Months;