
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

    void add_vertex(vertex *v);
    void rm_vertex(vertex *v);

    virtual void add_edge(vertex *from, vertex *to, int weight) = 0;
    virtual void rm_edge(vertex *from, vertex *to) = 0;

    bool v_exist(vertex *v);
    vertex *get_vertex(const std::string name);

    virtual void show() = 0;
    virtual int get_total_weight() = 0;

    void bfs(vertex *start);

    void dfs(vertex *s);
    void dfs_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::unordered_map<vertex *, vertex *> &paths);

    void dijkstra(vertex *start);
};

#endif
