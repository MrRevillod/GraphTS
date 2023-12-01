
#ifndef DIR_GRAPH_HPP
#define DIR_GRAPH_HPP

#include <graph.hpp>

struct directed_graph : graph {

    directed_graph(const std::string &n) : graph(n) {}

    void show() override {

        std::cout << " " << std::endl;
        std::cout << Color::blue << name << Color::def << std::endl;

        std::cout << " " << std::endl;
        std::cout << Color::green << "Tipo: " << Color::def << "Dirigido" << std::endl;
        std::cout << Color::green << "Vertices: " << Color::def << vertices.size() << std::endl;
        std::cout << Color::green << "Aristas:  " << Color::def;

        int n_edges = 0;

        for (const vertex *v : vertices) {
            n_edges += v->adj.size();
        }

        std::cout << n_edges << std::endl;
        std::cout << Color::green << "Peso total: " << Color::def << get_total_weight() << std::endl;

        topological_sort();
    };

    int get_total_weight() override {

        int total = 0;

        for (const vertex *v : vertices) {
            for (const auto edge : v->adj) {
                total += edge.second;
            }
        }

        return total;
    };

    void add_edge(vertex *from, vertex *to, int weight) override;
    void rm_edge(vertex *from, vertex *to) override;

    void topological_sort();
    void topological_sort_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::stack<vertex *> &topological_stack);
};

#endif
