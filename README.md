
# Grafo

Un grafo es un conjunto de vertices y aritas que los conectan entre si.

## Algoritmos implementados

### Breadth First Search (BFS)

* **Objetivo**: Recorrer todos los vertices de un grafo. Útil para encontrar la distancia desde un vertice de partida a todos los demas vertices. Su complejidad es lineal.

### Deep First Search (DFS)

* **Objetivo**: Recorrer todos los vertices de un grafo. Puede ser usado para encontrar los padres de cada vertice en un grafo. Se puede implementar en un grafo dirigido o no dirigido. Su complejidad es lineal y debe implementarse en un DAG (Directed Acyclic Graph).

### Topological Sort

* **Objetivo**: Ordenar los vertices de un grafo dirigido de tal manera que si existe una arista de u a v, entonces u aparece antes que v en el ordenamiento. Su complejidad es lineal y debe implementarse en un DAG (Directed Acyclic Graph).

### Dijkstra

* **Objetivo**: Encontrar el camino mas corto entre dos vertices o todos los vertices del grafo. Su complejidad es O((V+E) log V) usando una priority queue. No deben existir aristas con peso negativo.

## Requisitos

* C++
* CMake
* JsonCpp
* Visual Studio Code y C/C++ Extension pack