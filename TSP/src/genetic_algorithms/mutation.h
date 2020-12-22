//
// Created by Niklas Hartinger on 16.12.2020.
//

#ifndef TSP_MUTATION_H
#define TSP_MUTATION_H

#include <individual/Individual.h>
#include <genetic_algorithms/utility.h>

/*!
 * Performs a left shift mutation.
 * Creates two random indexes. Stores value on the smaller index1. Shifts the vector from the right side
 * of index1 one position to the left until index2 is reached. Stored value will be placed inside now empty position index2.
 * @param individual - individual that will be mutated
 * @param percentage - mutation probability. Between 0 and 100.
 * @return true = individual got mutated, false = individual did not get mutated
 */
bool mutation_delete_shift(Individual &individual, int percentage=5);

#endif //TSP_MUTATION_H
