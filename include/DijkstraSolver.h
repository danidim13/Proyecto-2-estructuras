#ifndef DIJKSTRASOLVER_H
#define DIJKSTRASOLVER_H

#include <vector>
#include <limits>

#include "Graph.h"



struct double_bool{

		double value;
		bool marked;
		bool prev_marked;
};

class DijkstraSolver{


	public:
			DijkstraSolver(int raiz,  Graph *grafo); // El constructor añade la primera fila, con un cero en raiz e inf en el resto

			virtual ~DijkstraSolver();

			std::vector<double_bool> nextRow(); // copia los elementos marcados en la fila anterior y llena los restantes con min()

			double Min(int column, int row); // devuelve min(DestValue, MarkedValue + EdgeWeight)

			void markMinimum(std::vector<double_bool> &fila); // marca el elemento minimo de una fila y pone en 1 prev_marked

			void markActualMinimum(std::vector<double_bool> &fila); // marca el elemento minimo de una fila y pone en 1 prev_marked

			int getMinimum(std::vector<double_bool> &fila);

			int getPrevMarked(std::vector<double_bool> &fila);

			void nextRow(int column);

			double solve(); // Añade las filas de la tabla hasta que el elemento marcado es el vertice de destino




	//private:

			std::vector<std::vector<double_bool>> table;
			Graph* g;

};


#endif
