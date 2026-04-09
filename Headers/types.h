/**
 * @brief Shared types and constants for the celiac economy simulator
 *
 * @file        types.h
 * @author      Rafael
 * @version     1.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#ifndef TYPES_H
#define TYPES_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


#define WORD_SIZE 256
#define MAX_LINE  1024
#define ERROR_INT -1

/* ---- Status ---- */
typedef enum { ERROR, OK } Status;

/* ---- City selection ---- */
typedef enum {
    ECO_UNKNOW,
    MADRID,
    ALMERIA,
    CARACAS,
    BARINAS
} EcoChoose;

/* ---- Social class ---- */
typedef enum {
    CLASS_UNKNOW,
    UPPER_CLASS,
    MIDDLE_CLASS,
    LOWER_CLASS
} SocialClass;

/* ---- Player actions per month ---- */
typedef enum {
    BUY_CERTIFIED,
    BUY_NONCERTIFIED,
    ABSTAIN
} PlayerAction;

/* ---- Months ---- */
typedef enum {
    MONTH_UNKNOW,
    JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE,
    JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
} Months;

/* ---- Numeric aliases ---- */
typedef double Gdp;
typedef double Price;

/* ---- Health constants ---- */
#define MAX_HEALTH      100.0
#define MIN_HEALTH        0.0
#define ERROR_HEALTH     -1.0

/* ---- Damage constants ---- */
#define DAMAGE_NONCERT   10.0   /* health lost from contaminated food ... (podriamos hacer que varie)   */
#define DAMAGE_HUNGER    20.0   /* health lost from not eating          */

/* ---- Economy limits ---- */
#define MAX_PRICE    99999.0
#define MIN_PRICE        0.0
#define MAX_INFLATION  500.0
#define MIN_INFLATION -100.0

/* ---- Purchasing power by social class (EUR/month for food) ---- */
#define POWER_UPPER    800.0
#define POWER_MIDDLE   400.0
#define POWER_LOWER    180.0

/* ---- Valores de stocks iniciales por clase ---- */
#define STOCK_CERT_UPPER    8
#define STOCK_CERT_MIDDLE   5
#define STOCK_CERT_LOWER    2
#define STOCK_FOOD_UPPER    4
#define STOCK_FOOD_MIDDLE   8
#define STOCK_FOOD_LOWER   12

/* ---- Contamination probability for non-certified (0..1) ---- */
#define PROB_CONTAMINATION 0.35

#endif /* TYPES_H */