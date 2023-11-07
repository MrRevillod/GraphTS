
# Grafo

Un grafo es un conjunto de vertices y aritas que los conectan entre si.

## Conceptos

* **Vértice**: Es un nodo del grafo.
* **Arista**: Es una conexión entre dos vértices. Una arista puede tener un peso asociado, que representa una medida de distancia, costo u otra característica entre los vértices que conecta.
* **Grado**: Es el número de aristas que tiene un vértice.
* **Camino**: Es una secuencia de vértices conectados por aristas. Los caminos pueden ser simples (sin repetir vértices) o no simples (pueden repetir vértices).
* **Ciclo**: Es un camino que inicia y termina en el mismo vértice.
* **Grafo dirigido**: Es un grafo en el que las aristas tienen una dirección.
* **Grafo no dirigido**: Es un grafo en el que las aristas no tienen una dirección.

* **Grafo bipartito**: Es un grafo cuyos vértices pueden ser divididos en dos conjuntos disjuntos U y V, de tal manera que cada arista conecta un vértice en U con uno en V. Los grafos bipartitos se utilizan comúnmente para modelar problemas de asignación.

* **Camino de Euler**: Es un camino que recorre cada arista de un grafo exactamente una vez. Un grafo tiene un camino de Euler si y solo si todos sus vértices tienen grado par, o si exactamente dos vértices tienen grado impar y todos los demás tienen grado par. Un ciclo de Euler es un camino de Euler que comienza y termina en el mismo vértice.

* **Relajar una arista**: En el algorithm de Dijkstra, relajar una arista significa actualizar la distancia de un vértice v si se encuentra un camino más corto a v a través de un vértice u.

* **Complejidad algoritmica**:
    
    **V**: Numero de vertices.
    **E**: Numero de aristas.
    
    | BFS | O(V+E) |

    | DFS | O(V+E) |

    | Dijkstra | O((V+E) log V) |

    | Bellman Ford | O(V*E) |

    | Floyd Warshall | O(V^3) |

    | Árbol de expansión mínima (Prim) | O(E log V) |

    | Árbol de expansión mínima (Kruskal) | O(E log V) |

## Algoritmos

### Breadth First Search (BFS)

* **Complejidad**: O(V+E)
* **Objetivo**: Recorrer todos los vertices de un grafo.
* Útil para encontrar la distancia desde un vertice de partida a todos los demas vertices.

* Se puede implementar en un grafo dirigido o no dirigido.

* Al ser un recorrido en anchura se recorren todos los vertices de un nivel antes de pasar al siguiente nivel. O sea se pasa por todos los vertices que estan a una distancia de 1, luego por todos los vertices que estan a una distancia de 2, etc.

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

                    bool exist = std::find(frontera.begin(), 
                        frontera.end(), edge.first) != frontera.end();

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

* **Complejidad**: O(V+E)
* **Objetivo**: Recorrer todos los vertices de un grafo.
* Puede ser usado para encontrar los padres de cada vertice en un grafo. Se puede implementar en un grafo dirigido o no dirigido.

* Al ser un recorrido en profundidad se visita un vertice y así sucesivamente hasta que no se pueda seguir avanzando, luego se retrocede al vertice anterior y se continua con el siguiente vertice si lo hay.

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

### Topological Sort

* **Complejidad**: O(V+E)
* **Objetivo**: Ordenar los vertices de un grafo dirigido de tal manera que si existe una arista de u a v, entonces u aparece antes que v en el ordenamiento.

* **Requisitos**:
    - El grafo debe ser dirigido y aciclico.

* **Ejemplo**:

```cpp
    Grafo dirigido aciclico:
    Dependiendo del orden de insercion de los vertices b y e.

    a --> b --> c --> d
    |
    >--> e --> f

    Ordenamiento topologico: a, b, c, d, e, f  ||  a, e, f, b, c, d
```

### Dijkstra

* **Complejidad**: O((V+E) log V)
* **Objetivo**: Encontrar el camino mas corto entre dos vertices o todos los vertices del grafo.

* **Requisitos**:
    - No debe haber aristas con peso negativo

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

        std::cout << "Distancias mínimas desde " << 
            start->name << " a:" << std::endl;

        for (vertex *v : vertices) {
            std::cout << v->name << " -> " << (distances[v] == oo 
            ? "∞" : std::to_string(distances[v])) << std::endl;
        }
    }
```

### Bellman Ford

* **Objetivo**: Encontrar camino más corto a un vertice a otro o todos los vertices del grafo

* En este caso pueden existir aristas con peso/ponderación negativa
* No puede existir un ciclo de aristas negativas

* **Complejidad**: O(V*E)


### Floyd Warshall

* **Objetivo**: Encontrar el camino mas corto entre todos los pares de vertices aunque no estén conectados

* **Requisitos**:
    - No debe haber aristas con peso negativo
    - Implementacion con matrices de adyacencia
    - Número de vertices <= 500

* **Problemas comunes**:
    - Encontrar el camino optimo para un trazado de lineas de comunicacion.

* **Complejidad**: 
    - Algoritmica: O(V^3) (Por los 3 ciclos anidados)
    - Espacial: O(V^2) (Por la matriz de adyacencia)
