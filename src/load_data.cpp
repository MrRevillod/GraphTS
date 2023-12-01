
#include <colormod.hpp>
#include <dir_graph.hpp>
#include <fstream>
#include <functional>
#include <load_data.hpp>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <und_graph.hpp>

typedef std::map<std::string, std::function<void(vertex *)>> std_function_map;

void create_vertices(graph *graph, Json::Value &vertices) {
    for (auto v : vertices)
        graph->add_vertex(v.asString());
}

void create_edges(graph *graph, Json::Value &edges) {
    for (auto e : edges) {
        std::string edge = e.asString();
        std::stringstream ss_edge(edge);
        std::string from, to, weight_str;

        std::getline(ss_edge, from, ':');
        std::getline(ss_edge, to, ':');
        std::getline(ss_edge, weight_str, ':');

        int weight = std::stoi(weight_str);

        graph->add_edge(from, to, weight);
    }
}

template <class T>
void run_graph(T *graph, Json::Value &algorithms) {

    std_function_map alg_map = {
        {"bfs", [&](vertex *v) { graph->bfs(v); }},
        {"dfs", [&](vertex *v) { graph->dfs(v); }},
        {"dijkstra", [&](vertex *v) { graph->dijkstra(v); }}};

    graph->show();

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

        vertex *start_vertex = graph->get_vertex(start_name);
        alg_map[alg_name](start_vertex);
    }
}

template <class T>
T *create_graph(Json::Value &data) {

    std::string g_name = data["name"].asString();
    T *g = new T(g_name);

    create_vertices(g, data["vertices"]);
    create_edges(g, data["edges"]);

    return g;
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
            undirected_graph *graph = create_graph<undirected_graph>(g);
            run_graph<undirected_graph>(graph, g["algorithms"]);
            std::string input;
            std::cout << Color::green << "\nPresiona Enter para ver el siguiente grafo o \ncualquier otra tecla para salir: " << Color::def;
            std::getline(std::cin, input);
            if (!input.empty()) {
                break;
            }
            continue;
        }

        directed_graph *graph = create_graph<directed_graph>(g);
        run_graph<directed_graph>(graph, g["algorithms"]);

        std::string input;
        std::cout << Color::green << "\nPresiona Enter para ver el siguiente grafo o \ncualquier otra tecla para salir: " << Color::def;
        std::getline(std::cin, input);
        if (!input.empty()) {
            break;
        }
    }
}