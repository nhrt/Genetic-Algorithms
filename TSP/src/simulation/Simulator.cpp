//
// Created by Niklas Hartinger on 05.01.2021.
//

#include <genetic_algorithms/marriage.h>
#include <genetic_algorithms/crossover.h>
#include <genetic_algorithms/mutation.h>
#include <genetic_algorithms/selection.h>
#include "Simulator.h"

Simulator::Simulator(
        const std::string &position_path, const std::string &distance_path, const int start_city,
        int number_cities, int population_size, int generations, int mutation_rate,
        Crossover_Algorithm crossover, Marriage_Algorithm marriage, Mutation_Algorithm mutation,
        Selection_Algorithm selection)
        : generations(generations), mutation_rate(mutation_rate), population_size(population_size),
          number_cities(number_cities) {

    if (!read_distances(distance_path, distances)) {
        std::cerr << "Distance-File can not be opened" << std::endl;
        exit(1);
    }

    if (!read_indexes(position_path, indexes, number_cities)) {
        std::cerr << "Cities-Position-File can not be opened" << std::endl;
        exit(2);
    }

    auto it = std::find(indexes.begin(), indexes.end(), start_city);
    if (it == indexes.end()) {
        std::cerr << "Start city is not part of the cities" << std::endl;
        exit(3);
    }
    start_city_idx = std::distance(indexes.begin(), it);

    crossover_algo = crossover;
    marriage_algo = marriage;
    mutation_algo = mutation;
    selection_algo = selection;

    if(marriage_algo == Marriage_Algorithm::Roulette_Reversed || marriage_algo == Marriage_Algorithm::Roulette_Reversed_Distinct){
        population = Population(population_size, number_cities - 1, start_city_idx, rating_reversed, fitness_reversed,
                                distances);
    }else{
        population = Population(population_size, number_cities-1, start_city_idx, rating, fitness, distances);
    }
}

std::tuple<int, int, int> Simulator::simulate() {
    std::tuple<int, int, int> result = std::make_tuple(0, 0, 0);
    if (finished()) {
        std::cout << "No calculations done. Simulation was already finished." << std::endl;
        return result;
    }

    Population population_next = Population(start_city_idx, distances);
    Population test = population;
    test.calc_population_fitness();
    population.calc_population_fitness();
    while (population_next.size() < population.size()) {

        std::pair<int, int> idx_children;
        switch (marriage_algo) {
            case Marriage_Algorithm::Roulette:
                idx_children = marriage_roulette(population, false);
                break;
            case Marriage_Algorithm::Roulette_Reversed:
                idx_children = marriage_roulette_reversed(population, false);
                break;
            case Marriage_Algorithm::Roulette_Reversed_Distinct:
                idx_children = marriage_roulette_reversed_distinct(population, false);
                break;
            default:
                idx_children = marriage_roulette(population, false);
        }

        Individual p1 = population.get_individuals().at(idx_children.first);
        Individual p2 = population.get_individuals().at(idx_children.second);


        Individual c1 = marriage_algo == Marriage_Algorithm::Roulette ?
                        Individual((int) p1.get_size(), population.get_idx_start(), rating, fitness, false)
                                                                               : Individual((int) p1.get_size(),
                                                                                            population.get_idx_start(),
                                                                                            rating_reversed,
                                                                                            fitness_reversed,
                                                                                            false);
        Individual c2 = marriage_algo == Marriage_Algorithm::Roulette ?
                        Individual((int) p1.get_size(), population.get_idx_start(), rating, fitness, false)
                                                                               : Individual((int) p1.get_size(),
                                                                                            population.get_idx_start(),
                                                                                            rating_reversed,
                                                                                            fitness_reversed,
                                                                                            false);

        switch (crossover_algo) {
            case Crossover_Algorithm::Partially_Matched:
                partially_matched_crossover(p1, p2, c1, c2);
                break;
            case Crossover_Algorithm::Cycle_all_cycles:
                cycle_crossover_all_cycles(p1, p2, c1, c2);
                break;
            case Crossover_Algorithm::Cycle_one_cycle:
                cycle_crossover_one_cycle(p1, p2, c1, c2);
                break;
            case Crossover_Algorithm::Edge_Recombination:
                edge_recombination_crossover(p1, p2, c1, c2);
                break;
            case Crossover_Algorithm::Order:
                order_crossover(p1, p2, c1, c2);
                break;
            default:
                partially_matched_crossover(p1, p2, c1, c2);
        }

        switch (mutation_algo) {
            case Mutation_Algorithm::Delete_Shift:
                mutation_delete_shift(c1, mutation_rate);
                mutation_delete_shift(c2, mutation_rate);
                break;
            default:
                mutation_delete_shift(c1, mutation_rate);
                mutation_delete_shift(c2, mutation_rate);
        }

        population_next.add_individual(c1);
        if (population_next.size() < population.size()) {
            population_next.add_individual(c2);
        }
    }
    switch (selection_algo) {
        case Selection_Algorithm::SOFT:
            population = selection_sotf(population, population_next);
            break;
        case Selection_Algorithm::SOFT_Distinct:
            population = selection_sotf_distinct(population, population_next);
            break;
        default:
            population = selection_sotf(population, population_next);
    }
    population.calc_population_fitness();

    simulations++;

    std::get<0>(result) = population.get_lowest_fitness_individual().get_last_calculates_fitness();
    std::get<1>(result) = population.get_highest_fitness_individual().get_last_calculates_fitness();
    std::get<2>(result) = population.get_last_calculates_population_fitness() / population_size;
    return result;
}

bool Simulator::finished() const {
    return simulations >= generations;
}

std::vector<int> Simulator::best_individual(){
    std::vector<int> best = population.get_highest_fitness_individual().get_chromosome();
    best.push_back(start_city_idx);
    best.insert(best.begin(), start_city_idx);

    return best;
}