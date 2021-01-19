from typing import List
from Simulator_Wrapper import *
from Plotter import Plotter
from SimulationExecutor import SimulationExecutor
from enums.FitnessConfig import FitnessConfig
import threading
from SimulationResultList import SimulationResultList

# simulation settings
labels_path: str = '../data/cities/labels'
distances_path: str = '../data/cities/distances'
generations: int = 50
cities: int = 59
start_city: str = 'Augsburg'
mutation: int = 10
population_size: int = 10

'''see simulator.h for usable evolutionary algorithms'''


def init_executors(reversed_fitness_only: bool = True) -> List[SimulationExecutor]:
	executor_partially_matched_r: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
																		  cities, population_size,
																		  generations, mutation, Crossover_Algorithm.Partially_Matched,
																		  Marriage_Algorithm.Roulette,
																		  Mutation_Algorithm.Delete_Shift,
																		  Selection_Algorithm.SOFT)
	executor_partially_matched_rr: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
																		   cities, population_size,
																		   generations, mutation, Crossover_Algorithm.Partially_Matched,
																		   Marriage_Algorithm.Roulette_Reversed,
																		   Mutation_Algorithm.Delete_Shift,
																		   Selection_Algorithm.SOFT)
	executor_order_r: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
															  cities, population_size,
															  generations, mutation, Crossover_Algorithm.Order,
															  Marriage_Algorithm.Roulette,
															  Mutation_Algorithm.Delete_Shift,
															  Selection_Algorithm.SOFT)
	executor_order_rr: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
															   cities, population_size,
															   generations, mutation, Crossover_Algorithm.Order,
															   Marriage_Algorithm.Roulette_Reversed,
															   Mutation_Algorithm.Delete_Shift,
															   Selection_Algorithm.SOFT)
	executor_cycle_all_cycles_r: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
																		 cities, population_size,
																		 generations, mutation, Crossover_Algorithm.Cycle_all_cycles,
																		 Marriage_Algorithm.Roulette,
																		 Mutation_Algorithm.Delete_Shift,
																		 Selection_Algorithm.SOFT)
	executor_cycle_all_cycles_rr: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
																		  cities, population_size,
																		  generations, mutation, Crossover_Algorithm.Cycle_all_cycles,
																		  Marriage_Algorithm.Roulette_Reversed,
																		  Mutation_Algorithm.Delete_Shift,
																		  Selection_Algorithm.SOFT)
	executor_cycle_one_cycle_r: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
																		cities, population_size,
																		generations, mutation, Crossover_Algorithm.Cycle_one_cycle,
																		Marriage_Algorithm.Roulette,
																		Mutation_Algorithm.Delete_Shift,
																		Selection_Algorithm.SOFT)
	executor_cycle_one_cycle_rr: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city,
																		 cities, population_size,
																		 generations, mutation, Crossover_Algorithm.Cycle_one_cycle,
																		 Marriage_Algorithm.Roulette_Reversed,
																		 Mutation_Algorithm.Delete_Shift,
																		 Selection_Algorithm.SOFT)
	executor_edge_recombination_r: SimulationExecutor = SimulationExecutor(labels_path,
																		   distances_path, start_city, cities,
																		   population_size,
																		   generations, mutation,
																		   Crossover_Algorithm.Edge_Recombination,
																		   Marriage_Algorithm.Roulette,
																		   Mutation_Algorithm.Delete_Shift,
																		   Selection_Algorithm.SOFT)
	executor_edge_recombination_rr: SimulationExecutor = SimulationExecutor(labels_path,
																			distances_path, start_city, cities,
																			population_size,
																			generations, mutation,
																			Crossover_Algorithm.Edge_Recombination,
																			Marriage_Algorithm.Roulette_Reversed,
																			Mutation_Algorithm.Delete_Shift,
																			Selection_Algorithm.SOFT)

	executors_r: List[SimulationExecutor] = [
		executor_partially_matched_r,
		executor_order_r,
		executor_cycle_all_cycles_r,
		executor_cycle_one_cycle_r,
		executor_edge_recombination_r,
	]
	executors_rr: List[SimulationExecutor] = [
		executor_partially_matched_rr,
		executor_order_rr,
		executor_cycle_all_cycles_rr,
		executor_cycle_one_cycle_rr,
		executor_edge_recombination_rr
	]
	if reversed_fitness_only:
		return executors_rr
	else:
		return executors_r + executors_rr


def get_result_lists(executor_list: List[SimulationExecutor]) -> List[SimulationResultList]:
	return list(map(lambda e: e.result_list, executor_list))


number_of_execution: int = 10

executors: List[SimulationExecutor] = init_executors()
best_individual_fitness_count: List[int] = [0 for x in executors]

for i in range(number_of_execution):
	threads: List[threading.Thread] = list(map(lambda e: threading.Thread(target=e.simulate_all), executors))

	print("{}/{}: starting simulation threads...".format(i+1, number_of_execution))
	for thread in threads:
		thread.start()
	print("simulating...")
	for thread in threads:
		thread.join()
	print("done simulating!")

	result_lists: List[SimulationResultList] = get_result_lists(executors)

	last_results_best_fitness: List[int] = list(map(lambda rl: rl.results[-1].highest_fitness, result_lists))
	best_individual_fitness = max(last_results_best_fitness)
	best_idxs: List[int] = [i for i, fitness in enumerate(last_results_best_fitness) if fitness == best_individual_fitness]
	for idx in best_idxs:
		best_individual_fitness_count[idx] += 1

	if i < number_of_execution - 1:
		executors = init_executors()


result_lists: List[SimulationResultList] = get_result_lists(executors)

best_result_lists: List[SimulationResultList] = [rl for i, rl in enumerate(result_lists) if best_individual_fitness_count[i] == max(best_individual_fitness_count)]

for result_list in best_result_lists:
	Plotter.plot([result_list], use_distances=True)

Plotter.plot(result_lists, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)
Plotter.plot(result_lists, use_distances=True, fitness_multiple=FitnessConfig.AVG)
Plotter.plot(result_lists, use_distances=True, fitness_multiple=FitnessConfig.LOWEST)

# experiment with different population sizes
print("Testing different population sizes...")
for result_list in best_result_lists:
	for pop_size in [5, 10, 50, 250, 1000]:
		executor: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city, cities, pop_size, generations, mutation, result_list.crossover, result_list.marriage, result_list.mutation, result_list.selection)
		executor.simulate_all()
		Plotter.plot([executor.result_list], use_distances=True)

# experiment with different mutation_rates
print("Testing different mutation rates...")
for result_list in best_result_lists:
	for mutation_rate in [0, 5, 10, 25, 50, 75, 100]:
		executor: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city, cities, population_size, generations, mutation_rate, result_list.crossover, result_list.marriage, result_list.mutation, result_list.selection)
		executor.simulate_all()
		Plotter.plot([executor.result_list], use_distances=True)

# experiment with different population sizes
print("Testing different generations (iteration count)...")
for result_list in best_result_lists:
	generation_list: List[int] = [0, 25, 50, 100, 200, 300, 1000, 5000, 10000, 20000]
	max_generation = max(generation_list)
	executor: SimulationExecutor = SimulationExecutor(labels_path, distances_path, start_city, cities, population_size, max_generation+1, mutation, result_list.crossover, result_list.marriage, result_list.mutation, result_list.selection)
	for gen in range(max_generation+1):
		executor.simulate()
		if gen in generation_list:
			Plotter.plot([executor.result_list], use_distances=True)
