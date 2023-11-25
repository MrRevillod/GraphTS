#ifndef LOAD_DATA_HPP
#define LOAD_DATA_HPP

#include <graph.hpp>
#include <iostream>
#include <json/json.h>
#include <vector>

std::vector<graph *> load_data(const std::string file_name);

#endif