//
// Created by Niklas Hartinger on 15.12.2020.
//
#include <map>
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
    return !(p1.get_chromosome().size() < minimum_size ||
             p1.get_chromosome().size() != p2.get_chromosome().size() ||
             c1.get_chromosome().size() != c2.get_chromosome().size() ||
             p1.get_chromosome().size() != c1.get_chromosome().size());
}

bool partially_matched_crossover(Individual &p1, Individual &p2, Individual &c1, Individual &c2) {
    if (!chromosomes_usable(3, p1, p2, c1, c2)) {
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
    if (!chromosomes_usable(3, p1, p2, c1, c2)) {
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
            } else if (i + 1 == parent->get_size() - 1) {
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