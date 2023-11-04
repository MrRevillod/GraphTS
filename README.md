

# Grafo

Un grafo es un conjunto de vertices y aritas que los conectan entre si.

## Conceptos

* **Vértice**: Es un nodo del grafo.
* **Arista**: Es una conexión entre dos vértices. Una arista puede tener un peso asociado, que representa una medida de distancia, costo u otra característica entre los vértices que conecta.
* **Grado**: Es el número de aristas que tiene un vértice.
* **Camino**: Es una secuencia de vértices conectados por aristas. Los caminos pueden ser simples (sin repetir vértices) o no simples (pueden repetir vértices).
* **Ciclo**: Es un camino que inicia y termina en el mismo vértice.
* **Grafo dirigido**: Es un grafo en el que las aristas tienen una dirección. Se utilizan comúnmente para representar relaciones asimétricas, como en un grafo de Internet, donde las aristas indican direcciones de enlace.
* **Grafo no dirigido**: Es un grafo en el que las aristas no tienen una dirección.


## Algoritmos

### Breadth First Search (BFS)

* **Significado**: Busqueda en anchura.

* **Objetivo**: Recorrer todos los vertices de un grafo.
* Útil para encontrar la distancia desde un vertice de partida a todos los demas vertices.

* **Complejidad**: O(V+E)

    - V: Numero de vertices.
    - E: Numero de aristas.

* **Ejemplo**:

```cpp

    void bfs(vertex *start) {

        std::vector<vertex *> frontera;
        frontera.push_back(start);
        niveles[start] = 0;

        int i = 1;

        while (!frontera.empty()) {

            std::vector<vertex *> next;

            for (const vertex *v : frontera) {
                for (const auto edge : v->adj) {

                    bool exist = std::find(frontera.begin(), frontera.end(), edge.first) != frontera.end();

                    if (!exist) {
                        vertex *to = edge.first;
                        next.push_back(to);
                        niveles[to] = i;
                    }
                }
            }

            frontera = next;
            i++;
        }
    }

```

### Deep First Search (DFS)

* **Significado**: Busqueda en profundidad.

* **Objetivo**: Recorrer todos los vertices de un grafo.
* Útil para encontrar ciclos en un grafo.

* **Complejidad**: O(V+E)

    - V: Numero de vertices.
    - E: Numero de aristas.

* **Ejemplo**:

```cpp

    void dfs(vertex *s) {

        visited[s] = true;

        for (const auto edge : s->adj) {

            if (!visited[edge.first]) {
                parents[edge.first] = s;
                dfs(edge.first);
            }
        }
    }

```

### Dijkstra

* **Objetivo**: Encontrar el camino mas corto entre dos vertices.
* Útil para encontrar el camino mas corto entre dos ciudades.

* Con el se pueden obtener las distancias mínimas entre un vertice
    de partida y todos los demas vertices.

* **Requisitos**:

    - No debe haber aristas con peso negativo

* **Problemas comunes**:

    - Encontrar el camino optimo para un trazado de lineas de comunicacion.

* **Complejidad**: O((V+E) log V)

    - V: Numero de vertices.
    - E: Numero de aristas.

* **Ejemplo**:

```cpp

    void dijkstra(vertex *start) {

        std::unordered_map<vertex *, int> distances;

        for (vertex *v : vertices) {
            distances[v] = oo;
        }

        distances[start] = 0;

        std::priority_queue<std::pair<vertex *, int>> pq;
        pq.push({start, 0});

        while (!pq.empty()) {

            vertex *u = pq.top().first;
            pq.pop();

            for (const auto edge : u->adj) {

                vertex *v = edge.first;
                int weight = edge.second;
                int distance = distances[u] + weight;

                if (distance < distances[v]) {
                    distances[v] = distance;
                    pq.push({v, -distance});
                }
            }
        }

        std::cout << "Distancias mínimas desde " << start->name << " a:" << std::endl;

        for (vertex *v : vertices) {
            std::cout << v->name << " -> " << (distances[v] == oo ? "∞" : std::to_string(distances[v])) << std::endl;
        }
    }

```

### Floyd Warshall

* **Objetivo**: Encontrar el camino mas corto entre todos los pares de vertices.
* Útil para encontrar el camino mas corto entre todos los pares de ciudades.

* **Requisitos**:

    - No debe haber aristas con peso negativo
    - Implementacion con matrices de adyacencia
    - Número de vertices <= 500

* **Problemas comunes**:

    - Encontrar el camino optimo para un trazado de lineas de comunicacion.

* **Complejidad**: O(V^3)

    - V: Numero de vertices.


### Bellman Ford