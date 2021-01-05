//
// Created by Niklas Hartinger on 29.12.2020.
//
#include <catch.hpp>
#include <simulation/Simulator.h>

SCENARIO("Test Simulator", "[simulation.cpp]") {

    std::string file_distances = "../../data/cities/distances";
    std::string file_labels = "../../data/cities/labels";

    std::string start_city = "Giessen";
    int number_cities = 59;
    int population_size = 10;
    int epochs = 10;
    int mutation_rate = 10;
    Simulator simulator = Simulator(file_labels, file_distances, start_city,
                                    number_cities, population_size, epochs, mutation_rate,
                                    Crossover_Algorithms::Edge_Recombination, Marriage_Algorithms::Roulette_Reversed,
                                    Mutation_Algorithms::Delete_Shift, Selection_Algorithms::SOFT_Reversed);
    for (int i = 0; i < epochs; ++i) {
        REQUIRE(!simulator.finished());
        simulator.simulate();
    }
    REQUIRE(simulator.finished());
}