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
import argparse

# simulation settings
parser = argparse.ArgumentParser(
    description="Apply different genetic algorithms on the Traveling Salesman Problem (TSP).")
parser.add_argument("--distances_path", type=str, default="../data/cities/att48_d.txt",
                    help="relative path to the file containing the n x n distance matrix of the cities.")
parser.add_argument("--positions_path", type=str, default="../data/cities/att48_xy.txt",
                    help="relative path to the file containing the x and y coordinates of the cities.")
parser.add_argument("--generations", type=int, default=1000, help="number of generations to simulate.")
parser.add_argument("--cities", type=int, default=48, help="number of cities to use for the simulations.")
parser.add_argument("--mutation", type=int, default=10, help="probability of mutations ocurring in a single generation.")
parser.add_argument("--population_size", type=int, default=100, help="number of individuals within a population.")
parser.add_argument("--executions", type=int, default=5, help="number execution to calculate averages.")
args = parser.parse_args()

distances_path: str = args.distances_path
positions_path: str = args.positions_path
generations: int = args.generations
cities: int = args.cities
start_city: int = 0
mutation: int = args.mutation
population_size: int = args.population_size
number_of_execution: int = args.executions

'''see simulator.h for usable evolutionary algorithms'''


def init_executors() -> List[SimulationExecutor]:
    executor_partially_matched_rrd: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
                                                                            cities, population_size,
                                                                            generations, mutation,
                                                                            Crossover_Algorithm.Partially_Matched,
                                                                            Marriage_Algorithm.Roulette_Reversed_Distinct,
                                                                            Mutation_Algorithm.Delete_Shift,
                                                                            Selection_Algorithm.SOFT_Distinct)
    executor_order_rrd: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
                                                                cities, population_size,
                                                                generations, mutation, Crossover_Algorithm.Order,
                                                                Marriage_Algorithm.Roulette_Reversed_Distinct,
                                                                Mutation_Algorithm.Delete_Shift,
                                                                Selection_Algorithm.SOFT_Distinct)
    executor_cycle_all_cycles_rrd: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
                                                                           cities, population_size,
                                                                           generations, mutation,
                                                                           Crossover_Algorithm.Cycle_all_cycles,
                                                                           Marriage_Algorithm.Roulette_Reversed_Distinct,
                                                                           Mutation_Algorithm.Delete_Shift,
                                                                           Selection_Algorithm.SOFT_Distinct)
    executor_cycle_one_cycle_rrd: SimulationExecutor = SimulationExecutor(positions_path, distances_path, start_city,
                                                                          cities, population_size,
                                                                          generations, mutation,
                                                                          Crossover_Algorithm.Cycle_one_cycle,
                                                                          Marriage_Algorithm.Roulette_Reversed_Distinct,
                                                                          Mutation_Algorithm.Delete_Shift,
                                                                          Selection_Algorithm.SOFT_Distinct)
    executor_edge_recombination_rrd: SimulationExecutor = SimulationExecutor(positions_path,
                                                                             distances_path, start_city, cities,
                                                                             population_size,
                                                                             generations, mutation,
                                                                             Crossover_Algorithm.Edge_Recombination,
                                                                             Marriage_Algorithm.Roulette_Reversed_Distinct,
                                                                             Mutation_Algorithm.Delete_Shift,
                                                                             Selection_Algorithm.SOFT_Distinct)

    executors_rrd: List[SimulationExecutor] = [
        executor_partially_matched_rrd,
        executor_order_rrd,
        executor_cycle_all_cycles_rrd,
        executor_cycle_one_cycle_rrd,
        executor_edge_recombination_rrd
    ]

    return executors_rrd


def get_result_lists(executor_list: List[SimulationExecutor]) -> List[SimulationResultList]:
    return list(map(lambda e: e.result_list, executor_list))



print("The Simulation will now run {} times and calculate average fitness-values for each crossover-algorithm.".format(number_of_execution))
print("After that the result will be plotted.")
print()
executors: List[SimulationExecutor] = init_executors()
result_averages: List[SimulationResultList] = []
best_individual_fitness_count: List[int] = [0 for x in executors]

for i in range(number_of_execution):
    threads: List[threading.Thread] = list(map(lambda e: threading.Thread(target=e.simulate_all), executors))

    print("{}/{}: starting simulation...".format(i + 1, number_of_execution))
    for thread in threads:
        thread.start()
    print("simulating...")
    for thread in threads:
        thread.join()
    print("done simulating!")
    print()

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
    best_idxs: List[int] = [i for i, fitness in enumerate(last_results_best_fitness) if
                            fitness == best_individual_fitness]
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

max_avg_result_highest_fitness: int = max([rl.results[-1].highest_fitness for rl in result_averages])
best_avg_result_lists: List[SimulationResultList] = [rl for rl in result_averages if
                                                     rl.results[-1].highest_fitness == max_avg_result_highest_fitness]


Plotter.plot(result_averages, use_distances=True, fitness_multiple=FitnessConfig.HIGHEST)
print("Best average highest fitness ({}) accomplished by:".format(max_avg_result_highest_fitness))
for result_list in best_avg_result_lists:
    print("\t{}".format(str(result_list)))
    Plotter.plot([result_list], use_distances=True)


print()
print("Now running the simulation with best found crossover algorithm and plotting the resulting roundpath:")
city_positions: List[Position] = read_city_positions(positions_path, 1)
for result_list in best_avg_result_lists:
    res_lists: List[SimulationResultList] = []
    executor = SimulationExecutor(positions_path, distances_path, start_city, cities, population_size,
                                                          generations, mutation, result_list.crossover,
                                                          result_list.marriage, result_list.mutation,
                                                          result_list.selection)
    result = executor.simulate_all()
    print(result_list)
    print(executor.best_individual())
    print("Calculated roundtrip with {} distance.".format(result.get_distance_lowest()))
    result = executor.best_individual()
    Plotter.plot_roundtrip(Position.convert_idxs_to_positions(result, city_positions))
