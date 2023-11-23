
#include <dir_graph.hpp>
#include <iostream>
#include <limits>
#include <string>

void bfs() {

    directed_graph g = directed_graph("Grafo I");

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

    g.show_props();
    g.bfs(s);
    g.dfs(s);
}

void dijkstra() {

    directed_graph g = directed_graph("Grafo II");

    vertex *A = new vertex("A");
    vertex *B = new vertex("B");
    vertex *C = new vertex("C");
    vertex *D = new vertex("D");
    vertex *E = new vertex("E");

    g.add_vertex(A);
    g.add_vertex(B);
    g.add_vertex(C);
    g.add_vertex(D);
    g.add_vertex(E);

    g.add_edge(A, B, 1);
    g.add_edge(B, C, 3);
    g.add_edge(A, D, 4);
    g.add_edge(D, E, 2);
    g.add_edge(E, C, 1);

    g.show_props();
    g.dijkstra(A);
    g.topological_sort();
}

int main() {
    bfs();
    dijkstra();
    return 0;
}