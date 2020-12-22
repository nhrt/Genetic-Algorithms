//
// Created by Niklas Hartinger on 14.12.2020.
//
#include <catch.hpp>
#include <util/read_cities.h>

SCENARIO("Test Utility Read Cities", "[test_util_read_distances.cpp],[test_util_read_names.cpp]")
{
    std::vector<std::vector<int>> distances;
    std::string file_distances = "distances";
    std::string location = "../../data/cities/";
    REQUIRE(read_distances(location + file_distances, distances) == true );
    REQUIRE(distances.size() == 59);
    REQUIRE(distances.at(0).size() == 59);
    REQUIRE(distances.at(9).at(10) == 123);
    REQUIRE(distances.at(0).at(0) == 0);
    REQUIRE(distances.at(56).at(58) == 90);

    std::vector<std::string> names;
    std::string file_labels = "labels";
    REQUIRE(read_names(location + file_labels, names) == true );
    REQUIRE(names.size() == 59);
    REQUIRE(names.at(0) == "Augsburg");
    REQUIRE(names.at(58) == "Siegen");
}

