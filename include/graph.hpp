
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <colormod.hpp>
#include <iostream>
#include <stack>
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

    std::string name;
    std::vector<vertex *> vertices;

    graph(const std::string &n) : name(n) {}

    virtual ~graph() {
        for (vertex *v : vertices) {
            delete (v);
        }
    }

    vertex *get_vertex(const std::string name) {

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

    virtual void show() = 0;
    virtual int get_total_weight() = 0;

    void bfs(vertex *start);

    void dfs(vertex *s);
    void dfs_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::unordered_map<vertex *, vertex *> &paths);

    void dijkstra(vertex *start);

    virtual void add_edge(vertex *from, vertex *to, int weight) = 0;
    virtual void rm_edge(vertex *from, vertex *to) = 0;
};

#endif
