#include <algorithm>
#include <errors.hpp>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <und_graph.hpp>

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

void undirected_graph::add_edge(vertex *from, vertex *to, int weight) {

    if (from == to)
        throw std::runtime_error(ERROR_SELF_CONNECTION);

    if (!v_exist(from) || !v_exist(to))
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);

    for (const auto edge : from->adj)
        if (edge.first == to)
            throw std::runtime_error(ERROR_EDGE_ALREADY_EXISTS);

    from->adj[to] = weight;
    to->adj[from] = weight;
}

void undirected_graph::rm_edge(vertex *from, vertex *to) {

    if (from == to)
        throw std::runtime_error(ERROR_SELF_CONNECTION);

    if (!v_exist(from) || !v_exist(to))
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);

    from->adj.erase(to);
    to->adj.erase(from);
}

undirected_graph *undirected_graph::kruskal() const {
    std::unordered_map<vertex *, std::size_t> pertenece;

    for (std::size_t i = 0; i < vertices.size(); i++) {
        pertenece[vertices[i]] = i;
    }

    edge aux_edge;
    vertex *node1;
    vertex *node2;

    std::size_t cn = vertices.size();
    std::size_t n = 0;
    undirected_graph *mst = new undirected_graph("Arbol de expanción mínima");
    while (n < (cn - 1)) {
        aux_edge.weight = oo;
        for (vertex *v : vertices) {
            for (auto e : v->adj) {
                if (aux_edge.weight > e.second && pertenece[v] != pertenece[e.first]) {
                    aux_edge.v1 = v;
                    aux_edge.v2 = e.first;
                    aux_edge.weight = e.second;
                }
            }
        }

        if (pertenece[aux_edge.v1] != pertenece[aux_edge.v2]) {
            node1 = new vertex(aux_edge.v1->name);
            node2 = new vertex(aux_edge.v2->name);

            bool find_node1 = false;
            bool find_node2 = false;
            for (vertex *v : mst->vertices) {
                // find_node1 = v->name == node1->name ? true : false;
                // find_node2 = v->name == node2->name ? true : false;
                if (v->name == node1->name)
                    find_node1 = true;
                if (v->name == node2->name)
                    find_node2 = true;
            }

            if (find_node1)
                node1 = mst->get_vertex(aux_edge.v1->name);
            else
                mst->add_vertex(node1);

            if (find_node2)
                node2 = mst->get_vertex(aux_edge.v2->name);
            else
                mst->add_vertex(node2);

            mst->add_edge(node1, node2, aux_edge.weight);

            std::size_t temp = pertenece[aux_edge.v2];
            pertenece[aux_edge.v2] = pertenece[aux_edge.v1];
            for (auto [k, v] : pertenece)
                if (pertenece[k] == temp)
                    pertenece[k] = pertenece[aux_edge.v1];

            n++;
        }
    }

    return mst;
}