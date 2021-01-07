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
    SOFT_Reversed
};


class Simulator {
private:

    int generations;
    int simulations = 0;
    int mutation_rate;
    int start_city_idx;
    int population_size;
    int number_cities;
    std::vector<std::string> cities;
    std::vector<std::vector<int>> distances;
    Crossover_Algorithm crossover_algo;
    Marriage_Algorithm marriage_algo;
    Mutation_Algorithm mutation_algo;
    Selection_Algorithm selection_algo;
    Population population;

public:

    Simulator(
            const std::string &city_path, const std::string &distance_path, const std::string &start_city,
            int number_cities, int population_size, int generations, int mutation_rate,
            Crossover_Algorithm crossover, Marriage_Algorithm marriage, Mutation_Algorithm mutation,
            Selection_Algorithm selection)
            : generations(generations), mutation_rate(mutation_rate), population_size(population_size),
              number_cities(number_cities) {

        if (!read_distances(distance_path, distances)) {
            std::cerr << "Distance-File can not be opened" << std::endl;
            exit(1);
        }

        if (!read_names(city_path, cities, number_cities)) {
            std::cerr << "Cities-Name-File can not be opened" << std::endl;
            exit(2);
        }

        auto it = std::find(cities.begin(), cities.end(), start_city);
        if (it == cities.end()) {
            std::cerr << "Start city is not part of the cities" << std::endl;
            exit(3);
        }
        start_city_idx = std::distance(cities.begin(), it);

        if (!parameters_valid(marriage, selection)) {
            std::cerr << "Parameter values are not valid. Check if you used reversed or not revered only!" << std::endl;
            exit(4);
        }

        crossover_algo = crossover;
        marriage_algo = marriage;
        mutation_algo = mutation;
        selection_algo = selection;

        if(selection_algo == Selection_Algorithm::SOFT_Reversed){
            population = Population(population_size, number_cities-1, start_city_idx, rating_reversed, fitness, distances);
        }else{
            population = Population(population_size, number_cities-1, start_city_idx, rating, fitness, distances);
        }
    }

    /*!
     * Checks if the chosen selection and marriage algorithms are fitting together.
     * @param marriage
     * @param selection
     * @return
     */
    static bool parameters_valid(Marriage_Algorithm marriage, Selection_Algorithm selection);

    /*!
     * Simulates once
     * @return tuple[0] = highest distance, tuple[1] = lowest distance, tuple[2] = average distance
     */
    std::tuple<int, int, int> simulate();

    bool finished() const;
};

#endif //TSP_SIMULATOR_H
