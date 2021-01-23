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
import time

# simulation settings

distances_path: str = '../data/cities/att48_d.txt'
positions_path: str = '../data/cities/att48_xy.txt'
best_roundtrip_path: str = '../data/cities/att48_s.txt'
generations: int = 1000
cities: int = 48
start_city: int = 0
mutation: int = 10
population_size: int = 300

executor = SimulationExecutor(positions_path,
                              distances_path, start_city, cities,
                              population_size,
                              generations, mutation,
                              Crossover_Algorithm.Edge_Recombination,
                              Marriage_Algorithm.Roulette_Reversed_Distinct,
                              Mutation_Algorithm.Delete_Shift,
                              Selection_Algorithm.SOFT_Distinct)

print("Plotting ideal roundtrip...")
city_positions: List[Position] = read_city_positions(positions_path, 1)
best_roundtrip: (int, List[int]) = (33523, read_best_roundtrip(best_roundtrip_path, 1))

start = time.time()
result = executor.simulate_all()
end = time.time()
print("Elapsed Time: ")
print(end - start)
print(result)
Plotter.plot([executor.result_list], use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)
result = executor.best_individual()
Plotter.plot_roundtrip(Position.convert_idxs_to_positions(best_roundtrip[1], city_positions))
Plotter.plot_roundtrip(Position.convert_idxs_to_positions(result, city_positions))
