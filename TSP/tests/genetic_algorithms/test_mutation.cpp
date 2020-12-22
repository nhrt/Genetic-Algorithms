//
// Created by Niklas Hartinger on 16.12.2020.
//

#include <catch.hpp>
#include <genetic_algorithms/mutation.h>

SCENARIO("Test Genetic Algorithms Mutation Shift delete", "[genetic_algorithms_mutation.cpp]"){
    Individual individual = Individual(5, nullptr, nullptr, true);

    for (int i = 0; i < 100; ++i) {
        REQUIRE(mutation_delete_shift(individual, 100));
        REQUIRE(individual.is_valid());
    }
}