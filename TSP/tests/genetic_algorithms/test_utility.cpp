//
// Created by Niklas Hartinger on 14.12.2020.
//
#include <catch.hpp>
#include <genetic_algorithms/utility.h>
#include <util/read_cities.h>
#include <individual/Individual.h>

SCENARIO("Test Genetic Algorithms Utility Rating", "[genetic_algorithms_utility.cpp]") {
    std::vector<std::vector<int>> distances =
            {
                    {0, 1, 2},
                    {3, 0, 4},
                    {5, 6, 0},
            };
    std::vector<int> chromosome = {0,
                                   0,
                                   0};
    REQUIRE(cost_function(0, chromosome, distances) == 0);

    chromosome = {0, 1, 2};
    REQUIRE((int) cost_function(0, chromosome, distances) == 10);

    chromosome = {0, 1, 2, 2};
    REQUIRE((int) cost_function(0, chromosome, distances) == 10);
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

SCENARIO("Test reversed ratin", "[genetic_algorithms_utility.cpp]") {
    std::string file_distances = "att48_d.txt";
    std::string location = "../../data/cities/";
    std::vector<std::vector<int>> distances;
    read_distances(location + file_distances, distances);
    std::vector<int> best = {
            7,
            37,
            30,
            43,
            17,
            6,
            27,
            5,
            36,
            18,
            26,
            16,
            42,
            29,
            35,
            45,
            32,
            19,
            46,
            20,
            31,
            38,
            47,
            4,
            41,
            23,
            9,
            44,
            34,
            3,
            25,
            1,
            28,
            33,
            40,
            15,
            21,
            2,
            22,
            13,
            24,
            12,
            10,
            11,
            14,
            39,
            8
    };

    Individual i = Individual(47, 0, rating_reversed, fitness_reversed, false);
    REQUIRE(best.size() == 47);
    REQUIRE(i.update_chromosome(best));
    REQUIRE(i.get_size() == 47);
    REQUIRE(i.is_valid());
    REQUIRE(-(int)i.fitness(0,distances) == 33551);
}


