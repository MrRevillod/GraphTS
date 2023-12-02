
#include <colormod.hpp>
#include <dir_graph.hpp>
#include <fstream>
#include <functional>
#include <load_data.hpp>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <und_graph.hpp>

using std_function_map = std::map<std::string, std::function<void(vertex *)>>;

load_data::load_data(const std::string &s_file) {

    file_handler.open(s_file);
    std::cout << Color::white << "Leyendo grafos desde: " << Color::def << Color::green << s_file << Color::def << std::endl;
    read_json();

    load_dir_graph();
    load_und_graph();

    for (directed_graph *g : directed) {
        for (auto json_graph : root) {

            if (!json_graph["directed"].asBool())
                continue;

            run_dir_graph(g, json_graph["algorithms"]);
        }
    }

    for (undirected_graph *g : undirected) {
        for (auto json_graph : root) {

            if (json_graph["directed"].asBool())
                continue;

            run_und_graph(g, json_graph["algorithms"]);
        }
    }
}

template <class T>
void load_data::create_vertices(T *g, Json::Value &vertices) {
    for (auto v : vertices) {
        g->add_vertex(v.asString());
    }
}

template <class T>
void load_data::create_edges(T *g, Json::Value &edges) {

    for (auto e : edges) {
        std::string edge = e.asString();
        std::stringstream ss_edge(edge);
        std::string from, to, weight_str;

        std::getline(ss_edge, from, ':');
        std::getline(ss_edge, to, ':');
        std::getline(ss_edge, weight_str, ':');

        std::size_t weight = std::stoul(weight_str);

        g->add_edge(from, to, weight);
    }
}

void load_data::run_und_graph(undirected_graph *g, Json::Value &algorithms) {

    std_function_map alg_map = {
        {"bfs", [&](vertex *v) { g->bfs(v); }},
        {"dfs", [&](vertex *v) { g->dfs(v); }},
        {"dijkstra", [&](vertex *v) { g->dijkstra(v); }},
        {"kruskal", [&](vertex *v) { g->kruskal(); }}

    };

    g->show();

    for (auto a : algorithms) {
        std::string alg = a.asString();
        std::stringstream ss_alg(alg);
        std::string alg_name, start_name;

        std::getline(ss_alg, alg_name, ':');
        std::getline(ss_alg, start_name, ':');

        if (!alg_map[alg_name]) {
            throw std::runtime_error("\n\n El algoritmo " + alg_name + "no está definido en el grafo.");
        }

        if (start_name.empty()) {
            throw std::runtime_error("\n\n Debes especificar un vertice de partida.");
        }

        vertex *start_vertex = g->get_vertex(start_name);
        alg_map[alg_name](start_vertex);
    }
}

void load_data::run_dir_graph(directed_graph *g, Json::Value &algorithms) {

    std_function_map alg_map = {
        {"bfs", [&](vertex *v) { g->bfs(v); }},
        {"dfs", [&](vertex *v) { g->dfs(v); }},
        {"dijkstra", [&](vertex *v) { g->dijkstra(v); }},
        {"topological-sort", [&](vertex *v) { g->topological_sort(); }}

    };

    g->show();

    for (auto a : algorithms) {
        std::string alg = a.asString();
        std::stringstream ss_alg(alg);
        std::string alg_name, start_name;

        std::getline(ss_alg, alg_name, ':');
        std::getline(ss_alg, start_name, ':');

        if (!alg_map[alg_name]) {
            throw std::runtime_error("\n\n El algoritmo " + alg_name + "no está definido en el grafo.");
        }

        if (start_name.empty()) {
            throw std::runtime_error("\n\n Debes especificar un vertice de partida.");
        }

        vertex *start_vertex = g->get_vertex(start_name);
        alg_map[alg_name](start_vertex);
    }
}

template <class T>
T *load_data::create_graph(Json::Value &data) {

    std::string g_name = data["name"].asString();
    T *g = new T(g_name);

    create_vertices<T>(g, data["vertices"]);
    create_edges<T>(g, data["edges"]);

    return g;
}

void load_data::read_json() {
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!parseFromStream(builder, file_handler, &root, &errs)) {
        throw std::runtime_error(errs);
    }
}

void load_data::load_dir_graph() {
    for (auto g : root) {
        bool is_directed = g["directed"].asBool();

        if (!is_directed)
            continue;

        directed_graph *gra = create_graph<directed_graph>(g);
        directed.emplace_back(gra);
    }
}

void load_data::load_und_graph() {
    for (auto g : root) {
        bool is_directed = g["directed"].asBool();

        if (is_directed)
            continue;

        undirected_graph *gra = create_graph<undirected_graph>(g);
        undirected.emplace_back(gra);
    }
}