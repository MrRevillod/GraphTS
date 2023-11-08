
#include "dir_graph.hpp"
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string>

void bfs() {

    directed_graph g;
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

    directed_graph g;
    vertex *uno = new vertex("1");
    vertex *dos = new vertex("2");
    vertex *tres = new vertex("3");
    vertex *cuatro = new vertex("4");
    vertex *cinco = new vertex("5");
    vertex *seis = new vertex("6");

    g.add_vertex(uno);
    g.add_vertex(dos);
    g.add_vertex(tres);
    g.add_vertex(cuatro);
    g.add_vertex(cinco);
    g.add_vertex(seis);

    g.add_edge(uno, dos, 0);
    g.add_edge(uno, tres, 0);
    g.add_edge(dos, cuatro, 0);
    g.add_edge(cuatro, cinco, 0);
    g.add_edge(cuatro, seis, 0);

    g.dfs(uno);
    g.show_dfs();
}

void dijkstra() {

    directed_graph g;
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

    g.dijkstra(A);
    g.topological_sort();
}

int main() {

    dijkstra();

    return 0;
}