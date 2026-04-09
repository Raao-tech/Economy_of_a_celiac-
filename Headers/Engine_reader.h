/**
 * @brief It define the component to read files .txt
 *
 * @file        Engine_reader.h
 * @author      Rafael
 * @version     0.0
 * @date        9-4-2026
 * @copyright   GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "Engine.h"

/*  Esta funcion lee un archvivo .txt con los datos economicos */
Status  engine_reader_file_economy(Engine*  engine, char*   namefile);

/*  
*   Esta funcion lee un archvivo .txt 
*   con los datos socioeconomicos y medicos 
*   del paciente 
*/
Status  engine_reader_file_patient(Engine*  engine, char*   namefile);