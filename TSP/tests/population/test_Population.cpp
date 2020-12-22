//
// Created by Niklas Hartinger on 14.12.2020.
//
#include <catch.hpp>
#include <population/Population.h>
#include <util/read_cities.h>
#include <genetic_algorithms/utility.h>

SCENARIO("Test Population initialization", "[Population.cpp]") {
    std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population = Population(-1, 0, 0, nullptr, nullptr, distances);
    REQUIRE(population.size() == 0);
    population = Population(10, 10, 0, nullptr, nullptr, distances);
    REQUIRE(population.size() == 10);
    REQUIRE(population.get_individuals().at(0).get_chromosome().size() == 10);
}

SCENARIO("Test Population fitness", "[Population.cpp]") {
    std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population = Population(0, 0, 0, rating, fitness, distances);
    int f = population.calc_population_fitness();
    REQUIRE(f == 0);

    population = Population(1, 58, 0, rating, fitness, distances);
    f = population.calc_population_fitness();
    REQUIRE(f > 0);

}
