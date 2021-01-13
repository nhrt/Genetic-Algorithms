from typing import List

from Simulator_Wrapper import *
from SimulationResult import SimulationResult
from Plotter import Plotter
from SimulationExecutor import SimulationExecutor

generations = 1000
cities = 59
mutation = 10
size_individual = 10

s = Simulator(
    '../data/cities/labels', '../data/cities/distances', 'Augsburg',
    cities, size_individual, generations, mutation,
    Crossover_Algorithm.Edge_Recombination, Marriage_Algorithm.Roulette_Reversed, Mutation_Algorithm.Delete_Shift, Selection_Algorithm.SOFT)

sr_list: List[SimulationResult] = []

executor = SimulationExecutor(s)
for generation in range(generations):
    sr: SimulationResult = executor.simulate()
    sr_list.append(sr)
    print(sr)

Plotter.plot(sr_list, use_distances=False)
Plotter.plot(sr_list, use_distances=True)
