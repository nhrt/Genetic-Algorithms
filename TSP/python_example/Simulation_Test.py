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

# simulation settings

distances_path: str = '../data/cities/att48_d.txt'
positions_path: str = '../data/cities/att48_xy.txt'
best_roundtrip_path: str = '../data/cities/att48_s.txt'
generations: int = 1000
cities: int = 48
start_city: int = 0
mutation: int = 50
population_size: int = 10


'''see simulator.h for usable evolutionary algorithms'''


def init_executors(reversed_fitness_only: bool = True) -> List[SimulationExecutor]:
	executor_partially_matched_r: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
																		  cities, population_size,
																		  generations, mutation, Crossover_Algorithm.Partially_Matched,
																		  Marriage_Algorithm.Roulette,
																		  Mutation_Algorithm.Delete_Shift,
																		  Selection_Algorithm.SOFT)
	executor_partially_matched_rr: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
																		   cities, population_size,
																		   generations, mutation, Crossover_Algorithm.Partially_Matched,
																		   Marriage_Algorithm.Roulette_Reversed,
																		   Mutation_Algorithm.Delete_Shift,
																		   Selection_Algorithm.SOFT)
	executor_order_r: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
															  cities, population_size,
															  generations, mutation, Crossover_Algorithm.Order,
															  Marriage_Algorithm.Roulette,
															  Mutation_Algorithm.Delete_Shift,
															  Selection_Algorithm.SOFT)
	executor_order_rr: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
															   cities, population_size,
															   generations, mutation, Crossover_Algorithm.Order,
															   Marriage_Algorithm.Roulette_Reversed,
															   Mutation_Algorithm.Delete_Shift,
															   Selection_Algorithm.SOFT)
	executor_cycle_all_cycles_r: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
																		 cities, population_size,
																		 generations, mutation, Crossover_Algorithm.Cycle_all_cycles,
																		 Marriage_Algorithm.Roulette,
																		 Mutation_Algorithm.Delete_Shift,
																		 Selection_Algorithm.SOFT)
	executor_cycle_all_cycles_rr: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
																		  cities, population_size,
																		  generations, mutation, Crossover_Algorithm.Cycle_all_cycles,
																		  Marriage_Algorithm.Roulette_Reversed,
																		  Mutation_Algorithm.Delete_Shift,
																		  Selection_Algorithm.SOFT)
	executor_cycle_one_cycle_r: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
																		cities, population_size,
																		generations, mutation, Crossover_Algorithm.Cycle_one_cycle,
																		Marriage_Algorithm.Roulette,
																		Mutation_Algorithm.Delete_Shift,
																		Selection_Algorithm.SOFT)
	executor_cycle_one_cycle_rr: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
																		 cities, population_size,
																		 generations, mutation, Crossover_Algorithm.Cycle_one_cycle,
																		 Marriage_Algorithm.Roulette_Reversed,
																		 Mutation_Algorithm.Delete_Shift,
																		 Selection_Algorithm.SOFT)
	executor_edge_recombination_r: SimulationExecutor = SimulationExecutor(positions_path,
																		   distances_path, start_city, cities,
																		   population_size,
																		   generations, mutation,
																		   Crossover_Algorithm.Edge_Recombination,
																		   Marriage_Algorithm.Roulette,
																		   Mutation_Algorithm.Delete_Shift,
																		   Selection_Algorithm.SOFT)
	executor_edge_recombination_rr: SimulationExecutor = SimulationExecutor(positions_path,
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
result_averages: List[SimulationResultList] = []
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
	if i == 0:
		result_averages = result_lists
	else:
		for rl_idx in range(len(result_lists)):
			for sr_idx in range(len(result_lists[rl_idx].results)):
				sr_avg: SimulationResult = result_averages[rl_idx].results[sr_idx]
				sr: SimulationResult = result_lists[rl_idx].results[sr_idx]
				sr_avg.highest_fitness += sr.highest_fitness
				sr_avg.avg_fitness += sr.avg_fitness
				sr_avg.lowest_fitness += sr.lowest_fitness

	last_results_best_fitness: List[int] = list(map(lambda rl: rl.results[-1].highest_fitness, result_lists))
	best_individual_fitness = max(last_results_best_fitness)
	best_idxs: List[int] = [i for i, fitness in enumerate(last_results_best_fitness) if fitness == best_individual_fitness]
	for idx in best_idxs:
		best_individual_fitness_count[idx] += 1

	if i < number_of_execution - 1:
		executors = init_executors()

for rl_idx in range(len(result_averages)):
	for sr_idx in range(len(result_averages[rl_idx].results)):
		sr_avg: SimulationResult = result_averages[rl_idx].results[sr_idx]
		sr_avg.highest_fitness /= number_of_execution
		sr_avg.avg_fitness /= number_of_execution
		sr_avg.lowest_fitness /= number_of_execution

print("Plotting ideal roundtrip...")
city_positions: List[Position] = read_city_positions(positions_path, 1)
best_roundtrip: (int, List[int]) = (33523, read_best_roundtrip(best_roundtrip_path, 1))
Plotter.plot_roundtrip(Position.convert_idxs_to_positions(best_roundtrip[1], city_positions))

max_avg_result_highest_fitness: int = max([rl.results[-1].highest_fitness for rl in result_averages])
best_avg_result_lists: List[SimulationResultList] = [rl for rl in result_averages if rl.results[-1].highest_fitness == max_avg_result_highest_fitness]

print("Best average highest fitness ({}) accomplished by:".format(max_avg_result_highest_fitness))
for result_list in best_avg_result_lists:
	print("\t{}".format(str(result_list)))
	Plotter.plot([result_list], use_distances=True)

Plotter.plot(result_averages, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)
Plotter.plot(result_averages, use_distances=True, fitness_multiple=FitnessConfig.AVG)
Plotter.plot(result_averages, use_distances=True, fitness_multiple=FitnessConfig.LOWEST)

# experiment with different population sizes
print("Testing different population sizes...")
for result_list in best_avg_result_lists:
	res_lists: List[SimulationResultList] = []
	for pop_size in sorted([5, 10, 50, 250]):
		print("simulating for population size = {}...".format(pop_size))
		executor: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city, cities, pop_size, generations, mutation, result_list.crossover, result_list.marriage, result_list.mutation, result_list.selection)
		executor.simulate_all()
		res_lists.append(executor.result_list)
	Plotter.plot(res_lists, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)

# experiment with different mutation_rates
print("Testing different mutation rates...")
for result_list in best_avg_result_lists:
	res_lists: List[SimulationResultList] = []
	for mutation_rate in sorted([0, 5, 10, 25, 50, 75, 100]):
		print("simulating for mutation_rate = {}%...".format(mutation_rate))
		executor: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city, cities, population_size, generations, mutation_rate, result_list.crossover, result_list.marriage, result_list.mutation, result_list.selection)
		executor.simulate_all()
		res_lists.append(executor.result_list)
	Plotter.plot(res_lists, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)

# experiment with different population sizes
print("Testing different generations (iteration count)...")
for result_list in best_avg_result_lists:
	generation_list: List[int] = sorted([0, 25, 50, 100, 200, 300, 1000, 5000, 10000])
	max_generation = generation_list[-1]
	executor: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city, cities, population_size, max_generation + 1, mutation, result_list.crossover, result_list.marriage, result_list.mutation, result_list.selection)
	for gen in range(max_generation+1):
		executor.simulate()
		if gen in generation_list:
			Plotter.plot([executor.result_list], use_distances=True)
			print("simulating until next generation count has been reached...")
