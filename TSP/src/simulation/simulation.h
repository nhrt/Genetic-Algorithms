//
// Created by Niklas Hartinger on 29.12.2020.
//

#ifndef TSP_SIMULATION_H
#define TSP_SIMULATION_H

#include <string>
#include <util/read_cities.h>

enum Marriage_Algorithms {
    Roulette
};

enum Crossover_Algorithms {
    Partially_Matched,
    Order,
    Cycle_all_cycles,
    Cycle_one_cycle,
    Edge_Recombination
};

enum Mutation_Algorithms {
    Delete_Shift
};

enum Selection_Algorithms {
    SOFT
};

int simulate(const std::string &city_path, const std::string &distance_path, const std::string &start_city,
             int number_cities, int population_size, int epochs, int mutation_rate,
             Crossover_Algorithms crossover, Marriage_Algorithms marriage, Mutation_Algorithms mutation,
             Selection_Algorithms selection
);

#endif //TSP_SIMULATION_H
