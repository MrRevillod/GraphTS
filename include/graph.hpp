
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

    void show() {

        std::cout << " " << std::endl;
        std::cout << Color::blue << name << Color::def << std::endl;

        std::cout << " " << std::endl;
        std::cout << Color::green << "Vertices: " << Color::def << vertices.size() << std::endl;
        std::cout << Color::green << "Aristas: " << Color::def;

        int n_edges = 0;

        for (const vertex *v : vertices) {
            n_edges += v->adj.size();
        }

        std::cout << n_edges << std::endl;
        std::cout << Color::green << "Peso total: " << Color::def << get_total_weight() << std::endl;
        std::cout << Color::green << "Tiene camino de euler: " << Color::def;
        std::cout << (has_euler_path() ? "Si" : "No") << std::endl;
    }

    int has_euler_path() {

        int n_impa = 0;

        for (const vertex *v : vertices) {
            if (v->adj.size() % 2 != 0) {
                n_impa += 1;
            }
        }

        return n_impa <= 2;
    }

    int get_total_weight() {

        int total = 0;

        for (const vertex *v : vertices) {
            for (const auto edge : v->adj) {
                total += edge.second;
            }
        }

        return total;
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
    void dfs_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::unordered_map<vertex *, vertex *> &paths);

    void dijkstra(vertex *start);

    void topological_sort();
    void topological_sort_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::stack<vertex *> &topological_stack);

    virtual void add_edge(vertex *from, vertex *to, int weight) = 0;
    virtual void rm_edge(vertex *from, vertex *to) = 0;
};

#endif
