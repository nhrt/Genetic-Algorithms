//
// Created by Niklas Hartinger on 14.12.2020.
//
#include <catch.hpp>
#include <population/Population.h>
#include <util/read_cities.h>

SCENARIO("Test Population initialization", "[Population.cpp]") {
    std::string file_distances = "att48_d.txt";
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
    std::string file_distances = "att48_d.txt";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population = Population(0, 0, 0, rating, fitness, distances);
    int f = population.calc_population_fitness();
    REQUIRE(f == 0);

    population = Population(1, 47, 0, rating, fitness, distances);
    f = population.calc_population_fitness();
    REQUIRE(f > 0);
}

SCENARIO("Test Population high and low fitness individual", "[Population.cpp]") {
    std::string file_distances = "att48_d.txt";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population = Population(0, distances);
    Individual individual = Individual(3,0, rating, fitness, false);
    std::vector<int> chromosome = {2,2,2};
    individual.update_chromosome(chromosome);
    population.add_individual(individual);
    chromosome = {1,1,1};
    individual.update_chromosome(chromosome);
    population.add_individual(individual);
    chromosome = {1,2,3};
    individual.update_chromosome(chromosome);
    population.add_individual(individual);

    chromosome = {2,2,2};
    REQUIRE(population.get_highest_fitness_individual().get_chromosome() == chromosome);
    chromosome = {1,2,3};
    REQUIRE(population.get_lowest_fitness_individual().get_chromosome() == chromosome);
}

SCENARIO("Test Population unique elements", "[Population.cpp]") {
   std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Population population = Population(0, distances);
    Individual individual = Individual(3,0, rating, fitness, false);
    std::vector<int> chromosome = {2,2,2};
    individual.update_chromosome(chromosome);
    population.add_individual(individual);
    chromosome = {1,1,1};
    individual.update_chromosome(chromosome);
    population.add_individual(individual);
    chromosome = {1,2,3};
    individual.update_chromosome(chromosome);
    population.add_individual(individual);

    chromosome = {1,1,1};
    individual.update_chromosome(chromosome);
    REQUIRE(!is_unique(population, individual));

    chromosome = {3,2,1};
    individual.update_chromosome(chromosome);
    REQUIRE(is_unique(population, individual));

    individual = create_unique_individual(population);
    REQUIRE(is_unique(population, individual));
}
