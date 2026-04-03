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
