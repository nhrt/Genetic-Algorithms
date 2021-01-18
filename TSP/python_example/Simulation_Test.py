from typing import List
from Simulator_Wrapper import *
from Plotter import Plotter
from SimulationExecutor import SimulationExecutor
from enums.FitnessConfig import FitnessConfig
import threading
from SimulationResultList import SimulationResultList

# simulation settings
generations: int = 50
cities: int = 59
mutation: int = 10
population_size: int = 10

'''see simulator.h for usable evolutionary algorithms'''

executor_partially_matched_r: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
																	cities, population_size,
																	generations, mutation, Crossover_Algorithm.Partially_Matched,
																	Marriage_Algorithm.Roulette,
																	Mutation_Algorithm.Delete_Shift,
																	Selection_Algorithm.SOFT)
executor_partially_matched_rr: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
																	  cities, population_size,
																	  generations, mutation, Crossover_Algorithm.Partially_Matched,
																	  Marriage_Algorithm.Roulette_Reversed,
																	  Mutation_Algorithm.Delete_Shift,
																	  Selection_Algorithm.SOFT)
executor_order_r: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
														cities, population_size,
														generations, mutation, Crossover_Algorithm.Order,
														Marriage_Algorithm.Roulette,
														Mutation_Algorithm.Delete_Shift,
														Selection_Algorithm.SOFT)
executor_order_rr: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
														  cities, population_size,
														  generations, mutation, Crossover_Algorithm.Order,
														  Marriage_Algorithm.Roulette_Reversed,
														  Mutation_Algorithm.Delete_Shift,
														  Selection_Algorithm.SOFT)
executor_cycle_all_cycles_r: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
																	 cities, population_size,
																	 generations, mutation, Crossover_Algorithm.Cycle_all_cycles,
																	 Marriage_Algorithm.Roulette,
																	 Mutation_Algorithm.Delete_Shift,
																	 Selection_Algorithm.SOFT)
executor_cycle_all_cycles_rr: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
																	 cities, population_size,
																	 generations, mutation, Crossover_Algorithm.Cycle_all_cycles,
																	 Marriage_Algorithm.Roulette_Reversed,
																	 Mutation_Algorithm.Delete_Shift,
																	 Selection_Algorithm.SOFT)
executor_cycle_one_cycle_r: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
										   cities, population_size,
										   generations, mutation, Crossover_Algorithm.Cycle_one_cycle,
										   Marriage_Algorithm.Roulette,
										   Mutation_Algorithm.Delete_Shift,
										   Selection_Algorithm.SOFT)
executor_cycle_one_cycle_rr: SimulationExecutor = SimulationExecutor('../data/cities/labels', '../data/cities/distances', 'Augsburg',
																	cities, population_size,
																	generations, mutation, Crossover_Algorithm.Cycle_one_cycle,
																	Marriage_Algorithm.Roulette_Reversed,
																	Mutation_Algorithm.Delete_Shift,
																	Selection_Algorithm.SOFT)
executor_edge_recombination_r: SimulationExecutor = SimulationExecutor('../data/cities/labels',
																	 '../data/cities/distances', 'Augsburg', cities,
																	 population_size,
																	 generations, mutation,
																	 Crossover_Algorithm.Edge_Recombination,
																	 Marriage_Algorithm.Roulette,
																	 Mutation_Algorithm.Delete_Shift,
																	 Selection_Algorithm.SOFT)
executor_edge_recombination_rr: SimulationExecutor = SimulationExecutor('../data/cities/labels',
																	   '../data/cities/distances', 'Augsburg', cities,
																	   population_size,
																	   generations, mutation,
																	   Crossover_Algorithm.Edge_Recombination,
																	   Marriage_Algorithm.Roulette_Reversed,
																	   Mutation_Algorithm.Delete_Shift,
																	   Selection_Algorithm.SOFT)

execturos: List[SimulationExecutor] = [
	executor_partially_matched_r,
	executor_partially_matched_rr,
	executor_order_r,
	executor_order_rr,
	executor_cycle_all_cycles_r,
	executor_cycle_all_cycles_rr,
	executor_cycle_one_cycle_r,
	executor_cycle_one_cycle_rr,
	executor_edge_recombination_r,
	executor_edge_recombination_rr
]
threads: List[threading.Thread] = list(map(lambda e: threading.Thread(target=e.simulate_all), execturos))

print("starting simulation threads...")
for thread in threads:
	thread.start()
print("simulating...")
for thread in threads:
	thread.join()
print("done simulating!")

result_lists: List[SimulationResultList] = list(map(lambda e: e.result_list, execturos))

for result_list in result_lists:
	Plotter.plot([result_list], use_distances=False)
	Plotter.plot([result_list], use_distances=True)

Plotter.plot(result_lists, use_distances=False, fitness_multiple=FitnessConfig.HIGHEST)
Plotter.plot(result_lists, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)
Plotter.plot(result_lists, use_distances=False, fitness_multiple=FitnessConfig.AVG)
Plotter.plot(result_lists, use_distances=True, fitness_multiple=FitnessConfig.AVG)
Plotter.plot(result_lists, use_distances=False, fitness_multiple=FitnessConfig.LOWEST)
Plotter.plot(result_lists, use_distances=True, fitness_multiple=FitnessConfig.LOWEST)
