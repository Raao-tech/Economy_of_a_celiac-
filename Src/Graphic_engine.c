/**
 * @brief Graphic_engine - terminal-based visual dashboard
 *
 * @file        Graphic_engine.c
 * @author      Rafael
 * @version     1.1
 * @date        10-4-2026
 * @copyright   GNU Public License
 */
#include "../Headers/Graphic_engine.h"

/* ---- ANSI color codes ---- */
#define C_RESET   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_DIM     "\033[2m"
#define C_RED     "\033[31m"
#define C_GREEN   "\033[32m"
#define C_YELLOW  "\033[33m"
#define C_BLUE    "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN    "\033[36m"
#define C_WHITE   "\033[37m"
#define C_BG_RED  "\033[41m"

#define PANEL_W  60
#define BAR_LEN  30

struct _GraphicEngine {
    Engine* engine;
};

/* ---- Create / Destroy ---- */

GraphicEngine* graphic_engine_create(Engine* engine)
{
    GraphicEngine* ge;
    if (!engine) return NULL;
    ge = (GraphicEngine*)malloc(sizeof(GraphicEngine));
    if (!ge) return NULL;
    ge->engine = engine;
    return ge;
}

Status graphic_engine_destroy(GraphicEngine* ge)
{
    if (!ge) return ERROR;
    free(ge);
    return OK;
}

/* ---- Internal helpers ---- */

static const char* month_name(int m)
{
    static const char* names[] = {
        "???", "Enero", "Febrero", "Marzo", "Abril",
        "Mayo", "Junio", "Julio", "Agosto",
        "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };
    if (m < 1 || m > 12) return names[0];
    return names[m];
}

static const char* class_name(SocialClass sc)
{
    switch (sc) {
        case UPPER_CLASS:  return "Alta";
        case MIDDLE_CLASS: return "Media";
        case LOWER_CLASS:  return "Baja";
        default:           return "Desconocida";
    }
}

static void print_line(char left, char fill, char right, int width)
{
    printf("%s%c", C_CYAN, left);
    for (int i = 0; i < width; i++) printf("%c", fill);
    printf("%c%s\n", right, C_RESET);
}

static void print_row(const char* content)
{
    int len = 0;
    const char* p = content;
    int in_escape = 0;
    while (*p) {
        if (*p == '\033') in_escape = 1;
        else if (in_escape && ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))) in_escape = 0;
        else if (!in_escape) len++;
        p++;
    }
    int pad = PANEL_W - len;
    if (pad < 0) pad = 0;
    printf("%s|%s %s%*s%s|%s\n", C_CYAN, C_RESET, content, pad, "", C_CYAN, C_RESET);
}

static void print_empty_row(void)
{
    printf("%s|%s%*s%s|%s\n", C_CYAN, C_RESET, PANEL_W + 1, "", C_CYAN, C_RESET);
}

static void print_health_bar(double health)
{
    int filled = (int)((health / MAX_HEALTH) * BAR_LEN);
    if (filled < 0) filled = 0;
    if (filled > BAR_LEN) filled = BAR_LEN;

    const char* color;
    if (health > 66)      color = C_GREEN;
    else if (health > 33) color = C_YELLOW;
    else                  color = C_RED;

    /* Build bar: filled=#, empty=- (no ANSI per char to avoid overflow) */
    char bar[BAR_LEN + 1];
    for (int i = 0; i < BAR_LEN; i++)
        bar[i] = (i < filled) ? '#' : '-';
    bar[BAR_LEN] = '\0';

    char buf[256];
    sprintf(buf, "  Salud: %s[%s] %s%.0f%%%s",
            color, bar, C_BOLD, health, C_RESET);
    print_row(buf);
}

static void print_stock_indicator(const char* label, int stock, const char* icon)
{
    char buf[256];
    int pos = 0;

    pos += sprintf(buf + pos, "  %s: ", label);
    int show = stock > 10 ? 10 : stock;
    for (int i = 0; i < show; i++)
        pos += sprintf(buf + pos, "%s", icon);
    if (stock > 10)
        pos += sprintf(buf + pos, " (+%d)", stock - 10);
    if (stock == 0)
        pos += sprintf(buf + pos, " %s(vacio)%s", C_RED, C_RESET);

    print_row(buf);
}

/* ================================================================
 *  Render
 * ================================================================ */

