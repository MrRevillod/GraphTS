
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define oo 0x3f3f3f3f

struct vertex {

    std::string name;
    std::unordered_map<vertex *, int> adj;

    vertex(std::string n) : name(n) {}

    bool operator==(const vertex *v) {
        return name == v->name;
    }
};

struct graph {

    std::vector<vertex *> vertices;
    std::unordered_map<vertex *, int> niveles;
    std::unordered_map<vertex *, bool> visited;
    std::unordered_map<vertex *, vertex *> parents;

    ~graph() {

        for (vertex *v : vertices) {
            delete (v);
        }
    }

    bool v_exist(vertex *v) {
        return std::find(vertices.begin(), vertices.end(), v) != vertices.end();
    }

    void add_vertex(vertex *v) {

        if (v_exist(v)) {
            throw std::runtime_error("\n\n El vertice " + v->name + " ya existe en el grafo\n");
        }

        vertices.push_back(v);
    }

    void rm_vertex(vertex *v) {

        if (!v_exist(v)) {
            throw std::runtime_error("\n\nEl vertice " + v->name + " no existe en el grafo\n");
        }

        if (v->adj.size() > 0) {
            throw std::runtime_error("\n\nEl vertice " + v->name + " tiene aristas\n");
        }

        vertices.erase(std::remove(vertices.begin(), vertices.end(), v), vertices.end());
    }

    void bfs(vertex *start);
    void dfs(vertex *s);
    void dijkstra(vertex *start);
    void bellman_ford(vertex *start);
    void floyd_warshall();

    void show_bfs();
    void show_dfs();
};

#endif
