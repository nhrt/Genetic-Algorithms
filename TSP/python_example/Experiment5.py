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

distances_path: str = '../data/cities/att48_d.txt'
positions_path: str = '../data/cities/att48_xy.txt'
best_roundtrip_path: str = '../data/cities/att48_s.txt'
generations: int = 3000
cities: int = 48
start_city: int = 0
population_size: int = 100
mutation_rate = 80


def init_executors_mutation_rate(mutation: int) -> SimulationExecutor:
    return SimulationExecutor(positions_path,
                              distances_path, start_city, cities,
                              population_size,
                              generations, mutation,
                              Crossover_Algorithm.Edge_Recombination,
                              Marriage_Algorithm.Roulette_Reversed_Distinct,
                              Mutation_Algorithm.Delete_Shift,
                              Selection_Algorithm.SOFT_Distinct)


res_lists: List[SimulationResultList] = []
print("Test with 3000 Generation:")
executor: SimulationExecutor = init_executors_mutation_rate(mutation_rate)
print(executor.simulate_all())
res_lists.append(executor.result_list)
Plotter.plot(res_lists, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)
