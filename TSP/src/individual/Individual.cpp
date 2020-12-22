//
// Created by Niklas Hartinger on 14.12.2020.
//


#include "Individual.h"

void Individual::initialize() {
    for (int c = 0; c < size; ++c) {
        bool finished = false;
        while (!finished) {
            int city = rand() % size;
            chromosome.at(c) = city;
            finished = is_valid(c);
        }
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

double Individual::fitness(std::vector<std::vector<int>> &distances) {
    if (func_fitness != nullptr && size > 0) {
        last_fitness = func_fitness(rating(distances));
        return last_fitness;
    }
    return -1;
}

double Individual::rating(std::vector<std::vector<int>> &distances) {
    if (func_rating != nullptr && size > 0) {
        return func_rating(chromosome, distances);
    }
    return -1;
}

int Individual::get_size() const {
    return size;
}

double Individual::get_last_calculates_fitness() const {
    return last_fitness;
}