//
// Created by Niklas Hartinger on 14.12.2020.
//

#include "utility.h"

int get_distance(int city_a, int city_b, std::vector<std::vector<int>> &distances) {
    return distances.at(city_a).at(city_b);
}

int cost_function(int idx_start, std::vector<int> &chromosome, std::vector<std::vector<int>> &distances) {
    int city_a, city_b;
    int costs = 0;

    costs += get_distance(idx_start, 0, distances);
    for (unsigned int i = 0; i < chromosome.size() - 1; ++i) {
        city_a = chromosome.at(i);
        city_b = chromosome.at(i + 1);
        costs += get_distance(city_a, city_b, distances);
    }
    costs += get_distance(chromosome.at(chromosome.size() - 1), idx_start, distances);

    return costs;
}

double rating(int idx_start, std::vector<int> &chromosome, std::vector<std::vector<int>> &distances) {
    int tmp = cost_function(idx_start, chromosome, distances);
    return tmp != 0 ? 1.0 / tmp * MAX_COSTS : 0;
}

double fitness(double rating) {
    return rating;
}

int find_duplicate(std::vector<int> &chromosome) {
    std::unordered_set<int> set;
    int n = chromosome.size();
    for (int i = 0; i < n; ++i) {
        int value = chromosome.at(i);
        auto it = set.insert(value);
        if (!it.second) {
            return i;
        }
    }
    return -1;
}

void swap_chromosome(std::vector<int> &i, int idx_a, int idx_b) {
    if (idx_a < 0 || idx_b < 0 || (unsigned int) idx_a >= i.size() || (unsigned int) idx_b >= i.size()) {
        std::cerr << "Index out of bounds while swapping values" << std::endl;
        exit(1);
    }

    int a = i.at(idx_a);
    int b = i.at(idx_b);
    i.at(idx_a) = b;
    i.at(idx_b) = a;
}

void shift_left(std::vector<int> &vector, int idx_start, int idx_end) {
    if (idx_start < 0 || idx_end < 0 || (unsigned int) idx_start >= vector.size() ||
        (unsigned int) idx_end >= vector.size()) {
        std::cerr << "Index out of bounds while swapping values" << std::endl;
        exit(1);
    }
    if (idx_start >= idx_end) {
        std::cerr << "Start index must be smaller than end index" << std::endl;
        exit(1);
    }

    for (int i = idx_start; i < idx_end; i++) {
        swap_chromosome(vector, i, i + 1);
    }

}

double fitness_reversed(double rating_reversed) {
    return -rating_reversed;
}

double rating_reversed(int idx_start, std::vector<int> &chromosome, std::vector<std::vector<int>> &distances) {
    return cost_function(idx_start, chromosome, distances);
}
