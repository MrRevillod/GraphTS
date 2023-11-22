
#ifndef DIR_GRAPH_HPP
#define DIR_GRAPH_HPP

#include "graph.hpp"

struct directed_graph : graph {

    directed_graph(const std::string &n) : graph(n) {}

    void show();
    void add_edge(vertex *from, vertex *to, int weight);
    void rm_edge(vertex *from, vertex *to);
};

#endif
