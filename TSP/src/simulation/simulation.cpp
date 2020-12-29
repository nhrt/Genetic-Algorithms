//
// Created by Niklas Hartinger on 29.12.2020.
//

#include <vector>
#include <util/read_cities.h>
#include <population/Population.h>
#include <algorithm>
#include <genetic_algorithms/marriage.h>
#include <genetic_algorithms/crossover.h>
#include <genetic_algorithms/mutation.h>
#include <genetic_algorithms/selection.h>

#include "simulation.h"


int simulate(const std::string &city_path, const std::string &distance_path, const std::string &start_city,
             int number_cities, int size_population, int epochs, int mutation_rate,
             int crossover_algorithm, int marriage_algorithm, int mutation_algorithm, int selection_algorithm
) {
    std::vector<std::vector<int>> distances;
    std::vector<std::string> cities;

    if (!read_distances(distance_path, distances)) {
        std::cerr << "Distance-File can not be opened" << std::endl;
        return -1;
    }

    if (!read_names(city_path, cities, number_cities)) {
        std::cerr << "Cities-Name-File can not be opened" << std::endl;
        return -2;
    }

    auto it = std::find(cities.begin(), cities.end(), start_city);
    if(it == cities.end()){
        std::cerr << "Start city is not part of the cities" << std::endl;
        return -3;
    }
    int start_city_idx = std::distance(cities.begin(), it);


    Population population_current = Population(size_population, number_cities-1, start_city_idx, rating, fitness, distances);
    Population population_next = Population(start_city_idx, distances);
    population_current.calc_population_fitness();
    for (int generation = 0; generation < epochs; ++generation) {
        while(population_next.size() < population_current.size()){
            std::pair<int,int> idx_children;
            switch(marriage_algorithm){
                default:
                    idx_children = marriage_roulette(population_current, false);
            }
            Individual p1 = population_current.get_individuals().at(idx_children.first);
            Individual p2 = population_current.get_individuals().at(idx_children.second);
            Individual c1 = Individual((int)p1.get_size(), population_current.get_idx_start(), rating, fitness, false);
            Individual c2 = Individual((int)p1.get_size(), population_current.get_idx_start(), rating, fitness, false);

            switch (crossover_algorithm) {
                default:
                    partially_matched_crossover(p1,p2,c1,c2);
            }

            switch(mutation_algorithm) {
                default:
                    mutation_delete_shift(c1, mutation_rate);
                    mutation_delete_shift(c2, mutation_rate);
            }

            population_next.add_individual(c1);
            population_next.add_individual(c2);
        }
        switch(selection_algorithm) {
            default:
                population_current = selection_sotf(population_current, population_next);
        }
        population_current.calc_population_fitness();
        std::cout << "Generation: " << generation+1 << " Fitness: " << population_current.get_last_calculates_population_fitness() <<std::endl;
    }


    return 0;
}