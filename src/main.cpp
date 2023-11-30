#include <iostream>
#include <load_data.hpp>
#include <und_graph.hpp>

int main() {
    // load_data("../data/input.json");

    undirected_graph *grafo = new undirected_graph("grafo1");

    grafo->add_vertex(new vertex("a"));
    grafo->add_vertex(new vertex("b"));
    grafo->add_vertex(new vertex("c"));
    grafo->add_vertex(new vertex("d"));
    grafo->add_vertex(new vertex("e"));
    grafo->add_vertex(new vertex("f"));
    grafo->add_vertex(new vertex("h"));

    grafo->add_edge(grafo->get_vertex("a"), grafo->get_vertex("b"), 100);
    grafo->add_edge(grafo->get_vertex("a"), grafo->get_vertex("c"), 200);
    grafo->add_edge(grafo->get_vertex("a"), grafo->get_vertex("d"), 300);
    grafo->add_edge(grafo->get_vertex("a"), grafo->get_vertex("e"), 400);
    grafo->add_edge(grafo->get_vertex("a"), grafo->get_vertex("f"), 500);
    grafo->add_edge(grafo->get_vertex("a"), grafo->get_vertex("h"), 600);
    grafo->add_edge(grafo->get_vertex("b"), grafo->get_vertex("c"), 700);
    grafo->add_edge(grafo->get_vertex("b"), grafo->get_vertex("d"), 800);
    grafo->add_edge(grafo->get_vertex("b"), grafo->get_vertex("e"), 900);
    grafo->add_edge(grafo->get_vertex("b"), grafo->get_vertex("f"), 600);
    grafo->add_edge(grafo->get_vertex("b"), grafo->get_vertex("h"), 600);
    grafo->add_edge(grafo->get_vertex("c"), grafo->get_vertex("d"), 400);
    grafo->add_edge(grafo->get_vertex("c"), grafo->get_vertex("e"), 500);
    grafo->add_edge(grafo->get_vertex("c"), grafo->get_vertex("f"), 600);
    grafo->add_edge(grafo->get_vertex("c"), grafo->get_vertex("h"), 600);
    grafo->add_edge(grafo->get_vertex("d"), grafo->get_vertex("e"), 500);
    grafo->add_edge(grafo->get_vertex("d"), grafo->get_vertex("f"), 600);
    grafo->add_edge(grafo->get_vertex("d"), grafo->get_vertex("h"), 600);
    grafo->add_edge(grafo->get_vertex("e"), grafo->get_vertex("f"), 600);
    grafo->add_edge(grafo->get_vertex("e"), grafo->get_vertex("h"), 600);
    grafo->add_edge(grafo->get_vertex("f"), grafo->get_vertex("h"), 600);

    undirected_graph *mst = grafo->kruskal();

    mst->show();

    return 0;
}