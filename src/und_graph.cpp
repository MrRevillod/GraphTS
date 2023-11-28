
#include <algorithm>
#include <errors.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <und_graph.hpp>

struct edge {
    vertex *v1, *v2;
    std::size_t weight;

    edge(vertex *_v1, vertex *_v2, std::size_t _w)
        : v1{_v1}, v2{_v2}, weight{_w} {}

    bool operator<(edge &e) {
        return weight < e.weight;
    }

    bool operator==(edge &e) {
        return (((v1 == e.v1) && (v2 == e.v2)) ||
                ((v2 == e.v1) && (v1 == e.v2))) &&
               (weight == e.weight);
    }
};

void undirected_graph::add_edge(vertex *from, vertex *to, int weight) {

    if (from == to) {
        throw std::runtime_error(ERROR_SELF_CONNECTION);
    }

    if (!v_exist(from) || !v_exist(to)) {
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);
    }

    for (const auto edge : from->adj) {
        if (edge.first == to) {
            throw std::runtime_error(ERROR_EDGE_ALREADY_EXISTS);
        }
    }

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

undirected_graph *undirected_graph::kruskal() {
    std::cout << "hola como estai desde el algoritmo kruskal\n";

    std::vector<edge> edges;

    for (vertex *v : vertices) {
        for (auto e : v->adj) {
            edge new_edge = edge(v, e.first, e.second);
            auto finded = std::find(edges.begin(), edges.end(), new_edge);
            if (finded != edges.end())
                continue;
            edges.emplace_back(new_edge);
        }
    }

    std::sort(edges.begin(), edges.end());

    for (edge e : edges)
        std::cout << e.weight << "\n";

    return nullptr;
}