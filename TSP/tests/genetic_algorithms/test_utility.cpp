//
// Created by Niklas Hartinger on 14.12.2020.
//
#include <catch.hpp>
#include <genetic_algorithms/utility.h>

SCENARIO("Test Genetic Algorithms Utility Rating", "[genetic_algorithms_utility.cpp]") {
    std::vector<std::vector<int>> distances =
            {
                    {0, 1, 2},
                    {3, 0, 4},
                    {5, 6, 0},
            };
    std::vector<int> chromosome = {0, 0, 0};
    REQUIRE((int) cost_function(chromosome, distances) == 0);

    chromosome = {0, 1, 2};
    REQUIRE((int) cost_function(chromosome, distances) == 5);

    chromosome = {0, 1, 2, 2};
    REQUIRE((int) cost_function(chromosome, distances) == 5);
}

SCENARIO("TEST Genetic Algorithms Utility Find Duplicates", "[genetic_algorithms_utility.cpp]") {
    std::vector<int> chromosome1 = {1, 2, 3};
    std::vector<int> chromosome2 = {1, 2, 1};
    std::vector<int> chromosome3 = {1, 2, 2};
    std::vector<int> chromosome4 = {3, 3, 2};

    REQUIRE(find_duplicate(chromosome1) < 0);
    REQUIRE(find_duplicate(chromosome2) == 2);
    REQUIRE(find_duplicate(chromosome3) == 2);
    REQUIRE(find_duplicate(chromosome4) == 1);
}

SCENARIO("TEST Genetic Algorithms Utility Shift", "[genetic_algorithms_utility.cpp]") {
    std::vector<int> chromosome = {1, 2, 3};
    shift_left(chromosome, 0, 1);
    std::vector<int> result = {2, 1, 3};
    REQUIRE(chromosome == result);

    chromosome = {1, 2, 3, 4, 5};
    result = {1, 3, 4, 2, 5};
    shift_left(chromosome, 1, 3);
    REQUIRE(chromosome == result);
}


