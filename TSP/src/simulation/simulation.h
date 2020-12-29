//
// Created by Niklas Hartinger on 29.12.2020.
//

#ifndef TSP_SIMULATION_H
#define TSP_SIMULATION_H

#include <string>
#include <util/read_cities.h>

int simulate(const std::string &city_path, const std::string &distance_path, const std::string &start_city,
             int number_cities, int population_size, int epochs, int mutation_rate,
             int crossover_algorithm, int marriage_algorithm, int mutation_algorithm, int selection_algorithm
);

#endif //TSP_SIMULATION_H
