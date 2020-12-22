//
// Created by Niklas Hartinger on 16.12.2020.
//
#include <catch.hpp>
#include <util/Random_Number_Generator.h>
#include <iostream>

SCENARIO("Test Utility random number generator", "[test_util_random_number_generator.cpp]")
{
    Random_Number_Generator &randomNumberGenerator = Random_Number_Generator::getInstance();
    for (int i = 0; i < 100; ++i) {
        REQUIRE(randomNumberGenerator.random(0,10) >= 0);
        REQUIRE(randomNumberGenerator.random(0,10) <= 10);
    }
    for (int i = 0; i < 100; ++i) {
        REQUIRE(randomNumberGenerator.random(0, 1) == 0);
    }
    for (int i = 0; i < 100; ++i) {
        REQUIRE(randomNumberGenerator.random(1, 2) == 1);
    }

    for(int i = 0; i < 100; i++){
        REQUIRE(randomNumberGenerator.random(1) == 0);
    }
}