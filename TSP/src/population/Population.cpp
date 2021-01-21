//
// Created by Niklas Hartinger on 14.12.2020.
//
#include "Population.h"


void Population::initialize(int size_population, int size_chromosome, Function_rating fct_rating,
                            Function_fitness fct_fitness) {
    for (int i = 0; i < size_population; ++i) {
        individuals.emplace_back(size_chromosome, idx_start, fct_rating, fct_fitness);
    }
}

std::vector<Individual> &Population::get_individuals() {
    return individuals;
}

int Population::calc_population_fitness() {
    int sum = 0;
    for (auto &individual : individuals) {
        sum += (int) individual.fitness(idx_start, distances);
    }
    last_fitness = sum;
    return last_fitness;
}

int Population::get_last_calculates_population_fitness() const {
    return last_fitness;
}

void Population::add_individual(Individual &individual) {
    individuals.push_back(individual);
}

Individual Population::get_highest_fitness_individual(){
    calc_population_fitness();
    return *std::max_element(individuals.begin(), individuals.end());
}

Individual Population::get_lowest_fitness_individual(){
    calc_population_fitness();
    return *std::min_element(individuals.begin(), individuals.end());
}

bool is_unique(Population &p, Individual &i){
    for(auto& value: p.get_individuals()) {
        if(value.get_chromosome() == i.get_chromosome()){
            return false;
        }
    }
    return true;
}

Individual create_unique_individual(Population &p){
    Individual i = p.get_individuals().at(0).create_with_same_parameters(p.get_idx_start());
    bool unique = is_unique(p,i);

    while(!unique){
        i = p.get_individuals().at(0).create_with_same_parameters(p.get_idx_start());
        unique = is_unique(p,i);
    }
    return i;
}