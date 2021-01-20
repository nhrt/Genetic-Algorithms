//
// Created by Niklas Hartinger on 29.12.2020.
//
#include <catch.hpp>
#include <simulation/Simulator.h>

SCENARIO("Test Simulator", "[simulation.cpp]") {

    std::string file_distances = "../../data/cities/att48_d.txt";
    std::string file_positions = "../../data/cities/att48_xy.txt";

    int start_city = 0;
    int number_cities = 48;
    int population_size = 10;
    int generations = 1000;
    int mutation_rate = 10;
    Simulator simulator = Simulator(file_positions, file_distances, start_city,
                                    number_cities, population_size, generations, mutation_rate,
                                    Crossover_Algorithm::Edge_Recombination, Marriage_Algorithm::Roulette_Reversed,
                                    Mutation_Algorithm::Delete_Shift, Selection_Algorithm::SOFT);
    bool print = false;
    for (int i = 0; i < generations; ++i) {
        REQUIRE(!simulator.finished());
        auto result = simulator.simulate();
        if(print){
            std::cout << "Generation: " << i << std::endl <<
                      "Highest distance: " << -std::get<0>(result) << std::endl <<
                      "Lowest distance: " << -std::get<1>(result) << std::endl <<
                      "Average distance: " << -std::get<2>(result) << std::endl << std::endl;
        }
    }
    REQUIRE(simulator.finished());
}