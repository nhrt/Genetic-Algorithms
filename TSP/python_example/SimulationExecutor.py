from typing import List

from SimulationResult import SimulationResult


class SimulationExecutor:

    def __init__(self, simulator):
        self.simulator = simulator
        self.generation = 0
        self.result_list = []

    def simulate(self, store_result: bool = True) -> 'SimulationResult':
        res_fitness: List[int, int, int] = self.simulator.simulate()
        result: SimulationResult = SimulationResult(res_fitness[0], res_fitness[1], res_fitness[2], self.generation)
        if store_result:
            self.result_list.append(result)
        self.generation += 1
        return result
