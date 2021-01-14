from typing import List
from SimulationResult import SimulationResult


class SimulationResultList:

	def __init__(self, crossover: int, marriage: int, mutation: int, selection: int):
		self.results: List[SimulationResult] = []
		self.crossover: int = crossover
		self.marriage: int = marriage
		self.mutation: int = mutation
		self.selection: int = selection
