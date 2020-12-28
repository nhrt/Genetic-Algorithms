//
// Created by Niklas Hartinger on 15.12.2020.
//
#include "crossover.h"


void duplicate_correction_pmx(Individual &p1, Individual &p2, Individual &c) {
    int value_non_unique, idx_non_unique, idx_p, value_p;
    idx_non_unique = find_duplicate(c.get_chromosome());
    while (idx_non_unique >= 0) {
        value_non_unique = c.get_chromosome().at(idx_non_unique);
        idx_p = std::find(p2.get_chromosome().begin(), p2.get_chromosome().end(), value_non_unique) -
                p2.get_chromosome().begin();
        value_p = p1.get_chromosome().at(idx_p);
        c.update_chromosome(value_p, idx_non_unique);
        idx_non_unique = find_duplicate(c.get_chromosome());
    }
}

bool chromosomes_usable(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    return !(p1.get_chromosome().size() < 3 ||
             p1.get_chromosome().size() != p2.get_chromosome().size() ||
             c1.get_chromosome().size() != c2.get_chromosome().size() ||
             p1.get_chromosome().size() != c1.get_chromosome().size());
}

bool partially_matched_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    if (!chromosomes_usable(p1, p2, c1, c2)) {
        return false;
    }
    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    int length = p1.get_chromosome().size();
    int interval_border_left = rng.random(length - 2) + 1; // inclusive
    int interval_border_right; // exclusive

    do {
        interval_border_right = rng.random(length - interval_border_left) + interval_border_left;
    } while (interval_border_left == interval_border_right);

    for (int i = 0; i < length; ++i) {
        if (i < interval_border_left || i >= interval_border_right) {
            c1.update_chromosome(p1.get_chromosome().at(i), i);
            c2.update_chromosome(p2.get_chromosome().at(i), i);
        } else {
            c1.update_chromosome(p2.get_chromosome().at(i), i);
            c2.update_chromosome(p1.get_chromosome().at(i), i);
        }
    }

    duplicate_correction_pmx(p1, p2, c1);
    duplicate_correction_pmx(p2, p1, c2);

    return true;
}

bool order_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    if (!chromosomes_usable(p1, p2, c1, c2)) {
        return false;
    }
    int length = p1.get_chromosome().size();
    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    int interval_border_left = rng.random(length - 2) + 1; // inclusive
    int interval_border_right; // exclusive

    do {
        interval_border_right = rng.random(length / 2 - 1) + 1 + interval_border_left;
    } while (interval_border_right >= length);

    std::unordered_set<int> set_c1, set_c2;

    for (int i = interval_border_left; i < interval_border_right; ++i) {
        set_c1.insert(p1.get_chromosome().at(i));
        set_c2.insert(p2.get_chromosome().at(i));
    }
    for (int i = 0; i < length; ++i) {
        if (set_c2.find(p1.get_chromosome().at(i)) != set_c2.end()) {
            c1.update_chromosome(DUPLICATE_FLAG, i);
        } else {
            c1.update_chromosome(p1.get_chromosome().at(i), i);
        }
        if (set_c1.find(p2.get_chromosome().at(i)) != set_c1.end()) {
            c2.update_chromosome(DUPLICATE_FLAG, i);
        } else {
            c2.update_chromosome(p2.get_chromosome().at(i), i);
        }
    }

    int offset, i;
    for (i = interval_border_left, offset = 0; i < interval_border_right && offset < length; ++i) {
        swap_chromosome(c1.get_chromosome(), offset, i);
        swap_chromosome(c2.get_chromosome(), offset, i);
        offset++;
        if (offset == interval_border_left) {
            offset = interval_border_right;
        }
    }

    int offset_interval_c1 = interval_border_left;
    int offset_interval_c2 = interval_border_left;

    for (int j = 0; j < length; ++j) {
        if (j < interval_border_left || j >= interval_border_right) {
            if (c1.get_chromosome().at(j) == DUPLICATE_FLAG) {
                swap_chromosome(c1.get_chromosome(), j, offset_interval_c1);
                do {
                    ++offset_interval_c1;
                } while (c1.get_chromosome().at(offset_interval_c1) == DUPLICATE_FLAG);
            }

            if (c2.get_chromosome().at(j) == DUPLICATE_FLAG) {
                swap_chromosome(c2.get_chromosome(), j, offset_interval_c2);
                do {
                    offset_interval_c2++;
                } while (c2.get_chromosome().at(offset_interval_c2) == DUPLICATE_FLAG);
            }
        }
    }
    for (int j = interval_border_left; j < interval_border_right; ++j) {
        if (c1.get_chromosome().at(j) == DUPLICATE_FLAG) {
            c1.update_chromosome(p2.get_chromosome().at(j), j);
        }
        if (c2.get_chromosome().at(j) == DUPLICATE_FLAG) {
            c2.update_chromosome(p1.get_chromosome().at(j), j);
        }
    }

    return true;
}

