/**
 * @brief Celiac Economy Simulator
 *
 * @file        main.c
 * @author      Rafael
 * @version     1.1
 * @date        10-4-2026
 * @copyright   GNU Public License
 */
#include "Headers/Engine.h"
#include "Headers/Engine_reader.h"
#include "Headers/Graphic_engine.h"

int main()
{
    Engine*        engine = NULL;
    GraphicEngine* ge     = NULL;
    int            city_choice, class_choice;
    EcoChoose      city;
    SocialClass    sclass;
    const char*    filename;
    int            seed;

    /* ---- 1. Welcome ---- */
    printf("\033[2J\033[H");
    printf("\n");
    printf("  ============================================\n");
    printf("  ||  SIMULADOR DE ECONOMIA CELIACA         ||\n");
    printf("  ||  Como afecta la clase social y la      ||\n");
    printf("  ||  inflacion a la esperanza de vida      ||\n");
    printf("  ||  de un paciente celiaco?               ||\n");
    printf("  ============================================\n\n");

    /* ---- 2. City ---- */
    printf("  Selecciona una ciudad:\n");
    printf("    1. Madrid     (Espana - economia estable)\n");
    printf("    2. Almeria    (Espana - economia menor)\n");
    printf("    3. Caracas    (Venezuela - alta inflacion)\n");
    printf("    4. Barinas    (Venezuela - zona rural)\n");
    printf("\n  > ");
    if (scanf("%d", &city_choice) != 1 || city_choice < 1 || city_choice > 4) {
        printf("  Seleccion invalida. Usando Madrid.\n");
        city_choice = 1;
    }
    city = (EcoChoose)city_choice;

    /* ---- 3. Class ---- */
    printf("\n  Selecciona clase social del paciente:\n");
    printf("    1. Clase alta   (poder adquisitivo: %.0f EUR/mes)\n", POWER_UPPER);
    printf("    2. Clase media  (poder adquisitivo: %.0f EUR/mes)\n", POWER_MIDDLE);
    printf("    3. Clase baja   (poder adquisitivo: %.0f EUR/mes)\n", POWER_LOWER);
    printf("\n  > ");
    if (scanf("%d", &class_choice) != 1 || class_choice < 1 || class_choice > 3) {
        printf("  Seleccion invalida. Usando clase media.\n");
        class_choice = 2;
    }
    sclass = (SocialClass)class_choice;

    /* ---- 4. Init engine ---- */
    engine = engine_create();
    if (!engine) {
        fprintf(stderr, "Error: no se pudo crear el engine.\n");
        return 1;
    }

    filename = reader_get_filename(city);
    if (!filename || reader_load_economy(filename, engine_get_economy(engine)) == ERROR) {
        fprintf(stderr, "Error: no se pudo cargar '%s'.\n",
                filename ? filename : "(null)");
        engine_destroy(engine);
        return 1;
    }

    patient_set_name(engine_get_patient(engine), "Paciente");
    patient_set_social_class(engine_get_patient(engine), sclass);

    switch (sclass) {
        case UPPER_CLASS:
            patient_set_stock_foodCert(engine_get_patient(engine), STOCK_CERT_UPPER);
            patient_set_stock_food(engine_get_patient(engine), STOCK_FOOD_UPPER);
            break;
        case LOWER_CLASS:
            patient_set_stock_foodCert(engine_get_patient(engine), STOCK_CERT_LOWER);
            patient_set_stock_food(engine_get_patient(engine), STOCK_FOOD_LOWER);
            break;
        default:
            patient_set_stock_foodCert(engine_get_patient(engine), STOCK_CERT_MIDDLE);
            patient_set_stock_food(engine_get_patient(engine), STOCK_FOOD_MIDDLE);
            break;
    }

    /* ---- 5. Graphic engine ---- */
    ge = graphic_engine_create(engine);
    if (!ge) {
        fprintf(stderr, "Error: no se pudo crear el graphic engine.\n");
        engine_destroy(engine);
        return 1;
    }

    /* ---- 6. Simulation loop ---- */
    seed = (int)time(NULL);

    while (1) {
        graphic_engine_render(ge);

        if (patient_get_health(engine_get_patient(engine)) <= MIN_HEALTH) {
            printf("\n  %s*** El paciente ha fallecido. ***%s\n",
                   "\033[1;31m", "\033[0m");
            printf("  Presiona Enter para ver el resumen...");
            getchar(); getchar();
            break;
        }

        PlayerAction action = graphic_engine_prompt_action(ge);
        if ((int)action == -1) break;

        seed += 17;
        if (engine_next_month(engine, action, seed) == ERROR) {
            printf("  Error en la simulacion.\n");
            break;
        }
    }

    /* ---- 7. Summary ---- */
    graphic_engine_render_summary(ge);

    /* ---- 8. Cleanup ---- */
    graphic_engine_destroy(ge);
    engine_destroy(engine);

    return 0;
}