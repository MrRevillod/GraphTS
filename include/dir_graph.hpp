
#ifndef DIR_GRAPH_HPP
#define DIR_GRAPH_HPP

#include <graph.hpp>

struct directed_graph : graph {
    directed_graph() : graph() {}
    directed_graph(const std::string &n) : graph(n) {}

    ~directed_graph() {}

    void add_edge(const std::string &from, const std::string &to, std::size_t weight);
    void rm_edge(const std::string &from, const std::string &to);

    void show();
    std::size_t get_total_weight();

    void topological_sort();

private:
    void topological_sort_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::stack<vertex *> &topological_stack);
};

#endif
