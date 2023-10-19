
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

void dijkstra() {

    graph G;

    vertex *A = new vertex("A");
    vertex *B = new vertex("B");
    vertex *C = new vertex("C");
    vertex *D = new vertex("D");
    vertex *E = new vertex("E");

    G.add_vertex(A);
    G.add_vertex(B);
    G.add_vertex(C);
    G.add_vertex(D);
    G.add_vertex(E);

    G.add_edge(A, B, 4);
    G.add_edge(A, C, 2);
    G.add_edge(B, C, 5);
    G.add_edge(B, D, 10);
    G.add_edge(C, D, 3);
    G.add_edge(C, E, 2);
    G.add_edge(E, D, 7);

    G.dijkstra(E);
}

int main() {
    dfs();
    return 0;
};