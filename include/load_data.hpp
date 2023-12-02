
#ifndef LOAD_DATA_HPP
#define LOAD_DATA_HPP

#include <dir_graph.hpp>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <und_graph.hpp>
#include <vector>

struct load_data {

    load_data(const std::string &s_file);

private:
    
    std::vector<directed_graph *> directed;
    std::vector<undirected_graph *> undirected;

    std::ifstream file_handler;
    Json::Value root;

    void load_dir_graph();
    void load_und_graph();

    void read_json();

    void run_dir_graph(directed_graph *g, Json::Value &algorithms);
    void run_und_graph(undirected_graph *g, Json::Value &algorithms);

    template <class T>
    void create_vertices(T *g, Json::Value &vertices);

    template <class T>
    void create_edges(T *g, Json::Value &edges);

    template <class T>
    T *create_graph(Json::Value &data);
};

#endif