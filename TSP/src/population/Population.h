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
public:
    /*!
     * Creates a population object and initializes a list of individuals of the given size.
     * If the given sizes are smaller than 0, 0 is used.
     * @param size_population - population size
     * @param size_chromosome - size of the chromosmes of the individuals
     * @param fct_rating - function to calc the individual rating
     * @param fct_fitness - function to calc the individual fitness
     * @param distances - distance matrix
     */
    Population(int size_population, int size_chromosome, Function_rating fct_rating, Function_fitness fct_fitness,
               std::vector<std::vector<int>> &distances) {
        size_population = size_population < 0 ? 0 : size_population;
        this->distances = distances;
        initialize(size_population, size_chromosome, fct_rating, fct_fitness);
    }

    /*!
     * Creates an empty population
     * @param distances - distance matrix
     */
    explicit Population(std::vector<std::vector<int>> &distances){
        this->distances = distances;
    }

    /*!
     * Initializes the population
     */
    void initialize(int size_population, int size_chromosome, Function_rating fct_rating, Function_fitness fct_fitness);

    /*!
     * Returns the individuals
     * @return vector of individuals
     */
    std::vector<Individual>& get_individuals();

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

    std::vector<std::vector<int>>& get_distances(){
        return distances;
    }

private:
};


#endif //TSP_POPULATION_H
