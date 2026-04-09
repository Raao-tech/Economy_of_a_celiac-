/**
 * @brief Graphic_engine - text-based rendering of the simulation state
 *
 * Renders a visual dashboard in the terminal showing economy data,
 * patient health, stock levels, and prompts for player action.
 *
 * @file        Graphic_engine.h
 * @author      Rafael
 * @version     1.0
 * @date        10-4-2026
 * @copyright   GNU Public License
 */
#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "../Headers/Engine.h"

typedef struct _GraphicEngine GraphicEngine;

/* ---- Create / Destroy ---- */
GraphicEngine* graphic_engine_create(Engine* engine);
Status         graphic_engine_destroy(GraphicEngine* ge);

/**
 * @brief Renders the full dashboard to the terminal
 *
 * Shows: month/year, economy panel, patient panel,
 * health bar, stock indicators, and price comparison.
 */
Status graphic_engine_render(GraphicEngine* ge);

/**
 * @brief Prompts the user for the next action
 *
 * @return The PlayerAction chosen, or -1 to quit
 */
PlayerAction graphic_engine_prompt_action(GraphicEngine* ge);

/**
 * @brief Shows the game-over / end-of-simulation summary
 */
Status graphic_engine_render_summary(GraphicEngine* ge);

#endif /* GRAPHIC_ENGINE_H */