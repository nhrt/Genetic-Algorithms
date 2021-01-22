//
// Created by Niklas Hartinger on 14.12.2020.
//
#include <catch.hpp>
#include <util/read_cities.h>

SCENARIO("Test Utility Read Cities", "[test_util_read_distances.cpp],[test_util_read_names.cpp]")
{
    std::vector<std::vector<int>> distances;
    std::string file_distances = "att48_d.txt";
    std::string location = "../../data/cities/";
    REQUIRE(read_distances(location + file_distances, distances) == true );
    REQUIRE(distances.size() == 48);
    REQUIRE(distances.at(0).size() == 48);
    REQUIRE(distances.at(0).at(0) == 0);
    REQUIRE(distances.at(47).at(47) == 0);
    REQUIRE(distances.at(0).at(47) == 3744);
    REQUIRE(distances.at(47).at(0) == 3744);

    std::vector<int> indexes;
    std::string file_labels = "att48_xy.txt";
    REQUIRE(read_indexes(location + file_labels, indexes) == true );
    REQUIRE(indexes.size() == 48);
    for (int i = 0; i < 48; ++i) {
        REQUIRE(indexes.at(i) == i);
    }
}

