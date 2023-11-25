
#include <algorithm>
#include <errors.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <und_graph.hpp>

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

    if (from == to) {
        throw std::runtime_error(ERROR_SELF_CONNECTION);
    }

    if (!v_exist(from) || !v_exist(to)) {
        throw std::runtime_error(ERROR_VERTEX_NOT_FOUND);
    }

    from->adj.erase(to);
    to->adj.erase(from);
}