int vector_find(std::vector<int> vec, int val) {
    for (int i = 0; (unsigned int)  i < vec.size(); ++i) {
        if (vec.at(i) == val)
            return i;
    }
    return -1;
}

bool cycle_crossover_all_cycles(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    // mark whether the values at a certain index are already part of another cycle
    std::vector<bool> index_flags(p1.get_chromosome().size(), false);

    // identify cycles within the chromosome values of the first and second parent
    std::vector<std::vector<std::tuple<int, int, int>>> cycles;
    int cycle_start;
    for (int i = 0; (unsigned int) i < p1.get_chromosome().size(); ++i) {
        std::vector<std::tuple<int, int, int>> cycle;
        if (!index_flags.at(i)) {
            cycle_start = i;

            int idx = cycle_start;
            do {
                index_flags.at(idx) = true;
                int v1 = p1.get_chromosome().at(idx);
                int v2 = p2.get_chromosome().at(idx);
                cycle.emplace_back(idx, v1, v2);
                idx = vector_find(p1.get_chromosome(), v2);
                if (idx == -1) {
                    std::cerr << "chromosome value of second parent cannot be found in first parent chromosome in cycle_crossover_all_cycles(Individual &p1, Individual &p2, Individual &c1, Individual &c2)" << std::endl;
                    return false;
                }
            } while (!index_flags.at(idx));

            cycles.push_back(cycle);
        }
    }

    // copy alternate cycles to the children
    for (int i = 0; (unsigned int) i < cycles.size(); ++i) {
        bool cross_copy = i % 2 != 0;
        std::vector<std::tuple<int, int, int>> &values_at_index = cycles.at(i);
        for (std::tuple<int, int, int> &t : values_at_index) {
            if (cross_copy) {
                c1.update_chromosome(std::get<2>(t), std::get<0>(t));
                c2.update_chromosome(std::get<1>(t), std::get<0>(t));
            } else {
                c1.update_chromosome(std::get<1>(t), std::get<0>(t));
                c2.update_chromosome(std::get<2>(t), std::get<0>(t));
            }
        }
    }

    return true;
}

bool cycle_crossover_one_cycle(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    // mark whether the values at a certain index are already part of the cycle
    std::vector<bool> index_flags(p1.get_chromosome().size(), false);

    // identify one random cycle within the chromosome values of the first and second parent
    std::vector<std::tuple<int, int, int>> cycle;
    int cycle_start = Random_Number_Generator::getInstance().random(p1.get_chromosome().size());
    int idx = cycle_start;
    do {
        index_flags.at(idx) = true;
        int v1 = p1.get_chromosome().at(idx);
        int v2 = p2.get_chromosome().at(idx);
        cycle.emplace_back(idx, v1, v2);
        idx = vector_find(p1.get_chromosome(), v2);
        if (idx == -1) {
            std::cerr << "chromosome value of second parent cannot be found in first parent chromosome in cycle_crossover_one_cycle(Individual &p1, Individual &p2, Individual &c1, Individual &c2)" << std::endl;
            return false;
        }
    } while (!index_flags.at(idx));

    // create children by copying values of the cycle from p1 to c1 and p2 to c2 and changing the copy direction for all other values of the chromosome
    int tupleCounter = 0;
    for (int i = 0; (unsigned int) i < index_flags.size(); ++i) {
        bool flag = index_flags.at(i);
        if (flag) {
            std::tuple<int, int, int> &t = cycle.at(tupleCounter);
            tupleCounter++;
            c1.update_chromosome(std::get<1>(t), std::get<0>(t));
            c2.update_chromosome(std::get<2>(t), std::get<0>(t));
        } else {
            c1.update_chromosome(p2.get_chromosome().at(i), i);
            c2.update_chromosome(p1.get_chromosome().at(i), i);
        }
    }

    return true;
}
