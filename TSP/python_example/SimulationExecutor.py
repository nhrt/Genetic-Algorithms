from typing import List

from SimulationResult import SimulationResult


class SimulationExecutor:

    def __init__(self, simulator):
        self.simulator = simulator
        self.generation = 0

    def simulate(self) -> 'SimulationResult':
        res_fitness: List[int, int, int] = self.simulator.simulate()
        result: SimulationResult = SimulationResult(res_fitness[0], res_fitness[1], res_fitness[2], self.generation)
        self.generation += 1
        return result
