from Simulator_Wrapper import *
from SimulationResult import SimulationResult
from Plotter import Plotter
from SimulationExecutor import SimulationExecutor

generations = 50000
cities = 59
mutation = 10
size_individual = 10

s = Simulator(
    '../data/cities/labels', '../data/cities/distances', 'Augsburg',
    cities, size_individual, generations, mutation,
    Crossover_Algorithm.Edge_Recombination, Marriage_Algorithm.Roulette_Reversed, Mutation_Algorithm.Delete_Shift, Selection_Algorithm.SOFT)

executor = SimulationExecutor(s)
for generation in range(generations):
    sr: SimulationResult = executor.simulate()
    print(sr)

Plotter.plot(executor.result_list, use_distances=False)
Plotter.plot(executor.result_list, use_distances=True)
