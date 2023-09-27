
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct vertex;

struct edge {

    vertex *to;
    int weight;

    edge(vertex *t, int w) : to(t), weight(w) {}
    ~edge() {}
};

struct vertex {

    std::string name;
    std::vector<edge *> edges;

    vertex(std::string n) : name(n) {}
    ~vertex() {
        for (edge *e : edges) {
            delete e;
        }
    }
};

struct nivel {
    vertex *v;
    int distance;
    nivel(vertex *v, int d) : v(v), distance(d) {}
};

struct padre {
    vertex *v;
    vertex *p;
    padre(vertex *v, vertex *p = nullptr) : v(v), p(p) {}
};

class frontera {
public:
    std::vector<vertex *> vertices;

    bool is_empty() {
        return vertices.empty();
    }

    void push(vertex *v) { vertices.push_back(v); }
};

class graph {
private:
    std::vector<vertex *> vertices;

public:
    ~graph() {

        for (vertex *v : vertices) {
            delete (v);
        }
    }

    void show() {

        std::cout << " " << std::endl;

        for (vertex *v : vertices) {

            for (edge *e : v->edges) {

                std::cout << v->name << " -> " << e->weight << " -> " << e->to->name << std::endl;
            }
        }

        std::cout << " " << std::endl;
    }

    void add_vertex(vertex *v) {

        for (vertex *vert : vertices) {

            if (vert->name == v->name) {
                throw std::runtime_error("\n\nEl vertice " + v->name + " ya existe en el grafo\n");
            }
        }

        vertices.push_back(v);
    }

    void rm_vertex(vertex *v) {

        for (vertex *vert : vertices) {

            if (vert->name == v->name) {
            }
        }
    }

    void add_edge(vertex *from, vertex *to, int weight) {

        if (from == to) {
            throw std::runtime_error("El vertice no puede estar conectado a si mismo");
        }

        bool from_exists = std::find(vertices.begin(), vertices.end(), from) != vertices.end();
        bool to_exists = std::find(vertices.begin(), vertices.end(), to) != vertices.end();

        if (!from_exists || !to_exists) {
            throw std::runtime_error("Uno o ambos vertices no existen en el grafo");
        }

        for (edge *e : from->edges) {

            if (e->to == to) {
                throw std::runtime_error("\n\nLa arista " + from->name + " -> " + to->name + " ya existe\n");
            }
        }

        for (edge *e : to->edges) {

            if (e->to == from) {
                throw std::runtime_error("\n\nLa arista " + to->name + " -> " + from->name + " ya existe\n");
            }
        }

        from->edges.push_back(new edge(to, weight));
    }

    void rm_edge(vertex *from, vertex *to) {

        if (from->name == to->name) {
            throw std::runtime_error("\n\nNo se puede eliminar la arista ya que apuntan al mismo vertice\n");
        }

        bool from_exists = std::find(vertices.begin(), vertices.end(), from) != vertices.end();
        bool to_exists = std::find(vertices.begin(), vertices.end(), to) != vertices.end();

        if (!from_exists || !to_exists) {
            throw std::runtime_error("Uno o ambos vertices no existen en el grafo");
        }
    }

    std::vector<nivel *> bfs(vertex *s) {

        frontera f;
        f.push(s);

        std::vector<nivel *> niveles;
        std::vector<padre *> padres;

        nivel *n = new nivel(s, 0);
        padre *p = new padre(s);

        int i = 1;

        while (!f.is_empty()) {

            frontera next;

            for (vertex *v : f.vertices) {

                for (edge *e : v->edges) {

                    bool v_exists = std::find(f.vertices.begin(), f.vertices.end(), e->to) != f.vertices.end();

                    if (!v_exists) {

                        next.push(e->to);
                        niveles.push_back(new nivel(e->to, i));
                        padres.push_back(new padre(e->to, v));
                    }
                }
            }

            f = next;
            i++;
        }

        return niveles;
    }

    void show_bfs(std::vector<nivel *> &niveles) {

        std::cout << " " << std::endl;

        for (nivel *n : niveles) {
            std::cout << n->v->name << " -> " << n->distance << std::endl;
        }

        std::cout << " " << std::endl;
    }
};
