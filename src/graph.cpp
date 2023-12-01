
#include <algorithm>
#include <colormod.hpp>
#include <graph.hpp>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>

void graph::bfs(vertex *start) {

    std::vector<vertex *> frontier;
    std::unordered_map<vertex *, bool> visited;
    std::vector<std::pair<vertex *, int>> paths;

    frontier.push_back(start);
    visited[start] = true;
    paths.push_back({start, 0});

    int i = 1;

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

        frontier = next;
        i++;
    }

    /* Mostrar recorrido y niveles del grafo */

    std::cout << " " << std::endl;
    std::cout << Color::green << "Algoritmo: " << Color::def << "BFS" << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Vertice de partida: " << start->name << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Recorrido en anchura: " << Color::red << " [ " << Color::def;

    for (const auto &path : paths) {
        std::cout << path.first->name << " ";
    }

    std::cout << Color::red << "]" << Color::def << std::endl;
    std::cout << "Niveles del recorrido: " << Color::red << "[ " << Color::def;

    for (const auto &path : paths) {
        std::cout << path.second << " ";
    }

    std::cout << Color::red << "]" << Color::def << std::endl;
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

void graph::dfs_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::unordered_map<vertex *, vertex *> &parents) {

    visited[s] = true;

    for (const auto edge : s->adj) {
        if (!visited[edge.first]) {
            parents[edge.first] = s;
            dfs_recursive(edge.first, visited, parents);
        }
    }
}

void graph::dijkstra(vertex *start) {

    std::unordered_map<vertex *, int> distances;
    std::unordered_map<vertex *, std::vector<vertex *>> paths;

    for (auto [name, v] : vertices) {
        distances[v] = oo;
    }

    distances[start] = 0;
    paths[start] = {start};

    std::priority_queue<std::pair<vertex *, int>> pq;
    pq.push({start, 0});

    while (!pq.empty()) {

        vertex *u = pq.top().first;
        pq.pop();

        for (const auto edge : u->adj) {

            vertex *v = edge.first;
            int weight = edge.second;

            if (weight < 0) {
                throw std::runtime_error("\n\n El argoritmo de dijkstra no trabaja con pesos negativos\n");
            }

            int distance = distances[u] + weight;

            if (distance < distances[v]) {
                distances[v] = distance;
                paths[v] = paths[u];
                paths[v].push_back(v);
                pq.push({v, -distance});
            }
        }
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
