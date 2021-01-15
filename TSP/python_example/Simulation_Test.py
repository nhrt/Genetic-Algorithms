from Simulator_Wrapper import *
from Plotter import Plotter
from SimulationExecutor import SimulationExecutor
from enums.FitnessConfig import FitnessConfig

'''see simulator.h for usable evolutionary algorithms'''

generations: int = 5
cities: int = 59
mutation: int = 10
population_size: int = 10

executor_edge_recombination: SimulationExecutor = SimulationExecutor('../data/cities/labels',
																	 '../data/cities/distances', 'Augsburg', cities,
																	 population_size,
																	 generations, mutation,
																	 Crossover_Algorithm.Edge_Recombination,
																	 Marriage_Algorithm.Roulette_Reversed,
																	 Mutation_Algorithm.Delete_Shift,
																	 Selection_Algorithm.SOFT)

executor_order: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
														cities, population_size,
														generations, mutation, Crossover_Algorithm.Order,
														Marriage_Algorithm.Roulette_Reversed,
														Mutation_Algorithm.Delete_Shift,
														Selection_Algorithm.SOFT)

for generation in range(generations):
	executor_edge_recombination.simulate()
	executor_order.simulate()

Plotter.plot([executor_edge_recombination.result_list], use_distances=False)
Plotter.plot([executor_edge_recombination.result_list], use_distances=True)
Plotter.plot([executor_order.result_list], use_distances=False)
Plotter.plot([executor_order.result_list], use_distances=True)
Plotter.plot([executor_edge_recombination.result_list, executor_order.result_list], use_distances=False,
			 fitness_multiple=FitnessConfig.HIGHEST)
Plotter.plot([executor_edge_recombination.result_list, executor_order.result_list], use_distances=True,
			 fitness_multiple=FitnessConfig.HIGHEST)
Plotter.plot([executor_edge_recombination.result_list, executor_order.result_list], use_distances=False,
			 fitness_multiple=FitnessConfig.AVG)
Plotter.plot([executor_edge_recombination.result_list, executor_order.result_list], use_distances=True,
			 fitness_multiple=FitnessConfig.AVG)
Plotter.plot([executor_edge_recombination.result_list, executor_order.result_list], use_distances=False,
			 fitness_multiple=FitnessConfig.LOWEST)
Plotter.plot([executor_edge_recombination.result_list, executor_order.result_list], use_distances=True,
			 fitness_multiple=FitnessConfig.LOWEST)
