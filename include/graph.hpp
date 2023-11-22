
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "colormod.hpp"
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

extern Color::Modifier red;
extern Color::Modifier green;
extern Color::Modifier blue;
extern Color::Modifier def;

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

    std::string name;
    std::vector<vertex *> vertices;
    std::stack<vertex *> topological_stack;
    std::unordered_map<vertex *, bool> visited;
    std::unordered_map<vertex *, vertex *> parents;

    graph(const std::string &n) : name(n) {}

    ~graph() {

        for (vertex *v : vertices) {
            delete (v);
        }
    }

    void show_name() {
        std::cout << " " << std::endl;
        std::cout << blue << name << def << std::endl;
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
    void topological_sort();
    void topological_sort_recursive(vertex *v);

    void show_dfs();
};

#endif
