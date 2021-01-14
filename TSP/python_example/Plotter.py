from typing import List

import matplotlib.pyplot as plt
from SimulationResult import SimulationResult


class Plotter:

    def __init__(self):
        pass

    @staticmethod
    def plot(sr: List[SimulationResult], use_distances: bool = False):
        xs = [x.generation for x in sr]
        if use_distances:
            ys_best = [x.get_distance_highest() for x in sr]
            ys_avg = [x.get_distance_avg() for x in sr]
            ys_worst = [x.get_distance_lowest() for x in sr]
        else:
            ys_best = [x.highest_fitness for x in sr]
            ys_avg = [x.avg_fitness for x in sr]
            ys_worst = [x.lowest_fitness for x in sr]
        title = "{} über {} Generationen".format("Distanzen" if use_distances else "Fitness", max(xs)-min(xs)+1)

        plt.plot(xs, ys_best, color=(0, 1, 0, 1), label="best")
        plt.plot(xs, ys_avg, color=(0, 0, 1, 1), label="average")
        plt.plot(xs, ys_worst, color=(1, 0, 0, 1), label="worst")
        plt.title(title)
        plt.legend()

        plt.show()
