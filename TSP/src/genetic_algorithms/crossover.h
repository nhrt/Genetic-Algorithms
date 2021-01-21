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
#include <limits>

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
bool cycle_crossover_all_cycles(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

/*!
 * Randomly identify one cycle between the first and second parent.
 * This cycle is used to copy the chromosome values of parent 1 to child 1 and of parent 2 to child 2.
 * The other values are used to crossover the parents, meaning that parent 1 passes on the values to child 2 and parent 2 to child 1.
 * @param p1 first parent individual
 * @param p2 second parent individual
 * @param c1 first child individual
 * @param c2 second child individual
 * @return true
 */
bool cycle_crossover_one_cycle(Individual &p1, Individual &p2, Individual &c1, Individual &c2);

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
