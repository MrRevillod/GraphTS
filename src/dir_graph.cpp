
#include <algorithm>
#include <colormod.hpp>
#include <dir_graph.hpp>
#include <errors.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void directed_graph::show() {
    std::cout << " " << std::endl;
    std::cout << Color::blue << name << Color::def << std::endl;

    std::cout << " " << std::endl;
    std::cout << Color::green << "Tipo: " << Color::def << "No dirigido" << std::endl;
    std::cout << Color::green << "Vertices:   " << Color::def << vertices.size() << std::endl;
    std::cout << Color::green << "Aristas:    " << Color::def;

    int n_edges = 0;

    for (auto [name, v] : vertices)
        n_edges += v->adj.size();

    std::cout << n_edges << std::endl;
    std::cout << Color::green << "Peso total: " << Color::def << get_total_weight() << std::endl;
    std::cout << Color::green << "Tiene camino de euler: " << Color::def << (has_euler_path() ? "Si" : "No") << std::endl;
}

std::size_t directed_graph::get_total_weight() {

    int total_weight = 0;

    for (auto [name, v] : vertices) {
        for (const auto edge : v->adj) {
            total_weight += edge.second;
        }
    }

    return total_weight;
}

void directed_graph::add_edge(const std::string &from, const std::string &to, std::size_t weight) {

    if (from == to) {
        throw std::runtime_error(ERROR_SELF_CONNECTION);
    }

    if (!v_exist(from) || !v_exist(to)) {
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);
    }

    auto finded = vertices[from]->adj.find(vertices[to]);
    if (finded != vertices[from]->adj.end()) {
        throw std::runtime_error(ERROR_EDGE_ALREADY_EXISTS);
    }

    vertices[from]->adj.insert(std::pair<vertex *, std::size_t>(vertices[to], weight));
}

void directed_graph::rm_edge(const std::string &from, const std::string &to) {
    if (from == to) {
        throw std::runtime_error(ERROR_SELF_CONNECTION);
    }

    if (!v_exist(from) || !v_exist(to)) {
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);
    }

    auto finded = vertices[from]->adj.find(vertices[to]);
    if (finded == vertices[from]->adj.end()) {
        throw std::runtime_error(ERROR_EDGE_NOT_FOUND);
    }

    vertices[from]->adj.erase(vertices[to]);
}

void directed_graph::topological_sort() {

    std::unordered_map<vertex *, bool> visited;
    std::stack<vertex *> topological_stack;

    for (auto [name, v] : vertices) {
        visited[v] = false;
    }

    for (auto [name, v] : vertices) {
        if (!visited[v]) {
            topological_sort_recursive(v, visited, topological_stack);
        }
    }

    std::cout << Color::green << "Algoritmo: " << Color::def << "Ordenamiento topológico" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Ordenamiento: " << Color::red << "[ " << Color::def;

    while (!topological_stack.empty()) {
        std::cout << topological_stack.top()->name << " ";
        topological_stack.pop();
    }

    std::cout << Color::red << "]" << Color::def << std::endl;
    std::cout << std::endl;
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