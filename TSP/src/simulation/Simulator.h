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

enum Marriage_Algorithms {
    Roulette,
    Roulette_Reversed
};

enum Crossover_Algorithms {
    Partially_Matched,
    Order,
    Cycle_all_cycles,
    Cycle_one_cycle,
    Edge_Recombination,
};

enum Mutation_Algorithms {
    Delete_Shift
};

enum Selection_Algorithms {
    SOFT,
    SOFT_Reversed
};


class Simulator {
private:

    int epochs;
    int simulations = 0;
    int mutation_rate;
    int start_city_idx;
    int population_size;
    int number_cities;
    std::vector<std::string> cities;
    std::vector<std::vector<int>> distances;
    Crossover_Algorithms crossover_algo;
    Marriage_Algorithms marriage_algo;
    Mutation_Algorithms mutation_algo;
    Selection_Algorithms selection_algo;
    Population population;

public:

    Simulator(
            const std::string &city_path, const std::string &distance_path, const std::string &start_city,
            int number_cities, int population_size, int epochs, int mutation_rate,
            Crossover_Algorithms crossover, Marriage_Algorithms marriage, Mutation_Algorithms mutation,
            Selection_Algorithms selection)
            : epochs(epochs), mutation_rate(mutation_rate), population_size(population_size),
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

        if(selection_algo == Selection_Algorithms::SOFT_Reversed){
            population = Population(population_size, number_cities-1, start_city_idx, rating_reversed, fitness, distances);
        }else{
            population = Population(population_size, number_cities-1, start_city_idx, rating, fitness, distances);
        }
    }

    static bool parameters_valid(Marriage_Algorithms marriage, Selection_Algorithms selection) {
        return (marriage == Marriage_Algorithms::Roulette_Reversed && selection == Selection_Algorithms::SOFT_Reversed) ||
                (marriage == Marriage_Algorithms::Roulette && selection == Selection_Algorithms::SOFT);
    }

    /*!
     * Simulates once
     * @return tuple[0] = highest distance, tuple[1] = lowest distance, tuple[2] = average distance
     */
    std::tuple<int, int, int> simulate();

    bool finished() const;
};

#endif //TSP_SIMULATOR_H
