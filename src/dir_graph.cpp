
#include "dir_graph.hpp"
#include "errors.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void directed_graph::show() {

    std::cout << "Visualización del grafo:\n\n";

    for (const vertex *v : vertices) {
        std::cout << "Vértice: " << v->name << "\n";
        for (const auto edge : v->adj) {
            vertex *to = edge.first;
            int weight = edge.second;
            std::cout << "  --> " << to->name << " (peso: " << weight << ")\n";
        }
        std::cout << "\n";
    }

    std::cout << "Fin de la visualización del grafo.\n";
}

void directed_graph::add_edge(vertex *from, vertex *to, int weight) {

    if (from == to) {
        throw std::runtime_error(ERROR_SELF_CONNECTION);
    }

    if (!v_exist(from) || !v_exist(to)) {
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);
    }

    for (const auto edge : from->adj) {
        if (edge.first == to) {
            throw std::runtime_error("\nEl vertice " + from->name + "ya posee una conexión con el vertice " + to->name + "\n");
        }
    }

    for (const auto edge : to->adj) {
        if (edge.first == from) {
            throw std::runtime_error("\nEl vertice " + to->name + "ya posee una conexión con el vertice " + from->name + "\n");
        }
    }

    from->adj[to] = weight;
}

void directed_graph::rm_edge(vertex *from, vertex *to) {

    if (from == to) {
        throw std::runtime_error(ERROR_SELF_CONNECTION);
    }

    if (!v_exist(from) || !v_exist(to)) {
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);
    }

    if (from->adj.find(to) == from->adj.end()) {
        throw std::runtime_error(ERROR_EDGE_NOT_FOUND);
    }

    from->adj.erase(to);
}