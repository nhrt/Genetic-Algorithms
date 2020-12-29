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
    int population_size = 100;
    int epochs = 1000;
    int mutation_rate = 5;
    int crossover_algorithm = 0;
    int marriage_algorithm = 0;
    int mutation_algorithm = 0;
    int selection_algotihm = 0;

    int result = simulate(file_labels, file_distances, start_city, number_cities, population_size,
                          epochs,
                          mutation_rate, crossover_algorithm, marriage_algorithm, mutation_algorithm,
                          selection_algotihm);

    std::cout << result << std::endl;
}