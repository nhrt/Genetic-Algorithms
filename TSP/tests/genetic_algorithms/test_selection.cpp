//
// Created by Niklas Hartinger on 21.12.2020.
//
#include <catch.hpp>
#include <genetic_algorithms/selection.h>
#include <util/read_cities.h>

SCENARIO("Test Genetic Algorithms selection sotf", "[genetic_algorithms_selection.cpp]") {
    std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    for (int i = 0; i < 100; ++i) {
        Population population1 = Population(5, 5, 1, rating, fitness, distances);
        Population population2 = Population(5, 5, 1, rating, fitness, distances);
        Population p_best = selection_sotf(population1, population2);

        p_best.calc_population_fitness();
        REQUIRE(p_best.get_last_calculates_population_fitness() >= population1.get_last_calculates_population_fitness());
        REQUIRE(p_best.get_last_calculates_population_fitness() >= population2.get_last_calculates_population_fitness());
    }

    for (int i = 0; i < 100; ++i) {
        Population population1 = Population(5, 5, 1, rating_reversed, fitness_reversed, distances);
        Population population2 = Population(5, 5, 1, rating_reversed, fitness_reversed, distances);
        Population p_best = selection_sotf(population1, population2);

        p_best.calc_population_fitness();
        REQUIRE(p_best.get_last_calculates_population_fitness() >= population1.get_last_calculates_population_fitness());
        REQUIRE(p_best.get_last_calculates_population_fitness() >= population2.get_last_calculates_population_fitness());
    }

}

SCENARIO("Test Genetic Algorithms selection sotf distinct", "[genetic_algorithms_selection.cpp]") {
    std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population1 = Population( 1, distances);
    Population population2 = Population( 1, distances);
    Individual i = Individual(5, 1, rating_reversed, fitness_reversed, false);
    std::vector<int> chromosome = {5,2,0,4,3};
    i.update_chromosome(chromosome);
    population1.add_individual(i);
    population1.add_individual(i);

    population2.add_individual(i);
    population2.add_individual(i);
    Population p_best = selection_sotf_distinct(population1, population2);

    for (unsigned int j = 0; j < p_best.size(); ++j) {
        for (unsigned int k = 0; j < p_best.size(); ++j) {
            if(j != k){
                REQUIRE(p_best.get_individuals().at(j).get_chromosome() != p_best.get_individuals().at(k).get_chromosome());
            }
        }
    }

    for (int i = 0; i < 10000; ++i) {
        population1 = Population(5, 5, 1, rating_reversed, fitness_reversed, distances);
        population2 = Population(5, 5, 1, rating_reversed, fitness_reversed, distances);
        p_best = selection_sotf_distinct(population1, population2);

        for (unsigned int j = 0; j < p_best.size(); ++j) {
            for (unsigned int k = 0; j < p_best.size(); ++j) {
                if (j != k) {
                    REQUIRE(p_best.get_individuals().at(j).get_chromosome() != p_best.get_individuals().at(k).get_chromosome());
                }
            }
        }
    }
}