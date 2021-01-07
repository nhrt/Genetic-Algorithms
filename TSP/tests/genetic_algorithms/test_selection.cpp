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

}
SCENARIO("Test Genetic Algorithms selection sotf reversed", "[genetic_algorithms_selection.cpp]") {
    std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    for (int i = 0; i < 100; ++i) {
        Population population1 = Population(5, 5, 1, rating, fitness, distances);
        Population population2 = Population(5, 5, 1, rating, fitness, distances);
        Population p_best = selection_sotf_reversed(population1, population2);

        p_best.calc_population_fitness();
        REQUIRE(p_best.get_last_calculates_population_fitness() <= population1.get_last_calculates_population_fitness());
        REQUIRE(p_best.get_last_calculates_population_fitness() <= population2.get_last_calculates_population_fitness());
    }
}