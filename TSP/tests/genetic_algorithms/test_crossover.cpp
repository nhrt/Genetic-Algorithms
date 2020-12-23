//
// Created by Niklas Hartinger on 15.12.2020.
//

#include <catch.hpp>
#include <genetic_algorithms/crossover.h>
#include <iostream>

SCENARIO("Test Genetic Algorithms partially_matched_crossover", "[genetic_algorithms_crossover.cpp]")
{
    int start_idx = 0;
    Individual p1 = Individual(3, start_idx, nullptr, nullptr, false);
    Individual p2 = Individual(3, start_idx, nullptr, nullptr, false);
    std::vector<int> chromosome = {1, 2, 3};
    p1.update_chromosome(chromosome);
    chromosome = {4, 5, 6};
    p2.update_chromosome(chromosome);

    Individual c1 = Individual(3, start_idx, nullptr, nullptr, false);
    Individual c2 = Individual(3, start_idx, nullptr, nullptr, false);

    partially_matched_crossover(p1, p2, c1, c2);

    std::vector<int> result_c1 = {1, 5, 3};
    std::vector<int> result_c2 = {4, 2, 6};

    REQUIRE(c1.get_chromosome() == result_c1);
    REQUIRE(c2.get_chromosome() == result_c2);

    chromosome = {1, 2, 3};
    p1.update_chromosome(chromosome);
    chromosome = {2, 3, 1};
    p2.update_chromosome(chromosome);

    partially_matched_crossover(p1, p2, c1, c2);

    result_c1 = {1, 3, 2};
    result_c2 = {2, 3, 1};
    REQUIRE(c1.get_chromosome() == result_c1);
    REQUIRE(c2.get_chromosome() == result_c2);

    p1 = Individual(10, 10, nullptr, nullptr, false);
    p2 = Individual(10, 10, nullptr, nullptr, false);
    c1 = Individual(10, 10, nullptr, nullptr, false);
    c2 = Individual(10, 10, nullptr, nullptr, false);

    std::vector<int> chromosome1 = {8, 7, 3, 4, 5, 6, 0, 2, 1, 9};
    std::vector<int> chromosome2 = {7, 6, 0, 1, 2, 9, 8, 4, 3, 5};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);

    for (int i = 0; i < 100; ++i) {
        partially_matched_crossover(p1, p2, c1, c2);
        REQUIRE(c1.is_valid(9));
        REQUIRE(c2.is_valid(9));
    }
    REQUIRE(p1.get_chromosome() == chromosome1);
    REQUIRE(p2.get_chromosome() == chromosome2);
}

SCENARIO("Test Genetic Algorithms order_crossover", "[genetic_algorithms_crossover.cpp]")
{
    Individual p1 = Individual(10, 10, nullptr, nullptr, false);
    Individual p2 = Individual(10, 10, nullptr, nullptr, false);
    Individual c1 = Individual(10, 10, nullptr, nullptr, false);
    Individual c2 = Individual(10, 10, nullptr, nullptr, false);

    std::vector<int> chromosome1 = {8, 7, 3, 4, 5, 6, 0, 2, 1, 9};
    std::vector<int> chromosome2 = {7, 6, 0, 1, 2, 9, 8, 4, 3, 5};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);

    for (int i = 0; i < 100; ++i) {
        order_crossover(p1, p2, c1, c2);
        REQUIRE(c1.is_valid(9));
        REQUIRE(c2.is_valid(9));
    }
    REQUIRE(p1.get_chromosome() == chromosome1);
    REQUIRE(p2.get_chromosome() == chromosome2);
}