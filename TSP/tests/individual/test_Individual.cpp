//
// Created by Niklas Hartinger on 14.12.2020.
//
#include <catch.hpp>
#include <individual/Individual.h>
#include <util/read_cities.h>
#include <genetic_algorithms/utility.h>

// DEPRECATED
SCENARIO("Test Individual initialization DEPRECATED", "[Individual.cpp]")
{
    int size = 10;
    Individual individual = Individual(size, nullptr, nullptr);
    std::vector<int> chromosome = individual.get_chromosome();

    // Test size
    REQUIRE(chromosome.size() == (unsigned int) size);

    // Test value range
    for (int i = 0; i < size; ++i) {
        REQUIRE(chromosome.at(i) >= 0);
        REQUIRE(chromosome.at(i) < size);
    }

    // Test uniqueness
    REQUIRE(std::unique(chromosome.begin(), chromosome.end()) == chromosome.end());
}

SCENARIO("Test Individual initialization", "[Individual.cpp]")
{
    for (int i = 0; i < 100; ++i) {
        int size = 10;
        int idx_start = Random_Number_Generator::getInstance().random(size + 1);

        REQUIRE(idx_start >= 0);
        REQUIRE(idx_start <= size);

        Individual individual = Individual(size, idx_start, nullptr, nullptr);
        std::vector<int> chromosome = individual.get_chromosome();

        // Test size
        REQUIRE(chromosome.size() == (unsigned int) size);

        // Test value range
        for (int j = 0; j < size; ++j) {
            REQUIRE(chromosome.at(j) >= 0);
            REQUIRE(chromosome.at(j) <= size);
            REQUIRE(chromosome.at(j) != idx_start);
        }

        // Test uniqueness
        REQUIRE(std::unique(chromosome.begin(), chromosome.end()) == chromosome.end());
    }
}

SCENARIO("Test Individual update", "[Individual.cpp]") {
    int size = 10;

    Individual individual = Individual(size, nullptr, nullptr);
    REQUIRE(individual.update_chromosome(5, 100) == false);
    REQUIRE(individual.update_chromosome(5, -1) == false);
    REQUIRE(individual.update_chromosome(5, 0) == true);
    REQUIRE(individual.update_chromosome(5, size - 1) == true);
    REQUIRE(individual.get_chromosome().at(0) == 5);
    REQUIRE(individual.get_chromosome().at(size - 1) == 5);


    std::vector<int> update_valid = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> update_invalid = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    REQUIRE(individual.update_chromosome(update_invalid) == false);
    REQUIRE(individual.update_chromosome(update_valid) == true);
    for (unsigned int i = 0; i < individual.get_chromosome().size(); ++i) {
        REQUIRE(individual.get_chromosome().at(i) == update_valid.at(i));
    }
}


SCENARIO("Test Individual fitness", "[Individual.cpp]") {
    std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);

    Individual individual = Individual(10, rating, fitness, true);
    int f = individual.fitness(distances);
    REQUIRE(f >= 0);

    individual = Individual(1, rating, fitness, true);
    f = individual.fitness(distances);
    REQUIRE(f == 0);

    individual = Individual(0, rating, fitness, true);
    f = individual.fitness(distances);
    REQUIRE(f < 0);

}

SCENARIO("Test Inidividual < Operator", "[Individual.cpp]") {
    Individual individual1 = Individual(3, rating, fitness, false);
    Individual individual2 = Individual(3, rating, fitness, false);
    std::vector<int> chromo1 = {0, 1, 2};
    std::vector<int> chromo2 = {0, 1, 1};

    std::vector<std::vector<int>> distances = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
    };

    individual1.update_chromosome(chromo1);
    individual2.update_chromosome(chromo2);
    individual1.fitness(distances);
    individual2.fitness(distances);
    REQUIRE(individual1 < individual2);
}

