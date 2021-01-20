//
// Created by Niklas Hartinger on 21.12.2020.
//

#include <iostream>
#include "selection.h"

Population selection_sotf(Population &p_old, Population &p_new) {
    if (p_old.size() != p_new.size()) {
        std::cerr << "Populations have different sizes" << std::endl;
        exit(1);
    }
    int size = (int) p_old.size();

    p_old.calc_population_fitness();
    p_new.calc_population_fitness();

    Population result = Population(p_old.get_idx_start(), p_old.get_distances());

    std::vector<Individual> individuals_old = p_old.get_individuals();
    std::vector<Individual> individuals_new = p_new.get_individuals();

    std::sort(individuals_new.rbegin(), individuals_new.rend());
    std::sort(individuals_old.rbegin(), individuals_old.rend());

    int offset_old = 0;
    int offset_new = 0;
    for (int i = 0; i < size; ++i) {
        if (individuals_old.at(offset_old) < individuals_new.at(offset_new)) {
            result.add_individual(individuals_new.at(offset_new));
            offset_new++;
        } else {
            result.add_individual(individuals_old.at(offset_old));
            offset_old++;
        }
    }

    return result;
}

Population selection_sotf_distinct(Population &p_old, Population &p_new) {
    if (p_old.size() != p_new.size()) {
        std::cerr << "Populations have different sizes" << std::endl;
        exit(1);
    }
    int size = (int) p_old.size();

    p_old.calc_population_fitness();
    p_new.calc_population_fitness();

    Population result = Population(p_old.get_idx_start(), p_old.get_distances());

    std::vector<Individual> individuals_old = p_old.get_individuals();
    std::vector<Individual> individuals_new = p_new.get_individuals();

    std::sort(individuals_new.rbegin(), individuals_new.rend());
    std::sort(individuals_old.rbegin(), individuals_old.rend());

    unsigned int offset_old = 0;
    unsigned int offset_new = 0;
    for (int i = 0; i < size; ++i) {
        if(offset_old < individuals_old.size() && offset_new < individuals_new.size()){
            if (individuals_old.at(offset_old) < individuals_new.at(offset_new)) {
                if(result.size() == 0 || individuals_new.at(offset_new).get_chromosome() != result.get_individuals().at(result.size()-1).get_chromosome()){
                    result.add_individual(individuals_new.at(offset_new));
                }else{
                    i--;
                }
                offset_new++;
            } else {
                if(result.size() == 0 || individuals_old.at(offset_old).get_chromosome() != result.get_individuals().at(result.size()-1).get_chromosome()) {
                    result.add_individual(individuals_old.at(offset_old));
                }else{
                    i--;
                }
                offset_old++;
            }
        }else if(offset_old < individuals_old.size()){
            if(result.size() == 0 || individuals_old.at(offset_old).get_chromosome() != result.get_individuals().at(result.size()-1).get_chromosome()){
                result.add_individual(individuals_old.at(offset_old));
            }else{
                i--;
            }
            offset_old++;
        }else if(offset_new < individuals_new.size()) {
            if(result.size() == 0 || individuals_new.at(offset_new).get_chromosome() != result.get_individuals().at(result.size()-1).get_chromosome()) {
                result.add_individual(individuals_new.at(offset_new));
            }else{
                i--;
            }
            offset_new++;
        }else{
            Individual unique_individual = create_unique_individual(result);
            result.add_individual(unique_individual);
        }
    }
    return result;
}