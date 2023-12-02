
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
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
        for (auto [name, v] : vertices) {
            delete v;
        }
    }

    void add_vertex(const std::string &v_name);
    void rm_vertex(const std::string &v_name);
    vertex *get_vertex(const std::string &name);
    bool v_exist(const std::string &v_name);

    virtual void show() = 0;
    virtual std::size_t get_total_weight() = 0;
    bool has_euler_path();

    static void bfs(vertex *start);
    void dfs(vertex *s);
    void dijkstra(vertex *start);

    virtual void add_edge(const std::string &from, const std::string &to, std::size_t weight) = 0;
    virtual void rm_edge(const std::string &from, const std::string &to) = 0;

private:
    void dfs_recursive(vertex *s, std::unordered_map<vertex *, bool> &visited, std::unordered_map<vertex *, vertex *> &paths);
};

#endif
