//
// Created by Niklas Hartinger on 16.12.2020.
//

#ifndef TSP_RANDOM_NUMBER_GENERATOR_H
#define TSP_RANDOM_NUMBER_GENERATOR_H

#include <random>
#include <chrono>
#include <iostream>

/*!
 * This class implements the functionality of generating random numbers in the C++11 way.
 * To guarantee that the random seed is only set once, this Generator is implemented as a singleton.
 */
class Random_Number_Generator {
public:

    /*!
     * Returns a Random Number Generator reference.
     * @return Random Number Generator reference
     */
    static Random_Number_Generator &getInstance() {
        static Random_Number_Generator instance;
        return instance;
    }

    /*!
     * Calculates a random number between two values.
     * @param min_inclusive - minimum possible result
     * @param max_exclusive - max_exclusive-1 = maximum possible result
     * @return random number
     */
    int random(int min_inclusive, int max_exclusive) {
        std::uniform_int_distribution<int> intDistro(min_inclusive, max_exclusive - 1);
        return intDistro(defEngine);
    }

    /*!
     * Calculates a random number between 0 and a given value.
     * @param max_exclusive - max_exclusive-1 = maximum possible result
     * @return random number
     */
    int random(int max_exclusive) {
        std::uniform_int_distribution<int> intDistro(0, max_exclusive - 1);
        return intDistro(defEngine);
    }

    Random_Number_Generator(Random_Number_Generator const &) = delete;

    void operator=(Random_Number_Generator const &) = delete;

private:
    std::default_random_engine defEngine;

    Random_Number_Generator() {
        defEngine = std::default_random_engine(std::chrono::steady_clock::now().time_since_epoch().count());
    }
};


#endif //TSP_RANDOM_NUMBER_GENERATOR_H
