
#ifndef UND_GRAPH_HPP
#define UND_GRAPH_HPP

#include <graph.hpp>

struct undirected_graph : graph {

    undirected_graph(const std::string &n) : graph(n) {}

    void add_edge(vertex *from, vertex *to, int weight);
    void rm_edge(vertex *from, vertex *to);
    undirected_graph *kruskal();
};

#endif
