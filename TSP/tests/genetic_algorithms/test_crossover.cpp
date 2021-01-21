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
        for (int j = 0; j < c1.get_size(); ++j) {
            REQUIRE(c1.get_chromosome().at(j) >= 0);
            REQUIRE(c2.get_chromosome().at(j) >= 0);
        }
    }
    REQUIRE(p1.get_chromosome() == chromosome1);
    REQUIRE(p2.get_chromosome() == chromosome2);
}

SCENARIO("Test Genetic Algorithms edge_recombination_crossover", "[genetic_algorithms_crossover.cpp]") {

    std::vector<int> cr1 = {2,4,1,0,3};
    std::vector<int> cr2 = {2,1,3,4,0};
    Individual p1 = Individual(5, 5, nullptr, nullptr, false);
    Individual p2 = Individual(5, 5, nullptr, nullptr, false);
    p1.update_chromosome(cr1);
    p2.update_chromosome(cr2);
    Individual c1 = Individual(5, 5, nullptr, nullptr, false);
    Individual c2 = Individual(5, 5, nullptr, nullptr, false);
    edge_recombination_crossover(p1, p2, c1, c2);
    REQUIRE(edge_recombination_crossover(p1, p2, c1, c2) == true);
    REQUIRE(c1.is_valid());
    REQUIRE(c2.is_valid());

    for (int i = 0; i < 100; ++i) {
        p1 = Individual(5, 5, nullptr, nullptr, true);
        p2 = Individual(5, 5, nullptr, nullptr, true);
        c1 = Individual(5, 5, nullptr, nullptr, false);
        c2 = Individual(5, 5, nullptr, nullptr, false);
        edge_recombination_crossover(p1, p2, c1, c2);
        REQUIRE(edge_recombination_crossover(p1, p2, c1, c2) == true);
        REQUIRE(c1.is_valid());
        REQUIRE(c2.is_valid());
    }

    for (int i = 0; i < 100; ++i) {
        std::cout << "i " << i << std::endl << std::endl;
        p1 = Individual(59, 59, nullptr, nullptr, true);
        p2 = Individual(59, 59, nullptr, nullptr, true);
        c1 = Individual(59, 59, nullptr, nullptr, false);
        c2 = Individual(59, 59, nullptr, nullptr, false);
        edge_recombination_crossover(p1, p2, c1, c2);

        REQUIRE(edge_recombination_crossover(p1, p2, c1, c2) == true);
        std::cout << c1 << std::endl;
        REQUIRE(c1.is_valid());
        REQUIRE(c2.is_valid());
    }
}

SCENARIO("Test Genetic Algorithms cycle_crossover_all_cycles", "[genetic_algorithms_crossover.cpp]")
{
    Individual p1 = Individual(10, 10, nullptr, nullptr, false);
    Individual p2 = Individual(10, 10, nullptr, nullptr, false);
    Individual c1 = Individual(10, 10, nullptr, nullptr, false);
    Individual c2 = Individual(10, 10, nullptr, nullptr, false);
    // only one cycle identified, thus no crossover but a copy of parents to the children should occur.
    std::vector<int> chromosome1 = {8, 7, 3, 4, 5, 6, 0, 2, 1, 9};
    std::vector<int> chromosome2 = {7, 6, 0, 1, 2, 9, 8, 4, 3, 5};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);
    cycle_crossover_all_cycles(p1, p2, c1, c2);
    REQUIRE(c1.is_valid(9));
    REQUIRE(c2.is_valid(9));
    REQUIRE(std::equal(p1.get_chromosome().begin(), p1.get_chromosome().end(), c1.get_chromosome().begin()));
    REQUIRE(std::equal(p2.get_chromosome().begin(), p2.get_chromosome().end(), c2.get_chromosome().begin()));

    /*
     * more than one cycle is identified, thus a crossover should occur resulting in both children containing information of each parent but being unequal to both parents.
     * if there are multiple cycles but they consist of only one tuple, the children chromosomes will still be equal to the parent chromosomes even after a crossover occurred.
     */
    p1 = Individual(3, 3, nullptr, nullptr, false);
    p2 = Individual(3, 3, nullptr, nullptr, false);
    c1 = Individual(3, 3, nullptr, nullptr, false);
    c2 = Individual(3, 3, nullptr, nullptr, false);
    chromosome1 = {0, 2, 1};
    chromosome2 = {1, 2, 0};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);
    cycle_crossover_all_cycles(p1, p2, c1, c2);
    REQUIRE(c1.is_valid(2));
    REQUIRE(c2.is_valid(2));
    REQUIRE(std::equal(p1.get_chromosome().begin(), p1.get_chromosome().end(), c1.get_chromosome().begin()));
    REQUIRE(std::equal(p2.get_chromosome().begin(), p2.get_chromosome().end(), c2.get_chromosome().begin()));

    /*
     * more than one cycle is identified, thus a crossover should occur resulting in both children containing information of each parent but being unequal to both parents.
     * if there are multiple cycles and at least two consist of more than one tuple, the children chromosomes will not be equal to the parent chromosomes anymore after a crossover occurred.
     */
    p1 = Individual(4, 4, nullptr, nullptr, false);
    p2 = Individual(4, 4, nullptr, nullptr, false);
    c1 = Individual(4, 4, nullptr, nullptr, false);
    c2 = Individual(4, 4, nullptr, nullptr, false);
    chromosome1 = {0, 2, 3, 1};
    chromosome2 = {1, 3, 2, 0};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);
    cycle_crossover_all_cycles(p1, p2, c1, c2);
    REQUIRE(c1.is_valid(3));
    REQUIRE(c2.is_valid(3));
    REQUIRE(!std::equal(p1.get_chromosome().begin(), p1.get_chromosome().end(), c1.get_chromosome().begin()));
    REQUIRE(!std::equal(p2.get_chromosome().begin(), p2.get_chromosome().end(), c2.get_chromosome().begin()));
}

