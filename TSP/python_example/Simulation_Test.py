from Simulator_Wrapper import *

generations = 10
cities = 59
mutation = 10
size_individual = 10

s = Simulator(
    '../data/cities/labels','../data/cities/distances', 'Augsburg',
    cities, size_individual, generations, mutation,
    Crossover_Algorithm.Edge_Recombination,Marriage_Algorithm.Roulette_Reversed,Mutation_Algorithm.Delete_Shift,Selection_Algorithm.SOFT)

for x in range(generations):
    print(s.simulate())
