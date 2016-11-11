# Método Dijkstra y Algoritmos Genéticos

**Universidad de Costa Rica**

**Estructuras Abstractas de Datos y Algoritmos**

**Proyecto 2**

Integrantes:
* Daniel Díaz
* Luis F. Mora

## Objetivos


* Establecer la representación genética del dominio de la solución al problema del camino más corto.

* Establecer una función de aptitud según la solución óptima del método Dijkstra.

* Encontrar una solución al problema del camino más corto que utilice una complejidad menor al método
Dijkstra mediante AG implementados en C++.

## Clase Grafo

Recordar meter >> `typedef std::vector<vertex> Genoma` (pero esto iría en la clase GeneticSolver no?)

* `void crearVertice()` // añade una fila y columna a la matriz de adyacencia
* `void crearArista(int source, int dest, double peso)` // cambia el peso de la arista conectando a source con dest
* `std::vector<double> DevolverVecinos(int)` // Devuelve la fila de vecinos de la matriz de adyacencia
* `double devolverArista(int source, int dest)` // Devuelve el peso de la arista conectando a source con dest

## Funciones para el Algoritmo Genetico

* `bool esSolucion(std::list<int> genoma)` // Determina si un genoma es solucion para moverse de un nodo A otro B
* `double sumarTrayectorias(std::list<int> genoma)` // Determina la suma de los pesos de todas las aristas recorridas en genoma

## AlgoritmoGenetico // GeneticSolver

* `Genoma RandomGenoma()` // Genera un genoma random para el inicio de las iteraciones
* `Genoma Crossover(Genoma G1, Genoma G2)` // Devuelve un genoma con el crossover de G1 y G2
* `Genoma Mutar(Genoma G1)` // Muta el genoma para crear un nuevo genoma mejor o peor que el anterior

    - Condiciones del mutado:
        1. Fijarse que el nodo a reemplazar no este repetido
        2. Asegurar que el nodo a reemplazar tiene conexiones con los vecinos
        3. Tomar un vertice de todos los que resultan validos de las condiciones anteriores.


## Lista de tareas pendientes

### Daniel

- [x] Definir y documentar los métodos del Grafo (parámetros, return types, etc). __9/11__
- [x] Implementar métodos para añadir vértices y aristas, `addVertex()` y `addEdge()`. __10/11__
- [ ] Implementar métodos para comprobar la existencia de una arista entre dos nodos y obtener su peso, `isEdge()` y `getEdge()`.
- [x] Implementar métodos de información: número de vértices/aristas, imprimir. __10/11__
- [ ] Validar implementación.

### Luis

- [ ] Implementar método `esSolucion()`.
- [ ] Implementar método `sumarTrayectorias()`.
- [ ] Validar implementación.

### Sin asignar
- [ ] Hacer Makefile con targets: all, clean, tests, run
- [ ] Definir y documentar los miembros y métodos de la clase GeneticSolver. Definir paramétros y return types de los métodos, etc.
- [ ] Implementar y validar métodos definidos (expandir esta tarea una vez se sepa cuáles van a ser).
- [ ] Definir estrategias de cruze para genomas (número de generaciones, probabilidad de cruze\mutacion, cantidad de padres...).
- [ ] Obtener complejidad teórica del algoritmo genético.
- [ ] Definir pruebas para obtener la complejidad experimental. (Se puede reciclar la estructura del proyecto pasado!)
- [ ] Obtener algoritmo Dijkstra de algún lado.
- [ ] Definir pruebas para comparar tiempo entre ambos algoritmos.
