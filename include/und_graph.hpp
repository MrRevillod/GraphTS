
#ifndef UND_GRAPH_HPP
#define UND_GRAPH_HPP

#include <graph.hpp>

struct undirected_graph : graph {
    undirected_graph() : graph() {}
    undirected_graph(const std::string &n) : graph(n) {}

    ~undirected_graph() {}

    void show() override;
    std::size_t get_total_weight() override;

    void add_edge(const std::string &from, const std::string &to, std::size_t weight) override;
    void rm_edge(const std::string &from, const std::string &to) override;
    undirected_graph *kruskal() const;
};

#endif
