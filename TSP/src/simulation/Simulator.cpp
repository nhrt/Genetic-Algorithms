//
// Created by Niklas Hartinger on 05.01.2021.
//

#include <genetic_algorithms/marriage.h>
#include <genetic_algorithms/crossover.h>
#include <genetic_algorithms/mutation.h>
#include <genetic_algorithms/selection.h>
#include "Simulator.h"

void Simulator::simulate() {
    if(finished()){
        return;
    }

    Population population_next = Population(start_city_idx, distances);
    population.calc_population_fitness();
    while (population_next.size() < population.size()) {

        std::pair<int, int> idx_children;
        switch (marriage_algo) {
            case Marriage_Algorithms::Roulette:
                idx_children = marriage_roulette(population, false);
                break;
            case Marriage_Algorithms::Roulette_Reversed:
                idx_children = marriage_roulette_reversed(population, false);
                break;
            default:
                idx_children = marriage_roulette(population, false);
        }

        Individual p1 = population.get_individuals().at(idx_children.first);
        Individual p2 = population.get_individuals().at(idx_children.second);
        Individual c1 = Individual((int) p1.get_size(), population.get_idx_start(), rating, fitness, false);
        Individual c2 = Individual((int) p1.get_size(), population.get_idx_start(), rating, fitness, false);

        switch (crossover_algo) {
            case Crossover_Algorithms::Partially_Matched:
                partially_matched_crossover(p1, p2, c1, c2);
                break;
            case Crossover_Algorithms::Cycle_all_cycles:
                cycle_crossover_all_cycles(p1, p2, c1, c2);
                break;
            case Crossover_Algorithms::Cycle_one_cycle:
                cycle_crossover_one_cycle(p1, p2, c1, c2);
                break;
            case Crossover_Algorithms::Edge_Recombination:
                edge_recombination_crossover(p1, p2, c1, c2);
                break;
            case Crossover_Algorithms::Order:
                order_crossover(p1, p2, c1, c2);
            default:
                partially_matched_crossover(p1, p2, c1, c2);
        }

        switch (mutation_algo) {
            case Mutation_Algorithms::Delete_Shift:
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
        case Selection_Algorithms::SOFT:
            population = selection_sotf(population, population_next);
            break;
        case Selection_Algorithms::SOFT_Reversed:
            population = selection_sotf_reversed(population, population_next);
            break;
        default:
            population = selection_sotf(population, population_next);
    }
    population.calc_population_fitness();

    simulations++;
}

bool Simulator::finished() {
    return simulations >= epochs;
}
