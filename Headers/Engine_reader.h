/**
 * @brief Engine_reader - parses .txt data files to populate Economy
 *
 * @file        Engine_reader.h
 * @author      Rafael
 * @version     1.0
 * @date        4-4-2026
 * @copyright   GNU Public License
 */
#ifndef ENGINE_READER_H
#define ENGINE_READER_H

#include "../Headers/types.h"
#include "../Headers/Economy.h"

/**
 * @brief Reads an economy data file and populates the Economy struct
 *
 * File format:
 *   # comments
 *   Name: <city_name>
 *   Stabilization_speed: <double>
 *   Inflation_current: <double>
 *   Inflation_future: <double>
 *   Price_food: <double>
 *   Factor_celiaco: <double>
 *   PIB: YYYY-MM <value>
 *
 * @param filename  Path to .txt file
 * @param economy   Economy to populate
 * @return OK on success, ERROR on failure
 */
Status reader_load_economy(const char* filename, Economy* economy);

/**
 * @brief Returns the .txt file path for a given city choice
 */
const char* reader_get_filename(EcoChoose city);

#endif /* ENGINE_READER_H */