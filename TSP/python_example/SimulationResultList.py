from typing import List
from SimulationResult import SimulationResult
from AlgorithmResolver import *


class SimulationResultList:

	def __init__(self, cities: int, population_size: int, generations: int, mutation_rate: int, crossover: int,
				 marriage: int, mutation: int, selection: int):
		self.results: List[SimulationResult] = []
		self.cities = cities
		self.population_size = population_size
		self.generations = generations
		self.mutation_rate = mutation_rate
		self.crossover: int = crossover
		self.marriage: int = marriage
		self.mutation: int = mutation
		self.selection: int = selection

	def __str__(self) -> str:
		return "{} Ind., {}, {}, {} ({}%), {}".format(self.population_size,
											   get_marriage_name(self.marriage),
											   get_crossover_name(self.crossover),
											   get_mutation_name(self.mutation),
											   self.mutation_rate,
											   get_selection_name(self.selection))
