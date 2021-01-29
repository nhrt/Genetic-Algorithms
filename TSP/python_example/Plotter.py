from typing import List
import matplotlib.pyplot as plt
import itertools
from SimulationResultList import SimulationResultList
from enums.FitnessConfig import FitnessConfig
from AlgorithmResolver import *
from Position import Position


class Plotter:

	def __init__(self):
		pass

	@staticmethod
	def plot(simulations: List[SimulationResultList], use_distances: bool = False,
			 fitness_multiple: FitnessConfig = FitnessConfig.HIGHEST):
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
			plt.plot(xs, ys_best, color=(0, 1, 0, 1), marker=",", label="best",)
			plt.plot(xs, ys_avg, color=(0, 0, 1, 1), marker=",", label="average")
			plt.plot(xs, ys_worst, color=(1, 0, 0, 1), marker=",", label="worst")
			all_generations: List[int] = list(map(lambda sr: sr.generation, simulations[0].results))
			first_generation: int = min(all_generations)
			last_generation: int = max(all_generations)
			title: str = "{} über {} Generationen bei {} Städten\n{}".format(
				"Distanz" if use_distances else "Fitness", last_generation - first_generation + 1,
				simulations[0].cities, str(simulations[0]))
			plt.title(title)
			plt.xlabel("Generation")
			plt.ylabel("Distanz" if use_distances else "Fitness")
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
				label: str = str(simulation)
				# if default color cycle provided by matplotlib is not enough, use custom defined colors
				plt.plot(xs, ys, marker=",", label=label)
			all_generations: List[int] = list(map(lambda sr: sr.generation, list(
				itertools.chain.from_iterable(map(lambda s: s.results, simulations)))))
			first_generation: int = min(all_generations)
			last_generation: int = max(all_generations)
			info = ""
			if fitness_multiple == FitnessConfig.HIGHEST:
				info = "besten"
			elif fitness_multiple == FitnessConfig.AVG:
				info = "durchschnittlichen"
			elif fitness_multiple == FitnessConfig.LOWEST:
				info = "schlechtesten"
			title: str = "Vergleich der {} {} über {} Generationen".format(info,
																		   "Distanz" if use_distances else "Fitness",
																		   last_generation - first_generation + 1)
			plt.title(title)
			plt.xlabel("Generation")
			plt.ylabel("Distanz" if use_distances else "Fitness")
			plt.legend()
			plt.show()

	@staticmethod
	def plot_roundtrip(city_pos: List[Position], compare_city_pos: List[Position] = None):
		xs: List[int] = [p.x for p in city_pos]
		ys: List[int] = [p.y for p in city_pos]
		if compare_city_pos is not None:
			fig, (ax1, ax2) = plt.subplots(1, 2)
			xs_compare: List[int] = [p.x for p in compare_city_pos]
			ys_compare: List[int] = [p.y for p in compare_city_pos]
			ax2.plot(xs_compare, ys_compare, color=(0.5, 0.5, 0.5, 1), marker="o")
			ax2.set_title("Vergleich")
			ax1.plot(xs, ys, color=(0, 0, 0, 1), marker="o")
			ax1.set_title("Rundlauf")
			plt.show()
		else:
			plt.plot(xs, ys, color=(0, 0, 0, 1), marker="o")
			plt.title("Rundlauf")
			plt.show()
