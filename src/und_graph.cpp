#include <algorithm>
#include <colormod.hpp>
#include <errors.hpp>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <und_graph.hpp>
#include <unordered_set>

struct edge {
    vertex *v1, *v2;
    std::size_t weight;

    edge() {}

    edge(vertex *_v1, vertex *_v2, std::size_t _w)
        : v1{_v1}, v2{_v2}, weight{_w} {}

    bool operator<(const edge &e) {
        return weight < e.weight;
    }

    bool operator==(edge &e) {
        return (((v1 == e.v1) && (v2 == e.v2)) ||
                ((v2 == e.v1) && (v1 == e.v2))) &&
               (weight == e.weight);
    }
};

void undirected_graph::show() {
    std::cout << " " << std::endl;
    std::cout << Color::blue << name << Color::def << std::endl;

    std::cout << " " << std::endl;
    std::cout << Color::green << "Tipo: " << Color::def << "No dirigido" << std::endl;
    std::cout << Color::green << "Vertices:   " << Color::def << vertices.size() << std::endl;
    std::cout << Color::green << "Aristas:    " << Color::def;

    int n_edges = 0;

    for (auto [name, v] : vertices)
        n_edges += v->adj.size();

    std::cout << n_edges / 2 << std::endl;
    std::cout << Color::green << "Peso total: " << Color::def << get_total_weight() << std::endl;
    std::cout << Color::green << "Tiene camino de euler: " << Color::def << (has_euler_path() ? "Si" : "No") << std::endl;
}

std::size_t undirected_graph::get_total_weight() {

    int total_weight = 0;

    for (auto [name, v] : vertices) {
        for (const auto edge : v->adj) {
            total_weight += edge.second;
        }
    }

    return total_weight / 2;
}

void undirected_graph::add_edge(const std::string &from, const std::string &to, std::size_t weight) {

    if (from == to)
        throw std::runtime_error(ERROR_SELF_CONNECTION);

    if (!v_exist(from) || !v_exist(to))
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);

    auto finded = vertices[from]->adj.find(vertices[to]);
    if (finded != vertices[from]->adj.end())
        throw std::runtime_error(ERROR_EDGE_ALREADY_EXISTS);

    vertices[from]->adj.insert(std::pair<vertex *, std::size_t>(vertices[to], weight));
    vertices[to]->adj.insert(std::pair<vertex *, std::size_t>(vertices[from], weight));
}

void undirected_graph::rm_edge(const std::string &from, const std::string &to) {

    if (from == to)
        throw std::runtime_error(ERROR_SELF_CONNECTION);

    if (!v_exist(from) || !v_exist(to))
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);

    auto finded = vertices[from]->adj.find(vertices[to]);
    if (finded == vertices[from]->adj.end())
        throw std::runtime_error(ERROR_EDGE_NOT_FOUND);

    vertices[from]->adj.erase(vertices[to]);
    vertices[to]->adj.erase(vertices[from]);
}

undirected_graph *undirected_graph::kruskal() const {
    std::unordered_map<vertex *, std::size_t> pertenece;

    std::size_t i = 0;
    for (auto [name, v] : vertices) {
        pertenece[v] = i;
        i++;
    }

    edge aux_edge;

    std::size_t cn = vertices.size();
    std::size_t n = 0;
    undirected_graph *mst = new undirected_graph("Árbol de expanción mínima");
    while (n < (cn - 1)) {
        aux_edge.weight = oo;
        for (auto [name, v] : vertices) {
            for (auto [con, weight] : v->adj) {
                if (aux_edge.weight > weight && pertenece[v] != pertenece[con]) {
                    aux_edge.v1 = v;
                    aux_edge.v2 = con;
                    aux_edge.weight = weight;
                }
            }
        }

        if (pertenece[aux_edge.v1] != pertenece[aux_edge.v2]) {
            bool find_node1 = mst->vertices.find(aux_edge.v1->name) != mst->vertices.end();
            bool find_node2 = mst->vertices.find(aux_edge.v2->name) != mst->vertices.end();

            if (!find_node1)
                mst->add_vertex(aux_edge.v1->name);

            if (!find_node2)
                mst->add_vertex(aux_edge.v2->name);

            mst->add_edge(aux_edge.v1->name, aux_edge.v2->name, aux_edge.weight);

            std::size_t temp = pertenece[aux_edge.v2];
            pertenece[aux_edge.v2] = pertenece[aux_edge.v1];
            for (auto [k, v] : pertenece)
                if (pertenece[k] == temp)
                    pertenece[k] = pertenece[aux_edge.v1];

            n++;
        }
    }

    std::cout << " " << std::endl;
    std::cout << Color::green << "Algoritmo: " << Color::def << "Kruskal" << std::endl;
    std::cout << " " << std::endl;

    mst->show();

    return mst;
}