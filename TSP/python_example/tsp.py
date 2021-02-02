from typing import List
from Simulator_Wrapper import *
from Plotter import Plotter
from SimulationExecutor import SimulationExecutor
from enums.FitnessConfig import FitnessConfig
import threading
from SimulationResultList import SimulationResultList
from SimulationResult import SimulationResult
from Position import Position
from DataFileReader import *
from AlgorithmResolver import *
import argparse

# simulation settings
parser = argparse.ArgumentParser(
    description="Apply different genetic algorithms on the Traveling Salesman Problem (TSP).")
parser.add_argument("--distances_path", type=str, default="../data/cities/att48_d.txt",
                    help="relative path to the file containing the n x n distance matrix of the cities.")
parser.add_argument("--positions_path", type=str, default="../data/cities/att48_xy.txt",
                    help="relative path to the file containing the x and y coordinates of the cities.")
parser.add_argument("--best_roundtrip_path", type=str, default="../data/cities/att48_s.txt",
                    help="relative path to the file containing the best roundtrip (idxs of the cities).")
parser.add_argument("--generations", type=int, default=1000, help="number of generations to simulate.")
parser.add_argument("--cities", type=int, default=48, help="number of cities to use for the simulations.")
parser.add_argument("--mutation_rate", type=int, default=5,
                    help="probability of mutations ocurring in a single generation.")
parser.add_argument("--population_size", type=int, default=10, help="number of individuals within a population.")
parser.add_argument("--marriage_algorithm", type=int, default=2,
                    help=f"use int value [0 = {get_marriage_name(0)}, 1 = {get_marriage_name(1)}, 2 = {get_marriage_name(2)}]")
parser.add_argument("--crossover_algorithm", type=int, default=4,
                    help=f"use int value [0 = {get_crossover_name(0)}, 1 = {get_crossover_name(1)}, 2 = {get_crossover_name(2)}, 3 = {get_crossover_name(3)}, 4 = {get_crossover_name(4)}]")
parser.add_argument("--mutation_algorithm", type=int, default=0, help=f"use int value [0 = {get_mutation_name(0)}]")
parser.add_argument("--selection_algorithm", type=int, default=1,
                    help=f"use int value [0 = {get_selection_name(0)}, 1 = {get_selection_name(1)}]")

args = parser.parse_args()

distances_path: str = args.distances_path
positions_path: str = args.positions_path
best_roundtrip_path: str = args.best_roundtrip_path
generations: int = args.generations
cities: int = args.cities
start_city: int = 0
mutation_rate: int = args.mutation_rate
population_size: int = args.population_size
marriage_algorithm: int = args.marriage_algorithm
crossover_algorithm: int = args.crossover_algorithm
mutation_algorithm: int = args.mutation_algorithm
selection_algorithm: int = args.selection_algorithm

executor: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
                                                  cities, population_size,
                                                  generations, mutation_rate, get_crossover_value(crossover_algorithm),
                                                  get_marriage_value(marriage_algorithm),
                                                  get_mutation_value(mutation_algorithm),
                                                  get_selection_value(selection_algorithm))
result = executor.simulate_all()
print(executor.best_individual())
print("Calculated roundtrip with {} distance.".format(result.get_distance_lowest()))
result = executor.best_individual()
Plotter.plot([executor.result_list], use_distances=True)
city_positions: List[Position] = read_city_positions(positions_path, 1)
best_roundtrip: (int, List[int]) = (33523, read_best_roundtrip(best_roundtrip_path, 1))
Plotter.plot_roundtrip(Position.convert_idxs_to_positions(executor.best_individual(), city_positions),
                       Position.convert_idxs_to_positions(best_roundtrip[1], city_positions))
