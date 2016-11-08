#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
    public:
        /**
         * Constructor por defecto.
         * Inicia e grafo con cero nodos.
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
        std::vector<std::vector<double>> adjMatrix; /**<Matriz de ayacencia que representa al grafo.*/

};

#endif
