//
// Created by Niklas Hartinger on 15.12.2020.
//
#include <map>
#include <unordered_map>
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


bool chromosomes_usable(unsigned int minimum_size, Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    return !((unsigned int) p1.get_size() < minimum_size ||
             p1.get_size() != p2.get_size() ||
             c1.get_size() != c2.get_size() ||
             p1.get_size() != c1.get_size());
}

bool partially_matched_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    if (!chromosomes_usable(3, p1, p2, c1, c2)) {
        return false;
    }
    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    int length = (int) p1.get_size();
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

/*!
 * Helper function for the order crossover to set the duplicate flags.
 * @param map - Map which contains the information which value is at what position inside the other parent's interval
 * @param child - child individual, function sets duplicate flags on the correct position
 * @param parent - parent individual
 * @param chromosome_cache - in this cache the function writes the information on which position is a duplicate and on which position is not a duplicate
 * @param interval_border_left - left border of the interval
 * @param interval_border_right - right border of the interval
 */
void set_duplicate_flags(std::unordered_map<int, int> &map, Individual &child, Individual &parent,
                         std::vector<int> &chromosome_cache, int interval_border_left, int interval_border_right) {
    chromosome_cache.resize(child.get_size());
    for (int i = 0; i < child.get_size(); ++i) {
        if (i < interval_border_left || i >= interval_border_right) {
            if (map.find(parent.get_chromosome().at(i)) != map.end()) {
                chromosome_cache.at(i) = DUPLICATE_FLAG;
                child.update_chromosome(DUPLICATE_FLAG, map[parent.get_chromosome().at(i)]);
            } else {
                chromosome_cache.at(i) = parent.get_chromosome().at(i);
            }

        } else {
            chromosome_cache.at(i) = parent.get_chromosome().at(i);
        }
    }
}

/*!
 * Helper function for the order crossover to set the correct values into the child.
 * @param child - child individual
 * @param chromosome_cache - result cache of function <set_duplicate_flags>
 * @param interval_border_left - left border of the interval
 */
void set_other_values(Individual &child, std::vector<int> &chromosome_cache, int interval_border_left) {
    int offset = interval_border_left;
    for (int i = 0; i < child.get_size(); ++i) {
        int current = chromosome_cache.at(offset);
        while (current == DUPLICATE_FLAG) {
            offset++;
            if (offset >= child.get_size()) {
                offset = 0;
            }
            current = chromosome_cache.at(offset);
        }
        while (child.get_chromosome().at(i) == DUPLICATE_FLAG) {
            i++;
        }
        child.get_chromosome().at(i) = current;
        offset++;
        if (offset >= child.get_size()) {
            offset = 0;
        }
    }
}

bool order_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    if (!chromosomes_usable(3, p1, p2, c1, c2)) {
        return false;
    }

    int length = (int) p1.get_size();
    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    int interval_border_left = rng.random(length - 2) + 1; // inclusive
    int interval_border_right; // exclusive
    do {
        interval_border_right = rng.random(length / 2 - 1) + 1 + interval_border_left;
    } while (interval_border_right >= length);

    std::unordered_map<int, int> map_p1, map_p2;
    for (int i = interval_border_left; i < interval_border_right; ++i) {
        map_p1.insert(std::pair<int, int>(p1.get_chromosome().at(i), i));
        map_p2.insert(std::pair<int, int>(p2.get_chromosome().at(i), i));
    }

    std::vector<int> cache1, cache2;
    set_duplicate_flags(map_p2, c1, p1, cache1, interval_border_left, interval_border_right);
    set_duplicate_flags(map_p1, c2, p2, cache2, interval_border_left, interval_border_right);

    set_other_values(c1, cache1, interval_border_left);
    set_other_values(c2, cache2, interval_border_left);

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

std::map<int, std::set<int>> create_edge_map(Individual &p1, Individual &p2) {
    std::map<int, std::set<int>> edge_map;
    std::set<Individual *> parents = {&p1, &p2};
    for (auto parent : parents) {
        for (int i = 0; i < (int) parent->get_size() - 1; ++i) {
            int city_a = parent->get_chromosome().at(i);
            int city_b = parent->get_chromosome().at(i + 1);
            edge_map[city_a].insert(city_b);
            edge_map[city_b].insert(city_a);

            if (i == 0) {
                edge_map[city_a].insert(EDGE_TO_START);
            } else if (i + 1 == (int) parent->get_size() - 1) {
                edge_map[city_b].insert(EDGE_TO_START);
            }

        }
    }
    return edge_map;
}

void edge_recombination(Individual &i, std::map<int, std::set<int>> edge_map) {
    int idx = 0;
    int current_city;

    std::pair<int, std::set<int>> least_edges = *edge_map.begin();
    for (auto &city : edge_map) {
        if (least_edges.second.size() > city.second.size()) {
            least_edges = city;
        }
    }
    current_city = least_edges.first;
    Random_Number_Generator &rng = Random_Number_Generator::getInstance();
    bool finished = false;
    while (!finished) {
        i.update_chromosome(current_city, idx);
        idx++;
        edge_map.erase(current_city);
        if (edge_map.empty()) {
            finished = true;
        } else {
            least_edges = *edge_map.begin();
            for (auto &city : edge_map) {
                city.second.erase(current_city);
                if (least_edges.second.size() > city.second.size()) {
                    least_edges = city;
                } else if (least_edges.second.size() == city.second.size()) {
                    if (rng.random(2) == 0) {
                        least_edges = city;
                    }
                }
            }
            current_city = least_edges.first;
        }
    }
}

