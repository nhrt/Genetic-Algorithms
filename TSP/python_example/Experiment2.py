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
generations: int = 1000
cities: int = 48
start_city: int = 0
mutation: int = 5


def init_executors_pop_size(population: int) -> SimulationExecutor:
    return SimulationExecutor(positions_path,
                              distances_path, start_city, cities,
                              population,
                              generations, mutation,
                              Crossover_Algorithm.Order,
                              Marriage_Algorithm.Roulette_Reversed_Distinct,
                              Mutation_Algorithm.Delete_Shift,
                              Selection_Algorithm.SOFT_Distinct)


print("Testing different population sizes...")

res_lists: List[SimulationResultList] = []
for pop_size in sorted([5, 10, 100, 150, 300, 500]):
    print("simulating for population size = {}...".format(pop_size))
    executor: SimulationExecutor = init_executors_pop_size(pop_size)
    print(executor.simulate_all())
    res_lists.append(executor.result_list)
Plotter.plot(res_lists, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)
