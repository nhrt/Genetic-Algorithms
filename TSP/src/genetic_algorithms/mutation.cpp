//
// Created by Niklas Hartinger on 16.12.2020.
//

#include "mutation.h"

bool mutation_delete_shift(Individual &individual, int percentage) {
    bool mutate = rand() % 100 < percentage;

    if (mutate) {
        int position_a = rand() % (individual.get_size() - 1);
        int position_b;
        do {
            position_b = rand() % (individual.get_size() - position_a) + position_a;
        } while (position_a == position_b);

        shift_left(individual.get_chromosome(), position_a, position_b);
    }

    return mutate;
}