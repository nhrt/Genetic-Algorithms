# cmake version
cmake_minimum_required(VERSION 3.17)

# project name
set(project "TSP")
project(${project})

# flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER "g++.exe")
# Das big-ob ist notwendig weil catch so riesig ist. Sollte man in Zukunft versuchen zu fixen (Idee: catch2.hpp zu einer Library umwandeln).
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -m64 -Wa,-mbig-ob")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(PythonLibs 3 REQUIRED)
find_package( PythonInterp 3 REQUIRED )
find_package(Boost COMPONENTS python38 REQUIRED)
# files

# include
include_directories(./include ./src ${PYTHON_INCLUDE_DIRS})

# target

# external libs

# target

# Add source code here
add_library(${project}
        src/util/read_cities.cpp src/util/read_cities.h src/individual/Individual.cpp src/individual/Individual.h src/population/Population.cpp src/population/Population.h src/genetic_algorithms/utility.cpp src/genetic_algorithms/utility.h src/genetic_algorithms/crossover.cpp src/genetic_algorithms/crossover.h src/genetic_algorithms/mutation.cpp src/genetic_algorithms/mutation.h src/genetic_algorithms/marriage.cpp src/genetic_algorithms/marriage.h src/util/Random_Number_Generator.h src/genetic_algorithms/selection.cpp src/genetic_algorithms/selection.h src/simulation/Simulator.cpp src/simulation/Simulator.h)

add_library(Catch INTERFACE)
target_include_directories(Catch
        INTERFACE
        test/
        )

# Add unit tests here
add_executable(unit_tests
        tests/main.cpp
        tests/util/test_util_read_cities.cpp
        tests/individual/test_Individual.cpp tests/population/test_Population.cpp tests/genetic_algorithms/test_utility.cpp tests/genetic_algorithms/test_crossover.cpp tests/genetic_algorithms/test_mutation.cpp tests/genetic_algorithms/test_marriage.cpp tests/util/test_random_number_generator.cpp tests/genetic_algorithms/test_selection.cpp tests/simulation/test_Simulator.cpp)

target_include_directories(unit_tests
        PUBLIC
        libs/catch/
        ${PYTHON_INCLUDE_DIRS}
        )
target_link_libraries(unit_tests
        Catch
        ${project}
        )

add_library(matplotlib INTERFACE)

add_executable(research
        research/main.cpp)

target_include_directories(research
        PUBLIC
        libs/matplotlib/
        )

target_link_libraries(research
        ${project}
        ${PYTHON_LIBRARIES}
)

set(CMAKE_SHARED_MODULE_PREFIX "")
add_library(Simulator_Wrapper MODULE python_wrapper/Simulator_Wrapper.cpp)
target_link_libraries(Simulator_Wrapper
        ${Boost_LIBRARIES}
        ${PYTHON_LIBRARIES}
        ${project}
        )
target_include_directories(Simulator_Wrapper PRIVATE ${PYTHON_INCLUDE_DIRS})
set_target_properties(Simulator_Wrapper PROPERTIES SUFFIX ".pyd")