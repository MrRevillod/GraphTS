
# Grafo

Un grafo es un conjunto de vertices y aritas que los conectan entre si.

## Conceptos

* **Vértice**: Es un nodo del grafo.
* **Arista**: Es una conexión entre dos vértices. Una arista puede tener un peso asociado, que representa una medida de distancia, costo u otra característica entre los vértices que conecta.
* **Grado**: Es el número de aristas que tiene un vértice.
* **Ciclo**: Es un camino que inicia y termina en el mismo vértice.

* **Camino de Euler**: Es un camino que recorre cada arista de un grafo exactamente una vez. Un grafo tiene un camino de Euler si y solo si todos sus vértices tienen grado par, o si exactamente dos vértices tienen grado impar y todos los demás tienen grado par. Un ciclo de Euler es un camino de Euler que comienza y termina en el mismo vértice.

* **Relajar una arista**: En el algorithm de Dijkstra, relajar una arista significa actualizar la distancia de un vértice v si se encuentra un camino más corto a v a través de un vértice u.

## Algoritmos

### Coloreo de grafos

* **Complejidad**: NP-Completo
* **Objetivo**: Asignar un color a cada vertice de un grafo de tal manera que dos vertices adyacentes no tengan el mismo color.

* **Número cromático**: Es el menor número de colores que se necesitan para colorear un grafo.

- **Aplicación**: Coloreo de un mapa de tal manera que dos paises adyacentes no tengan el mismo color.

### Emparejamiento de grafos

* **Complejidad**: O(V*E)
* **Objetivo**: Encontrar el mayor numero de aristas que no se intersecten entre si.

- **Aplicación**: Encontrar el mayor numero de parejas de personas que se gusten entre si.

### Breadth First Search (BFS)

* **Complejidad**: O(V+E)
* **Objetivo**: Recorrer todos los vertices de un grafo.
* Útil para encontrar la distancia desde un vertice de partida a todos los demas vertices.

* Se puede implementar en un grafo dirigido o no dirigido.

* Al ser un recorrido en anchura se recorren todos los vertices de un nivel antes de pasar al siguiente nivel. O sea se pasa por todos los vertices que estan a una distancia de 1, luego por todos los vertices que estan a una distancia de 2, etc.

### Deep First Search (DFS)

* **Complejidad**: O(V+E)
* **Objetivo**: Recorrer todos los vertices de un grafo.
* Puede ser usado para encontrar los padres de cada vertice en un grafo. Se puede implementar en un grafo dirigido o no dirigido.

* Al ser un recorrido en profundidad se visita un vertice y así sucesivamente hasta que no se pueda seguir avanzando, luego se retrocede al vertice anterior y se continua con el siguiente vertice si lo hay.

- **Aplicación cotidiana**: Encontrar la salida de un laberinto.

### Topological Sort

* **Complejidad**: O(V+E)
* **Objetivo**: Ordenar los vertices de un grafo dirigido de tal manera que si existe una arista de u a v, entonces u aparece antes que v en el ordenamiento.

* **Requisitos**:
    - El grafo debe ser dirigido y aciclico.

### Dijkstra

* **Complejidad**: O((V+E) log V)
* **Objetivo**: Encontrar el camino mas corto entre dos vertices o todos los vertices del grafo.

* **Requisitos**:
    - No debe haber aristas con peso negativo

### Bellman Ford

* **Complejidad**: O(V*E)

* **Objetivo**: Encontrar camino más corto a un vertice a otro o todos los vertices del grafo

* En este caso pueden existir aristas con peso/ponderación negativa
* No puede existir un ciclo de aristas negativas


### Floyd Warshall

* **Complejidad**: 
    - Algoritmica: O(V^3) (Por los 3 ciclos anidados)
    - Espacial: O(V^2) (Por la matriz de adyacencia)

* **Objetivo**: Encontrar el camino mas corto entre todos los pares de vertices aunque no estén conectados

* **Requisitos**:
    - Sin ciclos de peso negativo
    - Implementacion con matrices de adyacencia
    - Número de vertices <= 500

* **Problemas comunes/cotidianos**:
    - Encontrar el camino más corto entre todas las ciudades de una región.
