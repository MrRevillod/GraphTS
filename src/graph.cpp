
#include "graph.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>

void graph::bfs(vertex *start) {

    std::vector<vertex *> frontera;
    frontera.push_back(start);
    niveles[start] = 0;

    int i = 1;

    while (!frontera.empty()) {
        std::vector<vertex *> next;

        for (const vertex *v : frontera) {
            for (const auto edge : v->adj) {

                bool exist = std::find(frontera.begin(), frontera.end(), edge.first) != frontera.end();

                if (!exist) {
                    vertex *to = edge.first;
                    next.push_back(to);
                    niveles[to] = i;
                }
            }
        }

        frontera = next;
        i++;
    }
}

void graph::show_bfs() {

    std::cout << " " << std::endl;
    std::cout << "Niveles" << std::endl;
    std::cout << " " << std::endl;

    for (auto nivel : niveles) {
        std::cout << nivel.first->name << " -> " << nivel.second << std::endl;
    }
}

void graph::dfs(vertex *s) {

    visited[s] = true;

    for (const auto edge : s->adj) {

        if (!visited[edge.first]) {
            parents[edge.first] = s;
            dfs(edge.first);
        }
    }
}

void graph::show_dfs() {

    std::cout << " " << std::endl;
    std::cout << "Padres " << std::endl;

    for (const auto parent : parents) {
        std::cout << parent.first->name << " -> " << parent.second->name << std::endl;
    }

    std::cout << " " << std::endl;
}

void graph::dijkstra(vertex *start) {

    std::unordered_map<vertex *, int> distances;

    for (vertex *v : vertices) {
        distances[v] = oo;
    }

    distances[start] = 0;

    std::priority_queue<std::pair<vertex *, int>> pq;
    pq.push({start, 0});

    while (!pq.empty()) {

        vertex *u = pq.top().first;
        pq.pop();

        for (const auto edge : u->adj) {

            vertex *v = edge.first;
            int weight = edge.second;
            int distance = distances[u] + weight;

            if (distance < distances[v]) {
                distances[v] = distance;
                pq.push({v, -distance});
            }
        }
    }

    std::cout << " " << std::endl;
    std::cout << "Distancias mínimas desde el vertice " << start->name << " a:" << std::endl;

    for (vertex *v : vertices) {
        std::cout << v->name << " -> " << (distances[v] == oo ? "∞" : std::to_string(distances[v])) << std::endl;
    }
}

void graph::topological_sort() {

    for (vertex *v : vertices) {
        visited[v] = false;
    }

    for (vertex *v : vertices) {
        if (!visited[v]) {
            topological_sort_recursive(v);
        }
    }

    std::cout << " " << std::endl;
    std::cout << "Orden topológico:" << std::endl;

    while (!topological_stack.empty()) {
        std::cout << topological_stack.top()->name << " ";
        topological_stack.pop();
    }
    std::cout << std::endl;
}

void graph::topological_sort_recursive(vertex *v) {

    visited[v] = true;

    for (const auto edge : v->adj) {
        if (!visited[edge.first]) {
            topological_sort_recursive(edge.first);
        }
    }

    topological_stack.push(v);
}
