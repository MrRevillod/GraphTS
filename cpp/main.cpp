
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

    std::vector<nivel *> bfs_result = g.bfs(s);
    g.show_bfs(bfs_result);
}

int main() {
    bfs();
    return 0;
};