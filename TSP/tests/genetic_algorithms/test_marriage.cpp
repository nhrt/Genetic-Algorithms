//
// Created by Niklas Hartinger on 16.12.2020.
//
#include <catch.hpp>
#include <genetic_algorithms/marriage.h>
#include <util/read_cities.h>

SCENARIO("Test Genetic Algorithms Marriage-Roulette", "[genetic_algorithms_mariage.cpp]") {
    std::string file_distances = "att48_d.txt";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population = Population(10, 10, 0, rating, fitness, distances);
    std::pair<int, int> result;
    population.calc_population_fitness();
    for (int i = 0; i < 100; i++) {
        result = marriage_roulette(population, false);
        REQUIRE(result.first >= 0);
        REQUIRE((unsigned int) result.first < population.size());
        REQUIRE(result.second >= 0);
        REQUIRE((unsigned int) result.second < population.size());
        REQUIRE(result.first != result.second);
    }
}

SCENARIO("Test Genetic Algorithms Marriage-Roulette-Reversed", "[genetic_algorithms_mariage.cpp]") {
    std::string file_distances = "att48_d.txt";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population = Population(10, 10, 0, rating_reversed, fitness, distances);
    std::pair<int, int> result;
    population.calc_population_fitness();
    for (int i = 0; i < 100; i++) {
        result = marriage_roulette_reversed(population, false);
        REQUIRE(result.first >= 0);
        REQUIRE((unsigned int) result.first < population.size());
        REQUIRE(result.second >= 0);
        REQUIRE((unsigned int) result.second < population.size());
    }
}


