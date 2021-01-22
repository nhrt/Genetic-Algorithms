from Simulator_Wrapper import *


def get_crossover_name(crossover: int) -> str:
	if crossover == Crossover_Algorithm.Partially_Matched:
		return "Partially Matched"
	elif crossover == Crossover_Algorithm.Order:
		return "Order"
	elif crossover == Crossover_Algorithm.Cycle_all_cycles:
		return "Cycle (all)"
	elif crossover == Crossover_Algorithm.Cycle_one_cycle:
		return "Cycle (one)"
	elif crossover == Crossover_Algorithm.Edge_Recombination:
		return "Edge Recombination"


def get_marriage_name(marriage: int) -> str:
	if marriage == Marriage_Algorithm.Roulette:
		return "Roulette"
	elif marriage == Marriage_Algorithm.Roulette_Reversed:
		return "Roulette Reversed"
	elif marriage == Marriage_Algorithm.Roulette_Reversed_Distinct:
		return "Distinct Roulette Reversed"


def get_mutation_name(mutation: int) -> str:
	if mutation == Mutation_Algorithm.Delete_Shift:
		return "Delete Shift"


def get_selection_name(selection: int) -> str:
	if selection == Selection_Algorithm.SOFT:
		return "Survival of the Fittest"
	elif selection == Selection_Algorithm.SOFT_Distinct:
		return "Distinct Survival of the Fittest"
