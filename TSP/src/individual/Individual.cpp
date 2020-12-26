//
// Created by Niklas Hartinger on 14.12.2020.
//


#include "Individual.h"

void Individual::initialize(int idx_start) {
    // check if idx_start is valid
    if (idx_start > size + 1) {
        std::cerr << "idx_start is not valid in Individual::initialize(int idx_start)" << std::endl;
        exit(1);
    }

    // insert idxs of cities to visit
    int chromosome_idx = 0;
    for (int i = 0; i <= size; ++i) {
        if (i != idx_start) {
            chromosome.at(chromosome_idx) = i;
            chromosome_idx++;
        }
    }
    // shuffle chromosome
    for (int i = ((int) chromosome.size()) - 1; i > 0; --i) {
        int j = Random_Number_Generator::getInstance().random(0, i + 1);
        swap_chromosome(chromosome, i, j);
    }
}

bool Individual::is_valid(int idx_end) {
    std::set<int> set;
    for (int i = 0; i <= idx_end; ++i) {
        if (!set.insert(chromosome.at(i)).second) {
            return false;
        }
    }
    return true;
}

bool Individual::is_valid() {
    std::set<int> set;
    for (int i = 0; i < size; ++i) {
        if (!set.insert(chromosome.at(i)).second) {
            return false;
        }
    }
    return true;
}

std::vector<int> &Individual::get_chromosome() {
    return chromosome;
}

bool Individual::update_chromosome(int update, int idx) {
    if (idx < 0 || (unsigned int) idx >= chromosome.size()) {
        return false;
    }
    chromosome.at(idx) = update;
    return true;
}

bool Individual::update_chromosome(std::vector<int> &update) {
    if (update.size() != chromosome.size())
        return false;
    for (unsigned int i = 0; i < update.size(); ++i) {
        chromosome.at(i) = update.at(i);
    }
    return true;
}

double Individual::fitness(int idx_start, std::vector<std::vector<int>> &distances) {
    if (func_fitness != nullptr && size > 0) {
        last_fitness = func_fitness(rating(idx_start, distances));
        return last_fitness;
    }
    return -1;
}

double Individual::rating(int idx_start, std::vector<std::vector<int>> &distances) {
    if (func_rating != nullptr && size > 0) {
        return func_rating(idx_start, chromosome, distances);
    }
    return -1;
}

int Individual::get_size() const {
    return size;
}

double Individual::get_last_calculates_fitness() const {
    return last_fitness;
}

void Individual::print() const {
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        std::cout << chromosome.at(i);
        if (i < size-1) {
            std::cout << " -> ";
        }
    }
    std::cout << "]" << std::endl;
}