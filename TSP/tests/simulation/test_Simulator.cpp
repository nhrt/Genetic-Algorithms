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
    int epochs = 200;
    int mutation_rate = 10;
    Simulator simulator = Simulator(file_labels, file_distances, start_city,
                                    number_cities, population_size, epochs, mutation_rate,
                                    Crossover_Algorithms::Edge_Recombination, Marriage_Algorithms::Roulette_Reversed,
                                    Mutation_Algorithms::Delete_Shift, Selection_Algorithms::SOFT_Reversed);
    bool print = true;
    for (int i = 0; i < epochs; ++i) {
        REQUIRE(!simulator.finished());
        auto result = simulator.simulate();
        if(print){
            std::cout << "Epoch: " << i << std::endl <<
                      "Highest distance: " << std::get<0>(result) << std::endl <<
                      "Lowest distance: " << std::get<1>(result) << std::endl <<
                      "Average distance: " << std::get<2>(result) << std::endl << std::endl;
        }
    }
    REQUIRE(simulator.finished());
}