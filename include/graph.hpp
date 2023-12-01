
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
    std::unordered_map<vertex *, std::size_t> adj;

    vertex() {}

    vertex(std::string n) : name(n) {}

    bool operator==(const vertex *v) {
        return name == v->name;
    }
};

struct graph {
    std::string name;
    std::unordered_map<std::string, vertex *> vertices;

    graph() {}
    graph(const std::string &n) : name(n) {}

    ~graph() {
        for (auto [name, v] : vertices)
            delete v;
    }

    vertex *get_vertex(const std::string &name) {

        if (!v_exist(name))
            throw std::runtime_error("\n\n El vertice " + name + " no existe en el grafo\n");

        return vertices[name];
    }

    virtual void show() = 0;

    bool has_euler_path() {
        int n_impa = 0;

        for (auto [name, v] : vertices)
            if (v->adj.size() % 2 != 0)
                n_impa += 1;

        return n_impa <= 2;
    }

    virtual std::size_t get_total_weight() = 0;

    bool v_exist(const std::string &v_name) {
        return vertices.find(v_name) != vertices.end();
    }

    void add_vertex(const std::string &v_name) {

        if (v_exist(v_name))
            throw std::runtime_error("\n\n El vertice " + v_name + " ya existe en el grafo\n");

        vertices[v_name] = new vertex(v_name);
    }

    void rm_vertex(const std::string &v_name) {

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

    static void bfs(vertex *start);

    void dfs(vertex *s);

    void dijkstra(vertex *start);

    virtual void add_edge(const std::string &from, const std::string &to, std::size_t weight) = 0;
    virtual void rm_edge(const std::string &from, const std::string &to) = 0;

private:
    void dfs_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::unordered_map<vertex *, vertex *> &paths);
};

#endif
