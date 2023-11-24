#include <iostream>
#include <load_data.hpp>

int main() {
    std::cout << "[*] Leyendo archivo de grafos...\n";

    std::vector<graph *> grafos = load_data("../data/input.json");

    return 0;
}