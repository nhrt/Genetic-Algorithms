//
// Created by Niklas Hartinger on 16.12.2020.
//

#include "marriage.h"


std::pair<int, int> marriage_roulette(Population &population, bool recalculate_population_fitness) {
    if (recalculate_population_fitness) {
        population.calc_population_fitness();
    }
    std::pair<int, int> pair = std::make_pair(-1, -1);
    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    int value_p1 = rng.random(population.get_last_calculates_population_fitness());
    int value_p2;
    do {
        value_p2 = rng.random(population.get_last_calculates_population_fitness());
    } while (value_p1 == value_p2);

    int value = 0;
    int current_idx = 0;
    for (auto &it : population.get_individuals()) {
        value += (int) it.get_last_calculates_fitness();
        if (value_p1 <= value && pair.first < 0) {
            pair.first = current_idx;
        }
        if (value_p2 <= value && pair.second < 0) {
            pair.second = current_idx;
        }
        current_idx++;
    }

    if (pair.first == pair.second) {
        return marriage_roulette(population, false);
    }

    return pair;
}

std::pair<int, int> marriage_roulette_reversed(Population &population, bool recalculate_population_fitness) {
    if (recalculate_population_fitness) {
        population.calc_population_fitness();
    }
    std::pair<int, int> pair = std::make_pair(-1, -1);
    int sum = 0;
    int worst_fitness_of_population = (int) population.get_lowest_fitness_individual().get_last_calculates_fitness();

    for (auto &it : population.get_individuals()) {
        sum += (int) it.get_last_calculates_fitness() - worst_fitness_of_population;
    }

    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    int value_p1 = rng.random(sum);
    int value_p2 = rng.random(sum);

    int value = 0;
    for (unsigned int current_idx = 0; current_idx < population.size(); ++current_idx) {
        value += (int) population.get_individuals().at(current_idx).get_last_calculates_fitness() -
                 worst_fitness_of_population;
        if (value_p1 <= value && pair.first < 0) {
            pair.first = current_idx;
        }
        if (value_p2 <= value && pair.second < 0) {
            pair.second = current_idx;
        }
    }

    return pair;
}


std::pair<int, int> marriage_roulette_reversed_distinct(Population &population, bool recalculate_population_fitness) {
    if (recalculate_population_fitness) {
        population.calc_population_fitness();
    }
    std::pair<int, int> pair = std::make_pair(-1, -1);
    int sum = 0;
    int worst_fitness_of_population = (int) population.get_lowest_fitness_individual().get_last_calculates_fitness();

    for (auto &it : population.get_individuals()) {
        sum += (int) it.get_last_calculates_fitness() - worst_fitness_of_population;
    }

    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    int value_p1 = rng.random(sum);
    int value_p2 = rng.random(sum);

    int value = 0;
    for (unsigned int current_idx = 0; current_idx < population.size(); ++current_idx) {
        value += (int) population.get_individuals().at(current_idx).get_last_calculates_fitness() -
                 worst_fitness_of_population;
        if (value_p1 <= value && pair.first < 0) {
            pair.first = current_idx;
        }
        if (value_p2 <= value && pair.second < 0) {
            pair.second = current_idx;
        }
    }

    if(pair.first == pair.second){
        return marriage_roulette_reversed_distinct(population, recalculate_population_fitness);
    }

    return pair;
}