//
// Created by Niklas Hartinger on 14.12.2020.
//

#ifndef TSP_UTILITY_H
#define TSP_UTILITY_H

#define MAX_COSTS 59 * 2500 // Value for the example rating function

#include <numeric>
#include <unordered_set>
#include <iostream>
#include <vector>

/*!
 * Calculates the rating of a chromosome
 * @param idx_start - index of start city
 * @param chromosome - chromosome of individual
 * @param distances - distance matrix
 * @return rating
 */
double rating(int idx_start, std::vector<int> &chromosome, std::vector<std::vector<int>> &distances);

/*!
 * Calculates the fitness of a chromosome
 * @param rating - rating of the individual
 * @return fitness
 */
double fitness(double rating);

/*!
 * Returns the index of a found duplicate. The index is the position of the second one.
 * @param chromosome
 * @return index < 0 when no duplicates in chromosome
 */
int find_duplicate(std::vector<int> &chromosome);

/*!
 * Swaps two chromosome values inside a individual
 * @param i - vector chromosome
 * @param idx_a - first value
 * @param idx_b - second value
 */
void swap_chromosome(std::vector<int> &i, int idx_a, int idx_b);

/*!
 * Takes a vector, stores a value on idx_start, shifts the right side of this vector until idx_end one position to the left.
 * Writes the stored value in the now empty space at position idx_end.
 * @param vector
 * @param idx_start - start of left shift
 * @param idx_end - end of left shift
 */
void shift_left(std::vector<int> &vector, int idx_start, int idx_end);

/*!
 * Calculates the costs of the individual
 * @param idx_start - index of start city
 * @param chromosome - chromosome of individual
 * @param distances - distance matrix
 * @return costs
 */
int cost_function(int idx_start, std::vector<int> &chromosome, std::vector<std::vector<int>> &distances);

#endif //TSP_UTILITY_H
