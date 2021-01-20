//
// Created by Niklas Hartinger on 05.01.2021.
//

#ifndef TSP_SIMULATOR_H
#define TSP_SIMULATOR_H

#include <string>
#include <vector>
#include <algorithm>
#include <population/Population.h>
#include <util/read_cities.h>

enum Marriage_Algorithm {
    Roulette,
    Roulette_Reversed
};

enum Crossover_Algorithm {
    Partially_Matched,
    Order,
    Cycle_all_cycles,
    Cycle_one_cycle,
    Edge_Recombination,
};

enum Mutation_Algorithm {
    Delete_Shift
};

enum Selection_Algorithm {
    SOFT,
};


class Simulator {
private:

    int generations;
    int simulations = 0;
    int mutation_rate;
    int start_city_idx;
    int population_size;
    int number_cities;
    std::vector<int> indexes;
    std::vector<std::vector<int>> distances;
    Crossover_Algorithm crossover_algo;
    Marriage_Algorithm marriage_algo;
    Mutation_Algorithm mutation_algo;
    Selection_Algorithm selection_algo;
    Population population;

public:

    Simulator(
            const std::string &position_path, const std::string &distance_path, const int start_city,
            int number_cities, int population_size, int generations, int mutation_rate,
            Crossover_Algorithm crossover, Marriage_Algorithm marriage, Mutation_Algorithm mutation, Selection_Algorithm selection);

    /*!
     * Simulates once
     * @return tuple[0] = lowest fitness, tuple[1] = highest fitness, tuple[2] = average fitness
     */
    // TODO: also return the best individual
    std::tuple<int, int, int> simulate();

    /*!
     * Return the best (highest fitness) individual chromosome.
     * The start city is already inserted to the front and to the end.
     * @return chromosome
     */
    std::vector<int> best_individual();

    bool finished() const;
};

#endif //TSP_SIMULATOR_H
