//
// Created by Niklas Hartinger on 16.12.2020.
//

#ifndef TSP_MARRIAGE_H
#define TSP_MARRIAGE_H

#include <population/Population.h>
#include <individual/Individual.h>
#include <util/Random_Number_Generator.h>
/*!
 * Calculates two different parents based on the reciprocal fitness of the individuals.
 * @param population
 * @param recalculate_population_fitness - when the population fitness value inside the population is not up to date set to true
 * @return two parent indexes for usage inside the popualtion.
 */
std::pair<int, int> marriage_roulette(Population &population, bool recalculate_population_fitness);

/*!
 * Calculates two different parents based on the reversed fitness of the individuals.
 * @param population
 * @param recalculate_population_fitness - when the population fitness value inside the population is not up to date set to true
 * @return two parent indexes for usage inside the popualtion.
 */
std::pair<int, int> marriage_roulette_reversed(Population &population, bool recalculate_population_fitness);

#endif //TSP_MARRIAGE_H
