//
// Created by Niklas Hartinger on 21.12.2020.
//

#ifndef TSP_SELECTION_H
#define TSP_SELECTION_H

#include <population/Population.h>


/*!
 * Survival of the fittest selection.
 * p_old and p_new must have equal size.
 * @param p_old - the old generation
 * @param p_new - the new generation
 * @return population with the fittest individuals
 */
Population selection_sotf(Population &p_old, Population &p_new);

/*!
 * Survival of the fittest selection. If input populations do
 * not contain enough unique individuals, the missing ones are created.
 * p_old and p_new must have equal size.
 * @param p_old - the old generation
 * @param p_new - the new generation
 * @return distinct population with the fittest individuals
 */
Population selection_sotf_distinct(Population &p_old, Population &p_new);

#endif //TSP_SELECTION_H