bool edge_recombination_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    if (!chromosomes_usable(1, p1, p2, c1, c2)) {
        return false;
    }
    std::map<int, std::set<int>> edge_map = create_edge_map(p1, p2);
    edge_recombination(c1, edge_map);
    edge_recombination(c2, edge_map);

    return true;
}

/*!
 * Linearly searches for a given element in a given vector and returns the index at which the value was found.
 * Returns -1 if the value could not be found.
 * @param vec vector to search
 * @param val value to find
 * @return index of val within vec or -1
 */
int vector_find(std::vector<int> vec, int val) {
    for (int i = 0; (unsigned int) i < vec.size(); ++i) {
        if (vec.at(i) == val)
            return i;
    }
    return -1;
}

typedef std::tuple<int, int, int> Tuple;
typedef std::vector<std::tuple<int, int, int>> Cycle;

/*!
 * Identifies a cycle within the chromosomes of the two parents starting at the given index.
 * The given cycle must be empty, the chromosomes of the two parents must consist of the same set of values (no recurring values) and the flags for all indices forming the cycle must not be set.
 * @param cycle empty cycle to fill with tuples
 * @param cycle_start_idx start index of the cycle to fill
 * @param p1 first parent
 * @param p2 second parent
 * @param index_flags indicate whether a value at a certain index is already part of a cycle
 * @return
 */
bool fill_empty_cycle_with_tuples(Cycle &cycle, int cycle_start_idx, Individual &p1, Individual &p2,
                                  std::vector<bool> &index_flags) {
    if (p1.get_size() != p2.get_size() || index_flags.size() < (unsigned int) p1.get_size()) {

        std::cout << "chromosomes must consist be of the same length." << std::endl;
        return false;
    }
    if (!cycle.empty()) {
        std::cout << "cycle to be filled is not empty." << std::endl;
        return false;
    }
    if (index_flags.at(cycle_start_idx)) {
        std::cerr << "index indicating the cycle start is already part of another cycle." << std::endl;
        return false;
    }

    int idx = cycle_start_idx;
    do {
        index_flags.at(idx) = true;
        int v1 = p1.get_chromosome().at(idx);
        int v2 = p2.get_chromosome().at(idx);
        cycle.emplace_back(idx, v1, v2);
        idx = vector_find(p1.get_chromosome(), v2);
        if (idx == -1) {
            std::cerr
                    << "chromosome value of second parent cannot be found in first parent chromosome. chromosomes must consist of the same set of values."
                    << std::endl;
            return false;
        }
    } while (!index_flags.at(idx));

    if (idx != cycle_start_idx) {
        std::cerr
                << "incomplete cycle built. the flags for the values' indices must not be previously occupied. a value must not occur twice within a chromosome."
                << std::endl;
        return false;
    }

    return true;
}

bool cycle_crossover_all_cycles(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    if (!chromosomes_usable(3, p1, p2, c1, c2)) {
        return false;
    }

    // mark whether the values at a certain index are already part of another cycle
    std::vector<bool> index_flags(p1.get_size(), false);

    // identify cycles within the chromosome values of the first and second parent
    std::vector<Cycle> cycles;
    for (int cycle_start_idx = 0; cycle_start_idx < p1.get_size(); ++cycle_start_idx) {
        Cycle cycle;
        if (!index_flags.at(cycle_start_idx)) {
            if (!fill_empty_cycle_with_tuples(cycle, cycle_start_idx, p1, p2, index_flags)) {
                return false;
            }
            cycles.push_back(cycle);
        }
    }

    // copy alternate cycles to the children
    for (int i = 0; (unsigned int) i < cycles.size(); ++i) {
        bool cross_copy = i % 2 != 0;
        Cycle &cycle = cycles.at(i);
        for (Tuple &t : cycle) {
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
    if (!chromosomes_usable(3, p1, p2, c1, c2)) {
        return false;
    }

    // mark whether the values at a certain index are already part of the cycle
    std::vector<bool> index_flags(p1.get_size(), false);

    // identify one random cycle within the chromosome values of the first and second parent
    Cycle cycle;
    int cycle_start_idx = Random_Number_Generator::getInstance().random((int) p1.get_size());
    if (!fill_empty_cycle_with_tuples(cycle, cycle_start_idx, p1, p2, index_flags)) {
        return false;
    }

    // create children by copying values of the cycle from p1 to c1 and p2 to c2 and changing the copy direction for all other values of the chromosome
    int tupleCounter = 0;
    for (int i = 0; (unsigned int) i < index_flags.size(); ++i) {
        bool flag = index_flags.at(i);
        if (flag) {
            Tuple &t = cycle.at(tupleCounter);
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
