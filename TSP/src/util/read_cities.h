//
// Created by Niklas Hartinger on 14.12.2020.
//

#ifndef TSP_READ_CITIES_H
#define TSP_READ_CITIES_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define CONTENT_START_INDEX_DISTANCES 2
#define CONTENT_START_INDEX_NAMES 2

/*!
 * Reads a file containing the distances between cities and stores the information in a 2d-Vector.
 * Format must be in matrix style.
 * @param file - path
 * @param distances - result
 * @param size - number of cities
 * @return true = success, false = no success
 */
bool read_distances(const std::string &file, std::vector<std::vector<int>> &distances, int size = 48);

/*!
 * Reads a file containing the city position and stores the indexes of the cities [0...n-1] and stores them in a vector.
 * @param file - path
 * @param names - result
 * @param size - number of cities
 * @return ture = success, false = no success
 */
bool read_indexes(const std::string &file, std::vector<int> &indexes, int size = 48);

#endif //TSP_READ_CITIES_H
