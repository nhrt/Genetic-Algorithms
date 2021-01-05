//
// Created by Niklas Hartinger on 14.12.2020.
//


#include "read_cities.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.length() > 0) {
            elems.push_back(item);
        }
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool read_distances(const std::string &file, std::vector<std::vector<int>> &distances, int size) {
    std::ifstream file_stream(file);
    std::string line;
    distances.resize(size, std::vector<int>(size, false));

    if (file_stream.is_open()) {
        int current_line = 0;
        std::vector<std::string> row_string;
        std::vector<int> row_int;
        while (getline(file_stream, line)) {
            current_line++;
            if (current_line < CONTENT_START_INDEX_DISTANCES) continue;
            row_string = split(line, ' ');
            char *pEnd;
            for (unsigned int i = 0; i < row_string.size(); i++) {
                int num = strtol(row_string.at(i).c_str(), &pEnd, 10);
                distances.at(current_line - CONTENT_START_INDEX_DISTANCES).at(i) = num;
            }
        }
        file_stream.close();
    } else {
        std::cerr << "Distances File not found\n";
        return false;
    }
    return true;
}

bool read_names(const std::string &file, std::vector<std::string> &names, int size) {
    std::ifstream file_stream(file);
    std::string line;
    names.resize(size);
    int counter = 0;
    if (file_stream.is_open()) {
        int current_line = 0;
        while (getline(file_stream, line) && counter < size) {
            current_line++;
            if (current_line < CONTENT_START_INDEX_NAMES) continue;
            names.at(current_line - CONTENT_START_INDEX_NAMES) = line;
            counter++;
        }
        file_stream.close();
    } else {
        std::cerr << "Name File not found\n";
        return false;
    }
    return true;
}