
#include <algorithm>
#include <graph.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

vertex *graph::get_vertex(const std::string name) {

    vertex *finded = nullptr;

    for (auto v : vertices) {
        if (v->name == name) {
            finded = v;
        }
    }

    if (finded == nullptr) {
        throw std::runtime_error("\n\nEl vertice " + name + " no existe en el grafo\n");
    }

    return finded;
}

bool graph::v_exist(vertex *v) {
    return std::find(vertices.begin(), vertices.end(), v) != vertices.end();
}

void graph::add_vertex(vertex *v) {

    if (v_exist(v)) {
        throw std::runtime_error("\n\n El vertice " + v->name + " ya existe en el grafo\n");
    }

    vertices.push_back(v);
}

void graph::rm_vertex(vertex *v) {

    if (!v_exist(v)) {
        throw std::runtime_error("\n\nEl vertice " + v->name + " no existe en el grafo\n");
    }

    if (v->adj.size() > 0) {
        throw std::runtime_error("\n\nEl vertice " + v->name + " tiene aristas\n");
    }

    vertices.erase(std::remove(vertices.begin(), vertices.end(), v), vertices.end());
}
