
#include <colormod.hpp>
#include <dir_graph.hpp>
#include <fstream>
#include <functional>
#include <load_data.hpp>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <und_graph.hpp>

template <class T>
T *create_graph(Json::Value &data) {

    std::string g_name = data["name"].asString();
    T *grafo = new T(g_name);

    std::map<std::string, std::function<void(vertex *)>> alg_map = {
        {"bfs", [&](vertex *v) { grafo->bfs(v); }},
        {"dfs", [&](vertex *v) { grafo->dfs(v); }},
        {"dijkstra", [&](vertex *v) { grafo->dijkstra(v); }}

    };

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

        vertex *v_from = grafo->get_vertex(from);
        vertex *v_to = grafo->get_vertex(to);
        int weight = std::stoi(weight_str);

        grafo->add_edge(v_from, v_to, weight);
    }

    grafo->show();

    for (auto a : data["algorithms"]) {

        std::string alg = a.asString();
        std::stringstream ss_alg(alg);
        std::string alg_name, start_name;

        std::getline(ss_alg, alg_name, ':');
        std::getline(ss_alg, start_name, ':');

        vertex *start_vertex = grafo->get_vertex(start_name);
        alg_map[alg_name](start_vertex);
    }

    return grafo;
}

void load_data(const std::string file_name) {

    std::cout << " " << std::endl;
    std::cout << Color::white << "Leyendo grafos desde: " << Color::def << Color::green << file_name << Color::def << std::endl;

    Json::Value root;
    std::ifstream file(file_name);
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, file, &root, &errs)) {
        std::cerr << errs << "\n";
        exit(EXIT_FAILURE);
    }

    for (auto g : root) {

        bool directed = g["directed"].asBool();

        if (!directed) {
            create_graph<undirected_graph>(g);
            continue;
        }

        create_graph<directed_graph>(g);
    }
}