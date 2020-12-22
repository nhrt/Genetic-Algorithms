//
// Created by Niklas Hartinger on 14.12.2020.
//

#ifndef TSP_INDIVIDUAL_H
#define TSP_INDIVIDUAL_H


#include <vector>
#include <algorithm>
#include <set>

typedef double (*Function_rating)(std::vector<int> &, std::vector<std::vector<int>> &);

typedef double (*Function_fitness)(double);

/*!
 * Class implements an individual
 */
class Individual {
private:
    std::vector<int> chromosome;
    int size;
    Function_fitness func_fitness;
    Function_rating func_rating;
    double last_fitness = 0;
public:
    /*!
     * Creates a Individual object and initializes it with random informations.
     * Resulting Individual is valid.
     * @param size - size of the chromosome
     * @param function_rating - function to calc the rating (dependency injection)
     * @param function_fitness - function to calc the fitness (dependency injection)
     * @param initialize_chromosome - initializes the chromosome with random valid values when true
     */
    Individual(int size, Function_rating function_rating, Function_fitness function_fitness,
               bool initialize_chromosome = true) {
        if (size < 0) size = 0;
        chromosome.resize(size);
        this->size = size;
        func_fitness = function_fitness;
        func_rating = function_rating;

        if (initialize_chromosome)
            initialize();
    }

    /*!
     * Initializes the chromosome with random valid informations
     */
    void initialize();

    /*!
     * Checks if a chromosome is valid. It is valid if every value inside the chromosome vector is unique.
     * @param idx_end - position up to which is checked, idx_end is inclusive
     * @return true = valid, false = invalid
     */
    bool is_valid(int idx_end);

    /*!
    * Checks if a chromosome is valid. It is valid if every value inside the chromosome vector is unique.
    * @return true = valid, false = invalid
    */
    bool is_valid();

    /*!
     * Returns the chromosome
     * @return chromosome - the chromosome vector
     */
    std::vector<int> &get_chromosome();

    /*!
     * Return the chromosome size
     * @return chromosome size
     */
    int get_size() const;

    /*!
     * Overwrites the individual chromosome with the values inside the update vector.
     * Update vector must have the same size as the chromosome vector.
     * NO VALIDATION IS DONE HERE.
     * @param update - update values for the chromosome
     * @return true = success, false = no success
     */
    bool update_chromosome(std::vector<int> &update);

    /*!
     * Overwrites the individual chromosome on position idx with the value update.
     * NO VALIDATION IS DONE HERE.
     * @param update - new chromosome value
     * @param idx - idx of the chromosome
     * @return true = success, false = no success
     */
    bool update_chromosome(int update, int idx);

    /*!
     * Calculates the fitness of the individual.
     * @return fitness value
     */
    double fitness(std::vector<std::vector<int>> &distances);

    /*!
     * Calculates the rating of the individual.
     * @return rating value
     */
    double rating(std::vector<std::vector<int>> &distances);

    /*!
    * Return the last calculated fitness. Only use if you are sure the individuals did not change.
    * @return fitness
    */
    double get_last_calculates_fitness() const;

    bool operator < (const Individual &i) const {
        return get_last_calculates_fitness() < i.get_last_calculates_fitness();
    }
};


#endif //TSP_INDIVIDUAL_H
