//
// Created by Niklas Hartinger on 29.12.2020.
//
#include <catch.hpp>
#include <simulation/simulation.h>

SCENARIO("Test simulation", "[simulation.cpp]") {

    std::string file_distances = "../../data/cities/distances";
    std::string file_labels = "../../data/cities/labels";

    std::string start_city = "Giessen";
    int number_cities = 59;
    int population_size = 10;
    int epochs = 1000;
    int mutation_rate = 5;

    int result = simulate(file_labels, file_distances, start_city, number_cities, population_size, epochs,
                          mutation_rate, Crossover_Algorithms::Partially_Matched, Marriage_Algorithms::Roulette,
                          Mutation_Algorithms::Delete_Shift,
                          Selection_Algorithms::SOFT);

    std::cout << result << std::endl;
}