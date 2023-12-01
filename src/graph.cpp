
#include <algorithm>
#include <graph.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

vertex *graph::get_vertex(const std::string name) {

    vertex *finded = nullptr;

    frontier.push_back(start);
    visited[start] = true;
    paths.push_back({start, 0});

    std::size_t i = 1;

    while (!frontier.empty()) {

        std::vector<vertex *> next;

        for (const vertex *v : frontier) {
            for (const auto edge : v->adj) {
                if (!visited[edge.first]) {
                    vertex *to = edge.first;
                    next.push_back(to);
                    paths.push_back({to, i});
                    visited[to] = true;
                }
            }
        }
    }

    if (finded == nullptr) {
        throw std::runtime_error("\n\nEl vertice " + name + " no existe en el grafo\n");
    }

    return finded;
}

void graph::dfs(vertex *start) {

    std::unordered_map<vertex *, bool> visited;
    std::unordered_map<vertex *, vertex *> path;

    std::cout << " " << std::endl;
    std::cout << Color::green << "Algoritmo: " << Color::def << "DFS" << std::endl;
    std::cout << " " << std::endl;

    for (auto [name, v] : vertices) {
        visited[v] = false;
    }

    dfs_recursive(start, visited, path);

    std::cout << "Vertice de partida: " << start->name << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Recorrido en profundidad: " << Color::red << "[ " << Color::def;

    for (const auto path : path) {
        std::cout << path.first->name << " ";
    }

    std::cout << Color::red << "]" << Color::def << std::endl;
}

void graph::add_vertex(vertex *v) {

    if (v_exist(v)) {
        throw std::runtime_error("\n\n El vertice " + v->name + " ya existe en el grafo\n");
    }

    vertices.push_back(v);
}

void graph::rm_vertex(vertex *v) {
    for (auto [name, v] : vertices) {
        distances[v] = oo;
    }

    if (v->adj.size() > 0) {
        throw std::runtime_error("\n\nEl vertice " + v->name + " tiene aristas\n");
    }

    /* Mostrar recorrido y caminos mínimos */

    std::cout << " " << std::endl;
    std::cout << Color::green << "Algoritmo: " << Color::def << "Dijkstra" << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Vertice de partida: " << start->name << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Distancias mínimas desde el vertice " << start->name << " a:";

    for (auto [name, v] : vertices) {
        std::cout << "" << std::endl;

        if (distances[v] != oo && v != start) {
            std::cout << "Vertice " << v->name << " - Camino:" << Color::red << " [ " << Color::def;

            for (vertex *p : paths[v]) {
                std::cout << p->name << " ";
            }

            std::cout << Color::red << "]" << Color::def << " - Costo: " << (distances[v] == oo ? "∞" : std::to_string(distances[v])) << std::endl;
        }
    }
}
