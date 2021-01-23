from typing import List
from Simulator_Wrapper import *
from SimulationResult import SimulationResult
from SimulationResultList import SimulationResultList


class SimulationExecutor:

	def __init__(self, positions_path: str, distances_path: str, start_city: int, cities: int, population_size: int,
				 generations: int, mutation_rate: int, crossover: int, marriage: int, mutation: int, selection: int):
		self.simulator = Simulator(
			positions_path, distances_path, start_city,
			cities, population_size, generations, mutation_rate,
			crossover, marriage, mutation, selection)
		self.generation: int = 0
		self.result: SimulationResult
		self.result_list: SimulationResultList = SimulationResultList(cities, population_size, generations,
																	  mutation_rate, crossover, marriage, mutation,
																	  selection)

	def simulate(self, store_result: bool = True) -> 'SimulationResult':
		res_fitness: List[int, int, int] = self.simulator.simulate()
		result: SimulationResult = SimulationResult(res_fitness[0], res_fitness[1], res_fitness[2], self.generation)
		if store_result:
			self.result_list.results.append(result)
		self.generation += 1
		return result

	def simulate_all(self, store_result: bool = True) -> 'SimulationResult':
		for generation in range(self.result_list.generations - 1):
			self.simulate(store_result)
		self.result = self.simulate(store_result)
		return self.result

	def best_individual(self) -> List[int]:
		return self.simulator.best_individual()
