//
// Created by Niklas Hartinger on 14.12.2020.
//

#ifndef TSP_POPULATION_H
#define TSP_POPULATION_H

#include <vector>
#include <ctime>

#include <individual/Individual.h>

/*!
 * This class implements the population. A population hold a list of individuals
 */
class Population {
    std::vector<Individual> individuals;
    int last_fitness = 0;
    std::vector<std::vector<int>> distances;
    int idx_start;
public:
    /*!
     * Creates a population object and initializes a list of individuals of the given size.
     * If the given sizes are smaller than 0, 0 is used.
     * @param size_population - population size
     * @param size_chromosome - size of the chromosmes of the individuals
     * @param idx_start - index of start city
     * @param fct_rating - function to calc the individual rating
     * @param fct_fitness - function to calc the individual fitness
     * @param distances - distance matrix
     */
    Population(int size_population, int size_chromosome, int idx_start, Function_rating fct_rating,
               Function_fitness fct_fitness,
               std::vector<std::vector<int>> &distances) {
        size_population = size_population < 0 ? 0 : size_population;
        this->distances = distances;
        this->idx_start = idx_start;
        initialize(size_population, size_chromosome, fct_rating, fct_fitness);
    }

    /*!
     * Creates an empty population
     * @param distances - distance matrix
     */
    Population(int idx_start, std::vector<std::vector<int>> &distances) {
        this->idx_start = idx_start;
        this->distances = distances;
    }

    Population()= default;

    /*!
     * Initializes this population
     * @param size_population - size of the population
     * @param size_chromosome - size of each chromosome
     * @param idx_start - start city
     * @param fct_rating - function to calc the rating
     * @param fct_fitness - function to calc the fitness
     */
    void initialize(int size_population, int size_chromosome, Function_rating fct_rating, Function_fitness fct_fitness);

    /*!
     * Returns the individuals
     * @return vector of individuals
     */
    std::vector<Individual> &get_individuals();

    /*!
     * Calculates the fitness of the population
     * @return
     */
    int calc_population_fitness();

    /*!
     * Return the last calculated fitness. Only use if you are sure that the individuals did not changed.
     * @return fitness
     */
    int get_last_calculates_population_fitness() const;

    /*!
     * Adds an individual to the population.
     * @param individual
     */
    void add_individual(Individual &individual);

    unsigned int size() const {
        return individuals.size();
    }

    /*!
     * Returns the index of the start city of this population.
     * @return
     */
    int get_idx_start() const {
        return idx_start;
    }

    std::vector<std::vector<int>> &get_distances() {
        return distances;
    }

    /*!
     * Returns individual with the highest fitness of the population
     * @return individual
     */
    Individual get_highest_fitness_individual();

    /*!
     * Returns individual with the lowest fitness of the population
     * @return individual
     */
    Individual get_lowest_fitness_individual();
private:
};


#endif //TSP_POPULATION_H
