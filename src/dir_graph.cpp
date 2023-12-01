
#include <algorithm>
#include <dir_graph.hpp>
#include <errors.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

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

void directed_graph::topological_sort() {

    std::unordered_map<vertex *, bool> visited;
    std::stack<vertex *> topological_stack;

    for (vertex *v : vertices) {
        visited[v] = false;
    }

    for (vertex *v : vertices) {
        if (!visited[v]) {
            topological_sort_recursive(v, visited, topological_stack);
        }
    }

    std::cout << Color::green << "Ordenamiento topológico: " << Color::def;
    std::cout << Color::red << "[ " << Color::def;

    while (!topological_stack.empty()) {
        std::cout << topological_stack.top()->name << " ";
        topological_stack.pop();
    }

    std::cout << Color::red << "]" << Color::def << std::endl;
}

void directed_graph::topological_sort_recursive(vertex *v, std::unordered_map<vertex *, bool> &visited, std::stack<vertex *> &topological_stack) {

    visited[v] = true;

    for (const auto edge : v->adj) {
        if (!visited[edge.first]) {
            topological_sort_recursive(edge.first, visited, topological_stack);
        }
    }

    topological_stack.push(v);
}