SCENARIO("Test Genetic Algorithms cycle_crossover_one_cycle", "[genetic_algorithms_crossover.cpp]")
{
    Individual p1 = Individual(10, 10, nullptr, nullptr, false);
    Individual p2 = Individual(10, 10, nullptr, nullptr, false);
    Individual c1 = Individual(10, 10, nullptr, nullptr, false);
    Individual c2 = Individual(10, 10, nullptr, nullptr, false);
    // cycle consists of all chromosome values, thus no crossover but a copy of parents to the children should occur.
    std::vector<int> chromosome1 = {8, 7, 3, 4, 5, 6, 0, 2, 1, 9};
    std::vector<int> chromosome2 = {7, 6, 0, 1, 2, 9, 8, 4, 3, 5};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);
    cycle_crossover_one_cycle(p1, p2, c1, c2);
    REQUIRE(c1.is_valid(9));
    REQUIRE(c2.is_valid(9));
    REQUIRE(std::equal(p1.get_chromosome().begin(), p1.get_chromosome().end(), c1.get_chromosome().begin()));
    REQUIRE(std::equal(p2.get_chromosome().begin(), p2.get_chromosome().end(), c2.get_chromosome().begin()));

    /*
     * more than one cycle can be constructed, thus a crossover should occur resulting in both children containing information of each parent but being unequal to both parents.
     * if there could be multiple cycles but they consist of only one tuple, the children chromosomes will still be equal to the parent chromosomes even after a crossover occurred.
     */
    p1 = Individual(3, 3, nullptr, nullptr, false);
    p2 = Individual(3, 3, nullptr, nullptr, false);
    c1 = Individual(3, 3, nullptr, nullptr, false);
    c2 = Individual(3, 3, nullptr, nullptr, false);
    chromosome1 = {0, 2, 1};
    chromosome2 = {1, 2, 0};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);
    cycle_crossover_one_cycle(p1, p2, c1, c2);
    REQUIRE(c1.is_valid(2));
    REQUIRE(c2.is_valid(2));

    /*
     * more than one cycle can be constructed, thus a crossover should occur resulting in both children containing information of each parent but being unequal to both parents.
     * if there could be multiple cycles and at least two consist of more than one tuple, the children chromosomes will not be equal to the parent chromosomes anymore after a crossover occurred.
     */
    p1 = Individual(4, 4, nullptr, nullptr, false);
    p2 = Individual(4, 4, nullptr, nullptr, false);
    c1 = Individual(4, 4, nullptr, nullptr, false);
    c2 = Individual(4, 4, nullptr, nullptr, false);
    chromosome1 = {0, 2, 3, 1};
    chromosome2 = {1, 3, 2, 0};
    p1.update_chromosome(chromosome1);
    p2.update_chromosome(chromosome2);
    cycle_crossover_one_cycle(p1, p2, c1, c2);
    REQUIRE(c1.is_valid(3));
    REQUIRE(c2.is_valid(3));
    REQUIRE(!std::equal(p1.get_chromosome().begin(), p1.get_chromosome().end(), c1.get_chromosome().begin()));
    REQUIRE(!std::equal(p2.get_chromosome().begin(), p2.get_chromosome().end(), c2.get_chromosome().begin()));
}