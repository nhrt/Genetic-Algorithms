from typing import List
from Simulator_Wrapper import *
from SimulationResult import SimulationResult
from SimulationResultList import SimulationResultList


class SimulationExecutor:

	def __init__(self, label_path: str, distances_path: str, start_city: str, cities: int, population_size: int,
				 generations: int, mutation_rate: int, crossover: int, marriage: int, mutation: int, selection: int):
		self.simulator = Simulator(
			label_path, distances_path, start_city,
			cities, population_size, generations, mutation_rate,
			crossover, marriage, mutation, selection)
		self.generation: int = 0
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
