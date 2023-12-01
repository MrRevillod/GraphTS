#include <iostream>
// #include <load_data.hpp>
#include <und_graph.hpp>

int main() {
    // load_data("../data/input.json");

    undirected_graph *grafo = new undirected_graph("grafo1");

    grafo->add_vertex("a");
    grafo->add_vertex("b");
    grafo->add_vertex("c");
    grafo->add_vertex("d");
    grafo->add_vertex("e");
    grafo->add_vertex("f");

    grafo->add_edge("a", "b", 100);
    grafo->add_edge("a", "c", 200);
    grafo->add_edge("a", "d", 300);
    grafo->add_edge("a", "e", 400);
    grafo->add_edge("a", "f", 500);
    grafo->add_edge("b", "c", 700);
    grafo->add_edge("b", "d", 800);
    grafo->add_edge("b", "e", 900);
    grafo->add_edge("b", "f", 600);
    grafo->add_edge("c", "d", 400);
    grafo->add_edge("c", "e", 500);
    grafo->add_edge("c", "f", 600);
    grafo->add_edge("d", "e", 500);
    grafo->add_edge("d", "f", 600);
    grafo->add_edge("e", "f", 600);

    undirected_graph *mst = grafo->kruskal();

    mst->show();

    return 0;
}