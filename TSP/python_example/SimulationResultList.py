from typing import List
from SimulationResult import SimulationResult


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
