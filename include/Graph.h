#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
    public:
        /**
         * Constructor por defecto.
         * Inicia el grafo con cero nodos.
         */
        Graph();

        /**
         * Constructor que recibe el numero de vertices.
         * Reserva la memoria necesaria e inicializa
         * la matriz de adyacencia con todos los
         * vertices desconectados, es decir Xij = inf.
         */
        Graph(int nodes);

        /**
         * Desctructor por defecto
         */
        virtual ~Graph();

	/**
	 * Agrega un nuevo vertice al grafo.
	 * @return El índice del vértice en la
	 * matriz de adyacencia.
	 */
	int addVertex();

	/**
	 * Agrega una arista dirigida al grafo.
	 * @param source Vértice origen.
	 * @param dest Vértice destino.
	 * @param weight Peso de la arista.
	 * @return True si la operación tiene éxito.
	 */
	bool addEdge(int source, int dest, double weight);

	/**
	 * Agrega una arista no dirigida al grafo.
	 * Equivalente a invocar addEdge(source, dest, weight) addEdge(dest, source, weight).
	 * @param source Vértice origen.
	 * @param dest Vértice destino.
	 * @param weight Peso de la arista.
	 * @return True si la operación tiene éxito.
	 */
	bool addEdgeBidir(int source, int dest, double weight);

	/**
	 * Retorna las conexiones de un vertice
	 * en forma de un vector de pesos a otros
	 * nodos.
	 * @param v Índice del vértice en la matríz de
	 * adyacencia.
	 * @return Lista de pesos.
	 */
	std::vector<double> getNeighbors(int v) const;

	/**
	 * Determina si existe un arco de
	 * un vértice a otro.
	 * Existe un arco de source a dest
	 * si el peso en la matríz es adyacencia
	 * es finito.
	 * @param source Vértice fuente.
	 * @param dest Vértice destino.
	 * @return True si existe.
	 */
	bool isEdge(int source, int dest) const;

	/**
	 * Obtiene el peso de la arista que va
	 * desde source a dest.
	 * @param source Fuente.
	 * @param dest Destino.
	 * @Return Peso de la conexión.
	 */
	double getEdge(int source, int dest) const;

        /**
         * Retorna el orden del grafo.
         * @return El numero de vertices.
         */
        int order() const;

        /**
         * Retorna el tamano del grafo.
         * @return El numero de aristas.
         */
        int size() const;

        /**
         * Imprime la representacion del grafo.
         * En este caso, imprime la matriz de
         * adyacencia.
         */
        void print() const;

    private:
        typedef std::vector<std::vector<double>> matrix_type;

        std::vector<std::vector<double>> adjMatrix; /**<Matriz de adyacencia que representa al grafo.*/

};

#endif
