/**
 * @brief Engine_reader - parses economy .txt files
 *
 * @file        Engine_reader.c
 * @author      Rafael
 * @version     1.0
 * @date        10-4-2026
 * @copyright   GNU Public License
 */
#include "../Headers/Engine_reader.h"

/* ---- Helper: trim leading whitespace ---- */
static char* trim(char* s)
{
    while (*s == ' ' || *s == '\t') s++;
    /* trim trailing newline */
    char* end = s + strlen(s) - 1;
    while (end > s && (*end == '\n' || *end == '\r' || *end == ' ')) {
        *end = '\0';
        end--;
    }
    return s;
}

/* ---- File path mapping ---- */

const char* reader_get_filename(EcoChoose city)
{
    switch (city) {
        case MADRID:  return "Economys/Madrid.txt";
        case ALMERIA: return "Economys/Almeria.txt";
        case CARACAS: return "Economys/Caracas.txt";
        case BARINAS: return "Economys/Barinas.txt";
        default:      return NULL;
    }
}

/* ---- Main parser ---- */

Status reader_load_economy(const char* filename, Economy* economy)
{
    FILE* f;
    char  line[MAX_LINE];
    double val;
    char   str_buf[WORD_SIZE];

    if (!filename || !economy) return ERROR;

    f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "[Reader] Error: cannot open '%s'\n", filename);
        return ERROR;
    }

    while (fgets(line, MAX_LINE, f)) {
        char* t = trim(line);

        /* Skip comments and empty lines */
        if (t[0] == '#' || t[0] == '\0') continue;

        /* Name: <value> */
        if (sscanf(t, "Name: %255[^\n]", str_buf) == 1) {
            economy_set_name(economy, str_buf);
        }
        /* Stabilization_speed: <value> */
        else if (sscanf(t, "Stabilization_speed: %lf", &val) == 1) {
            economy_set_stabilization_speed(economy, val);
        }
        /* Inflation_current: <value> */
        else if (sscanf(t, "Inflation_current: %lf", &val) == 1) {
            economy_set_inflation_current(economy, val);
        }
        /* Inflation_future: <value> */
        else if (sscanf(t, "Inflation_future: %lf", &val) == 1) {
            economy_set_inflation_future(economy, val);
        }
        /* Price_food: <value> */
        else if (sscanf(t, "Price_food: %lf", &val) == 1) {
            economy_set_price_food(economy, val);
        }
        /* Factor_celiaco: <value> */
        else if (sscanf(t, "Factor_celiaco: %lf", &val) == 1) {
            economy_set_factor_celiaco(economy, val);
        }
        /* PIB: YYYY-MM <value> */
        else if (strncmp(t, "PIB:", 4) == 0) {
            char date_buf[16];
            if (sscanf(t + 4, " %15s %lf", date_buf, &val) == 2) {
                economy_push_gdp(economy, val);
            }
        }
    }

    /* Derive certified price from factor if not set explicitly */
    if (economy_get_price_food(economy) > 0.0 && economy_get_factor_celiaco(economy) > 1.0) {
        Price cert = economy_get_price_food(economy) * economy_get_factor_celiaco(economy);
        economy_set_price_foodCert(economy, cert);
    }

    fclose(f);
    return OK;
}