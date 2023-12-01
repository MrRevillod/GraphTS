
#ifndef UND_GRAPH_HPP
#define UND_GRAPH_HPP

#include <graph.hpp>

struct undirected_graph : graph {

    undirected_graph(const std::string &n) : graph(n) {}

    void show() override {

        std::cout << " " << std::endl;
        std::cout << Color::blue << name << Color::def << std::endl;

        std::cout << " " << std::endl;
        std::cout << Color::green << "Tipo: " << Color::def << "No dirigido" << std::endl;
        std::cout << Color::green << "Vertices:   " << Color::def << vertices.size() << std::endl;
        std::cout << Color::green << "Aristas:    " << Color::def;

        int n_edges = 0;

        for (const vertex *v : vertices) {
            n_edges += v->adj.size();
        }

        std::cout << n_edges / 2 << std::endl;
        std::cout << Color::green << "Peso total: " << Color::def << get_total_weight() << std::endl;
        std::cout << Color::green << "Tiene camino de euler: " << Color::def << (has_euler_path() ? "Si" : "No") << std::endl;
    }

    int get_total_weight() override {

        int total_weight = 0;

        for (const vertex *v : vertices) {
            for (const auto edge : v->adj) {
                total_weight += edge.second;
            }
        }

        return total_weight / 2;
    }

    bool has_euler_path() {

        int n_impa = 0;

        for (const vertex *v : vertices) {
            if (v->adj.size() % 2 != 0) {
                n_impa += 1;
            }
        }

        return n_impa <= 2;
    };

    void add_edge(vertex *from, vertex *to, int weight);
    void rm_edge(vertex *from, vertex *to);
    void color_graph();
};

#endif
