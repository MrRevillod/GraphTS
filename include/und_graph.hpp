
#ifndef UND_GRAPH_HPP
#define UND_GRAPH_HPP

#include <graph.hpp>

struct undirected_graph : graph {

    undirected_graph() : graph() {}
    undirected_graph(const std::string &n) : graph(n) {}

    ~undirected_graph() {}

    void show();
    std::size_t get_total_weight();

    void add_edge(const std::string &from, const std::string &to, std::size_t weight);
    void rm_edge(const std::string &from, const std::string &to);
    undirected_graph *kruskal() const;
};

#endif
