#include <dir_graph.hpp>
#include <iostream>
#include <load_data.hpp>

int main() {
    std::cout << "[*] Leyendo archivo de grafos...\n";

    load_data("../data/input.json");

    return 0;
}