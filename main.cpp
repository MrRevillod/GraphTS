
#include "graph.cpp"
#include <iostream>
#include <string>

void bfs() {

    graph g;
    vertex *a = new vertex("a");
    vertex *z = new vertex("z");
    vertex *s = new vertex("s");
    vertex *x = new vertex("x");
    vertex *d = new vertex("d");
    vertex *c = new vertex("c");
    vertex *f = new vertex("f");
    vertex *v = new vertex("v");

    g.add_vertex(a);
    g.add_vertex(z);
    g.add_vertex(s);
    g.add_vertex(x);
    g.add_vertex(d);
    g.add_vertex(c);
    g.add_vertex(f);
    g.add_vertex(v);

    g.add_edge(s, a, 0);
    g.add_edge(s, x, 0);
    g.add_edge(a, z, 0);
    g.add_edge(x, d, 0);
    g.add_edge(x, c, 0);
    g.add_edge(d, c, 0);
    g.add_edge(d, f, 0);
    g.add_edge(c, f, 0);
    g.add_edge(c, v, 0);
    g.add_edge(f, v, 0);

    g.bfs(s);
}

void dfs() {

    graph g;

    vertex *a = new vertex("a");
    vertex *b = new vertex("b");
    vertex *c = new vertex("c");
    vertex *d = new vertex("d");
    vertex *e = new vertex("e");
    vertex *f = new vertex("f");

    g.add_vertex(a);
    g.add_vertex(b);
    g.add_vertex(c);
    g.add_vertex(d);
    g.add_vertex(e);
    g.add_vertex(f);

    g.add_edge(a, b, 0);
    g.add_edge(a, d, 0);
    g.add_edge(b, e, 0);
    g.add_edge(d, b, 0);
    g.add_edge(e, d, 0);
    g.add_edge(c, e, 0);
    g.add_edge(c, f, 0);

    g.dfs(a);

    g.show_visited();
    g.show_dfs();
}

// Djikstra no trabaja con pesos negativos
// relajar una arista:
// d(v) > d(u) + w(u, v)

int main() {
    bfs();
    return 0;
};