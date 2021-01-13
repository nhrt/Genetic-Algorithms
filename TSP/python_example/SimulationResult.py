class SimulationResult:

    def __init__(self, lowest_fitness: int, highest_fitness: int, avg_fitness: int, generation: int):
        self.lowest_fitness = lowest_fitness
        self.highest_fitness = highest_fitness
        self.avg_fitness = avg_fitness
        self.generation = generation

    def get_distance_lowest(self) -> int:
        return -self.lowest_fitness

    def get_distance_highest(self) -> int:
        return -self.highest_fitness

    def get_distance_avg(self) -> int:
        return -self.avg_fitness

    def __str__(self) -> str:
        return "{}: [{}, {}, {}]".format(self.generation, self.lowest_fitness, self.highest_fitness, self.avg_fitness)
