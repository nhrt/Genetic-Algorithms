from typing import List
import matplotlib.pyplot as plt
import itertools
from SimulationResultList import SimulationResultList
from enums.FitnessConfig import FitnessConfig


class Plotter:

    def __init__(self):
        pass

    @staticmethod
    def plot(simulations: List[SimulationResultList], use_distances: bool = False, fitness_multiple: FitnessConfig = FitnessConfig.HIGHEST):
        if len(simulations) == 0:
            return

        # plot graph for one simulation
        if len(simulations) == 1:
            xs: List[int] = [x.generation for x in simulations[0].results]
            if use_distances:
                ys_best = [x.get_distance_highest() for x in simulations[0].results]
                ys_avg = [x.get_distance_avg() for x in simulations[0].results]
                ys_worst = [x.get_distance_lowest() for x in simulations[0].results]
            else:
                ys_best = [x.highest_fitness for x in simulations[0].results]
                ys_avg = [x.avg_fitness for x in simulations[0].results]
                ys_worst = [x.lowest_fitness for x in simulations[0].results]
            plt.plot(xs, ys_best, color=(0, 1, 0, 1), label="best")
            plt.plot(xs, ys_avg, color=(0, 0, 1, 1), label="average")
            plt.plot(xs, ys_worst, color=(1, 0, 0, 1), label="worst")
            all_generations: List[int] = list(map(lambda sr: sr.generation, simulations[0].results))
            first_generation: int = min(all_generations)
            last_generation: int = max(all_generations)
            title: str = "{} über {} Generationen".format("Distanz" if use_distances else "Fitness", last_generation-first_generation+1)
            plt.title(title)
            plt.legend()
            plt.show()
        # plot graph for multiple simulations
        else:
            for simulation in simulations:
                xs: List[int] = [x.generation for x in simulation.results]
                if use_distances:
                    ys = [x.get_distance_highest() for x in simulation.results]
                else:
                    ys = [x.highest_fitness for x in simulation.results]
                # TODO: label lines according to the evolution algorithms used
                # TODO: use different color scheme for every line
                plt.plot(xs, ys, color=(0, 1, 0, 1), label="todo")
            all_generations: List[int] = list(map(lambda sr: sr.generation, list(itertools.chain.from_iterable(map(lambda s: s.results, simulations)))))
            first_generation: int = min(all_generations)
            last_generation: int = max(all_generations)
            info = ""
            if fitness_multiple == FitnessConfig.HIGHEST:
                info = "besten"
            elif fitness_multiple == FitnessConfig.AVG:
                info = "durchschnittlichen"
            elif fitness_multiple == FitnessConfig.LOWEST:
                info = "schlechtesten"
            title: str = "Vergleich der {} {} über {} Generationen".format(info, "Distanz" if use_distances else "Fitness", last_generation-first_generation+1)
            plt.title(title)
            plt.legend()
            plt.show()
