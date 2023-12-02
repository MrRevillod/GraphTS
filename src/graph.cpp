
#include <graph.hpp>
#include <iostream>
#include <string>

void graph::add_vertex(const std::string &v_name) {

    if (v_exist(v_name)) {
        throw std::runtime_error("\n\n El vertice " + v_name + " ya existe en el grafo\n");
    }

    vertices[v_name] = new vertex(v_name);
}

void graph::rm_vertex(const std::string &v_name) {

    if (!v_exist(v_name)) {
        throw std::runtime_error("\n\nEl vertice " + v_name + " no existe en el grafo\n");
    }

    if (vertices[v_name]->adj.size() > 0) {

        vertices[v_name]->adj.clear();
        for (auto &[name, v] : vertices) {

            if (v->adj.find(vertices[v_name]) == v->adj.end())
                continue;

            rm_edge(name, v_name);
        }
    }

    vertices.erase(v_name);
}

vertex *graph::get_vertex(const std::string &name) {

    if (!v_exist(name)) {
        throw std::runtime_error("\n\n El vertice " + name + " no existe en el grafo\n");
    }

    return vertices[name];
}

bool graph::has_euler_path() {

    int n_impa = 0;

    for (auto [name, v] : vertices) {
        if (v->adj.size() % 2 != 0) {
            n_impa += 1;
        }
    }

    return n_impa <= 2;
}

bool graph::v_exist(const std::string &v_name) {
    return vertices.find(v_name) != vertices.end();
}