Status graphic_engine_render(GraphicEngine* ge)
{
    Engine*   eng;
    Economy*  eco;
    Patient*  pat;
    char buf[512];

    if (!ge || !ge->engine) return ERROR;

    eng = ge->engine;
    eco = engine_get_economy(eng);
    pat = engine_get_patient(eng);
    if (!eco || !pat) return ERROR;

    printf("\033[2J\033[H");

    /* ---- Title ---- */
    print_line('+', '=', '+', PANEL_W + 1);
    sprintf(buf, "%s  SIMULADOR CELIACO  %s|%s  %s %d  %s",
            C_BOLD, C_RESET, C_RESET,
            month_name(engine_get_month(eng)),
            engine_get_year(eng), C_RESET);
    print_row(buf);
    print_line('+', '=', '+', PANEL_W + 1);

    /* ---- Event log from last month ---- */
    const char* evt = engine_get_last_event(eng);
    if (evt && evt[0] != '\0') {
        print_empty_row();
        sprintf(buf, "%s  -- Resumen del mes anterior --%s", C_DIM, C_RESET);
        print_row(buf);

        /* Print each line of the event log */
        char evt_copy[512];
        strncpy(evt_copy, evt, sizeof(evt_copy) - 1);
        evt_copy[sizeof(evt_copy) - 1] = '\0';

        char* line = strtok(evt_copy, "\n");
        while (line) {
            /* Color based on event type */
            const char* c = C_WHITE;
            if (line[0] == '[' && line[1] == '+')  c = C_GREEN;
            if (line[0] == '[' && line[1] == '!')  c = C_YELLOW;
            if (line[0] == '[' && line[1] == '-')  c = C_DIM;
            if (strstr(line, "!!!"))               c = C_RED;
            if (strstr(line, "CONTAMINACION"))     c = C_RED;
            if (strstr(line, "OK"))                c = C_GREEN;
            if (strstr(line, "sin contaminacion")) c = C_YELLOW;

            sprintf(buf, "  %s%s%s", c, line, C_RESET);
            print_row(buf);
            line = strtok(NULL, "\n");
        }
        print_line('|', '-', '|', PANEL_W + 1);
    }

    /* ---- Economy panel ---- */
    print_empty_row();
    sprintf(buf, "%s  >> ECONOMIA: %s%s",
            C_BLUE,
            economy_get_name(eco) ? economy_get_name(eco) : "???",
            C_RESET);
    print_row(buf);
    print_line('|', '-', '|', PANEL_W + 1);

    sprintf(buf, "  Inflacion actual:  %s%.2f%%%s",
            C_YELLOW, economy_get_inflation_current(eco), C_RESET);
    print_row(buf);

    double price_food = economy_get_price_food(eco);
    double price_cert = economy_get_price_foodCert(eco);
    double power      = patient_get_purchasing_power(pat);

    sprintf(buf, "  Precio comida:     %s%.2f EUR%s",
            C_WHITE, price_food, C_RESET);
    print_row(buf);

    const char* cert_color = (price_cert <= power) ? C_GREEN : C_RED;
    sprintf(buf, "  Precio cert(GF):   %s%.2f EUR%s  (x%.1f)",
            cert_color, price_cert, C_RESET,
            economy_get_factor_celiaco(eco));
    print_row(buf);

    /* ---- Patient panel ---- */
    print_empty_row();
    sprintf(buf, "%s  >> PACIENTE: %s%s  [Clase %s]",
            C_MAGENTA,
            patient_get_name(pat) ? patient_get_name(pat) : "???",
            C_RESET,
            class_name(patient_get_social_class(pat)));
    print_row(buf);
    print_line('|', '-', '|', PANEL_W + 1);

    print_health_bar(patient_get_health(pat));

    sprintf(buf, "  Poder adquisitivo: %s%.0f EUR/mes%s",
            (power >= price_cert) ? C_GREEN : C_RED,
            power, C_RESET);
    print_row(buf);

    print_stock_indicator("Stock cert  ", patient_get_stock_foodCert(pat), "O");
    print_stock_indicator("Stock normal", patient_get_stock_food(pat), "o");

    /* ---- Alerts ---- */
    if (power < price_food) {
        print_empty_row();
        sprintf(buf, "%s%s  !! NO PUEDES PERMITIRTE NINGUNA COMIDA !!%s",
                C_BG_RED, C_BOLD, C_RESET);
        print_row(buf);
    } else if (power < price_cert) {
        print_empty_row();
        sprintf(buf, "%s  ! Solo puedes comprar comida NO certificada%s",
                C_YELLOW, C_RESET);
        print_row(buf);
    }

    print_empty_row();
    print_line('+', '=', '+', PANEL_W + 1);

    return OK;
}

