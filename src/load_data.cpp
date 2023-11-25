#include <dir_graph.hpp>
#include <fstream>
#include <load_data.hpp>
#include <sstream>
#include <stdlib.h>
#include <und_graph.hpp>

template <class T>
T *create_graph(Json::Value &data) {

    T *grafo = new T("a");

    for (auto v : data["vertices"]) {
        grafo->add_vertex(new vertex(v.asString()));
    }

    for (auto e : data["edges"]) {
        std::string edge = e.asString();
        std::stringstream ss_edge(edge);
        std::string from, to, weight_str;

        std::getline(ss_edge, from, ':');
        std::getline(ss_edge, to, ':');
        std::getline(ss_edge, weight_str, ':');

        int weight = std::stoi(weight_str);

        grafo->add_edge(grafo->get_vertex(from), grafo->get_vertex(to), weight);
    }

    return grafo;
}

std::vector<graph *> load_data(const std::string file_name) {

    Json::Value root;
    std::ifstream file(file_name);
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, file, &root, &errs)) {
        std::cerr << errs << "\n";
        exit(EXIT_FAILURE);
    }

    std::vector<graph *> grafos;

    for (auto g : root) {

        bool directed = g["directed"].asBool();

        if (!directed) {
            undirected_graph *grafo = create_graph<undirected_graph>(g);
            grafos.emplace_back(grafo);
            continue;
        }
        directed_graph *grafo = create_graph<directed_graph>(g);
        grafos.emplace_back(grafo);
    }

    return grafos;
}