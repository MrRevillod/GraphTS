
#ifndef DIR_GRAPH_HPP
#define DIR_GRAPH_HPP

#include <graph.hpp>

struct directed_graph : graph {

    directed_graph(const std::string &n) : graph(n) {}

    void add_edge(vertex *from, vertex *to, int weight) override;
    void rm_edge(vertex *from, vertex *to) override;

    void topological_sort();
    void topological_sort_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::stack<vertex *> &topological_stack);
};

#endif