/* ================================================================
 *  Prompt action
 * ================================================================ */

PlayerAction graphic_engine_prompt_action(GraphicEngine* ge)
{
    int choice;
    double power, price_cert, price_food;
    Economy* eco;
    Patient* pat;

    if (!ge || !ge->engine) return -1;

    eco = engine_get_economy(ge->engine);
    pat = engine_get_patient(ge->engine);
    power      = patient_get_purchasing_power(pat);
    price_cert = economy_get_price_foodCert(eco);
    price_food = economy_get_price_food(eco);

    printf("\n");
    printf("  %sQue haces este mes?%s\n", C_BOLD, C_RESET);
    printf("  %s1%s. Comprar certificada   (%s%.2f EUR%s)%s\n",
           C_GREEN, C_RESET,
           (power >= price_cert) ? C_GREEN : C_RED,
           price_cert, C_RESET,
           (power < price_cert) ? "  [no alcanza]" : "");
    printf("  %s2%s. Comprar NO certificada (%s%.2f EUR%s)\n",
           C_YELLOW, C_RESET,
           (power >= price_food) ? C_GREEN : C_RED,
           price_food, C_RESET);
    printf("  %s3%s. No comprar (sobrevivir con stock)\n",
           C_RED, C_RESET);
    printf("  %s0%s. Salir\n\n",
           C_DIM, C_RESET);
    printf("  > ");

    if (scanf("%d", &choice) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return ABSTAIN;
    }

    switch (choice) {
        case 1:  return BUY_CERTIFIED;
        case 2:  return BUY_NONCERTIFIED;
        case 3:  return ABSTAIN;
        case 0:  return -1;
        default: return ABSTAIN;
    }
}

/* ================================================================
 *  Summary
 * ================================================================ */

Status graphic_engine_render_summary(GraphicEngine* ge)
{
    Engine*  eng;
    Patient* pat;
    Economy* eco;

    if (!ge || !ge->engine) return ERROR;

    eng = ge->engine;
    pat = engine_get_patient(eng);
    eco = engine_get_economy(eng);

    printf("\033[2J\033[H");
    print_line('+', '=', '+', PANEL_W + 1);

    char buf[512];
    sprintf(buf, "%s  RESUMEN DE SIMULACION%s", C_BOLD, C_RESET);
    print_row(buf);
    print_line('+', '=', '+', PANEL_W + 1);
    print_empty_row();

    double health = patient_get_health(pat);

    if (health <= MIN_HEALTH) {
        sprintf(buf, "%s  RESULTADO: El paciente ha fallecido.%s", C_RED, C_RESET);
    } else {
        sprintf(buf, "%s  RESULTADO: El paciente ha sobrevivido.%s", C_GREEN, C_RESET);
    }
    print_row(buf);
    print_empty_row();

    sprintf(buf, "  Ciudad:       %s",
            economy_get_name(eco) ? economy_get_name(eco) : "???");
    print_row(buf);
    sprintf(buf, "  Clase social: %s", class_name(patient_get_social_class(pat)));
    print_row(buf);
    sprintf(buf, "  Salud final:  %.1f / %.0f", health, MAX_HEALTH);
    print_row(buf);
    sprintf(buf, "  Mes final:    %s %d",
            month_name(engine_get_month(eng)), engine_get_year(eng));
    print_row(buf);
    sprintf(buf, "  Precio cert final: %.2f EUR", economy_get_price_foodCert(eco));
    print_row(buf);
    sprintf(buf, "  Inflacion final:   %.2f%%", economy_get_inflation_current(eco));
    print_row(buf);

    print_empty_row();
    sprintf(buf, "%s  La clase social y la inflacion determinan%s", C_DIM, C_RESET);
    print_row(buf);
    sprintf(buf, "%s  cuantos meses puede sobrevivir un celiaco.%s", C_DIM, C_RESET);
    print_row(buf);
    print_empty_row();
    print_line('+', '=', '+', PANEL_W + 1);
    printf("\n");

    return OK;
}