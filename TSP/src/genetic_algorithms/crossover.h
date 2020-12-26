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

/*!
 * Identify all cycles between the first and second parent. Afterwards, form the children by copying the values of the parents to the children for each cycle, alternating to whom the values get copied.
 * If only one cycle is identified, no crossover takes place and the children will consist of exactly the same chromosomes like their parents.
 * Example: Cycle 1 -> p1 to c1, p2 to c2 - Cycle 2 -> p1 to c2, p2 to c1 - Cycle 3 -> p1 to c1, p2 to c2 - Cycle 4 -> ...
 * Only works when both parents' chromosomes consist of the same set of values. Otherwise a certain chromosome value of the second parent cannot be found in the chromosome of the first parent.
 * For further explanation, see: https://www.rubicite.com/Tutorials/GeneticAlgorithms/CrossoverOperators/CycleCrossoverOperator.aspx
 * @param p1 first parent individual
 * @param p2 second parent individual
 * @param c1 first child individual
 * @param c2 second child individual
 * @return true
 */
bool cycle_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

bool uniform_order_based_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

bool edge_recombination_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

#endif //TSP_CROSSOVER_H
