
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

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
    std::unordered_map<vertex *, bool> visited;
    std::unordered_map<vertex *, vertex *> parents;

    ~graph() {

        for (vertex *v : vertices) {
            delete (v);
        }
    }

    void show() {

        std::cout << " " << std::endl;

        for (const vertex *v : vertices) {

            for (const auto edge : v->adj) {
                vertex *to = edge.first;
                int weight = edge.second;

                std::cout << v->name << " -> " << weight << " -> " << to->name << std::endl;
            }
        }

        std::cout << " " << std::endl;
    }

    void add_vertex(vertex *v) {

        for (const vertex *vert : vertices) {
            if (vert == v) {
                throw std::runtime_error("\n\n El vertice " + v->name + " ya existe en el grafo\n");
            }
        }

        vertices.push_back(v);
    }

    void rm_vertex(vertex *v) {

        bool v_exists = std::find(vertices.begin(), vertices.end(), v) != vertices.end();

        if (!v_exists) {
            throw std::runtime_error("\n\nEl vertice " + v->name + " no existe en el grafo\n");
        }

        if (v->adj.size() > 0) {
            throw std::runtime_error("\n\nEl vertice " + v->name + " tiene aristas\n");
        }

        vertices.erase(std::remove(vertices.begin(), vertices.end(), v), vertices.end());
    }

    void add_edge(vertex *from, vertex *to, int weight) {

        if (from == to) {
            throw std::runtime_error("\n\n El vertice " + from->name + "no puede estar conectado a si mismo\n");
        }

        bool from_exists = std::find(vertices.begin(), vertices.end(), from) != vertices.end();
        bool to_exists = std::find(vertices.begin(), vertices.end(), to) != vertices.end();

        if (!from_exists || !to_exists) {
            throw std::runtime_error("\n\nUno o ambos vertices no se encuentran en el grafo\n");
        }

        for (const auto edge : from->adj) {

            vertex *e_to = edge.first;

            if (e_to == to) {
                throw std::runtime_error("\n\nLa arista " + from->name + " -> " + to->name + " ya existe\n");
            }
        }

        from->adj[to] = weight;
    }

    void rm_edge(vertex *from, vertex *to) {

        if (from == to) {
            throw std::runtime_error("\n\n El vertice " + from->name + "no puede estar conectado a si mismo\n");
        }

        bool from_exists = std::find(vertices.begin(), vertices.end(), from) != vertices.end();
        bool to_exists = std::find(vertices.begin(), vertices.end(), to) != vertices.end();

        if (!from_exists || !to_exists) {
            throw std::runtime_error("\n\nUno o ambos vertices no se encuentran en el grafo\n");
        }

        if (from->adj.find(to) == from->adj.end()) {
            throw std::runtime_error("\n\nLa arista " + from->name + " -> " + to->name + " no existe\n");

            from->adj.erase(to);
        }
    }

    void bfs(vertex *start) {

        std::vector<vertex *> frontera;
        std::unordered_map<vertex *, int> niveles;

        frontera.push_back(start);
        niveles[start] = 0;

        int i = 1;

        while (!frontera.empty()) {

            std::vector<vertex *> next;

            for (const vertex *v : frontera) {

                for (const auto edge : v->adj) {

                    bool exist = std::find(frontera.begin(), frontera.end(), edge.first) != frontera.end();

                    if (!exist) {
                        vertex *to = edge.first;
                        next.push_back(to);
                        niveles[to] = i;
                    }
                }
            }

            frontera = next;
            i++;
        }

        std::cout << " " << std::endl;
        std::cout << "Niveles" << std::endl;
        std::cout << " " << std::endl;

        for (auto nivel : niveles) {
            std::cout << nivel.first->name << " -> " << nivel.second << std::endl;
        }
    }

    void dfs(vertex *s) {

        visited[s] = true;

        for (const auto edge : s->adj) {

            if (!visited[edge.first]) {
                parents[edge.first] = s;
                dfs(edge.first);
            }
        }
    }

    void show_dfs() {

        std::cout << " " << std::endl;
        std::cout << "Padres " << std::endl;

        for (const auto parent : parents) {
            std::cout << parent.first->name << " -> " << parent.second->name << std::endl;
        }

        std::cout << " " << std::endl;
    }

    void show_visited() {

        std::cout << " " << std::endl;
        std::cout << "Visitados " << std::endl;

        for (const auto visit : visited) {
            std::cout << visit.first->name << " -> " << (visit.second == 1 ? "true" : "false") << std::endl;
        }
    }
};
