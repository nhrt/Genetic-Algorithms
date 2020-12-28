//
// Created by Niklas Hartinger on 15.12.2020.
//

#ifndef TSP_CROSSOVER_H
#define TSP_CROSSOVER_H

#include <utility>
#include <genetic_algorithms/utility.h>
#include <individual/Individual.h>
#include <unordered_set>
#include <iostream>
#include <util/Random_Number_Generator.h>

#define DUPLICATE_FLAG -1
#define EDGE_TO_START -1

/*!
 * Performs a partially matched crossover.
 * All individuals need to have the same chromosome length. Mininmum chromosome length is 3.
 * @param p1 - first parent => first chromosome input
 * @param p2 - second parent => second chromosome input
 * @param c1 - first child => first chromosome output
 * @param c2 - second child => second chromosome output
 * @return true = success, false = no success => different chromosome length or too short.
 */
bool partially_matched_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

/*!
 * Performs a order crossover.
 * All individuals need to have the same chromosome length. Minimum Chromosome length is 3.
 * @param p1 - first parent => first chromosome input
 * @param p2 - second parent => second chromosome input
 * @param c1 - first child => first chromosome output
 * @param c2 - second child => second chromosome output
 * @return true = success, false = no success => different chromosome length or too short.
 */
bool order_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

bool cycle_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

bool uniform_order_based_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

/*!
 * Performs an edge recombination crossover. This algorithm is completely edge oriented.
 * Position of each city in chromosome is not relevant. It tries to create children with the highest amount of parent edges.
 * It is possible, that this function creates two equal children.
 * @param p1 - first parent => first chromosome input
 * @param p2 - second parent => second chromosome input
 * @param c1 - first child => first chromosome output
 * @param c2 - second child => second chromosome output
 * @return true = success, false = no success => different chromosome length or too short.
 */
bool edge_recombination_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

#endif //TSP_CROSSOVER_H
