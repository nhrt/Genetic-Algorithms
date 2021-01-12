//
// Created by Niklas Hartinger on 12.01.2021.
//

#include <iostream>
#include <boost/python.hpp>
#include <simulation/Simulator.h>
#include <tuple>

using namespace boost::python;

template<class T>
struct TupleToList
{
    static PyObject* convert(const std::tuple<T, T, T>& tuple)
    {
        list* l = new list();
        l->append(std::get<0>(tuple));
        l->append(std::get<1>(tuple));
        l->append(std::get<2>(tuple));
        return l->ptr();
    }
};
BOOST_PYTHON_MODULE(Simulator_Wrapper)
{
    to_python_converter<std::tuple<int, int, int>, TupleToList<int> >();

    enum_<Crossover_Algorithm>("Crossover_Algorithm")
            .value("Partially_Matched", Crossover_Algorithm::Partially_Matched)
            .value("Order", Crossover_Algorithm::Order)
            .value("Cycle_all_cycles", Crossover_Algorithm::Cycle_all_cycles)
            .value("Cycle_one_cycle", Crossover_Algorithm::Cycle_one_cycle)
            .value("Edge_Recombination", Crossover_Algorithm::Edge_Recombination)
            ;

    enum_<Marriage_Algorithm>("Marriage_Algorithm")
            .value("Roulette", Marriage_Algorithm::Roulette)
            .value("Roulette_Reversed", Marriage_Algorithm::Roulette_Reversed)
            ;

    enum_<Mutation_Algorithm>("Mutation_Algorithm")
            .value("Delete_Shift", Mutation_Algorithm::Delete_Shift)
            ;

    enum_<Selection_Algorithm>("Selection_Algorithm")
            .value("SOFT", Selection_Algorithm::SOFT)
    ;

    class_<Simulator>("Simulator", init<
            std::string, std::string, std::string,
            int,int,int,int,
            Crossover_Algorithm, Marriage_Algorithm, Mutation_Algorithm, Selection_Algorithm>(
            ))
            .def("simulate", &Simulator::simulate)
            .def("finished", &Simulator::finished);
}
