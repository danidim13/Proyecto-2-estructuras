#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H

#include "Graph.h"
#include <vector>
#include <list>
#include <cmath>
#include <random>

struct Genoma {
	std::vector<int> genes;
	double peso_total;
};

class GeneticSolver {
	public:
		typedef std::vector<int> gene_t;

		GeneticSolver(int p_crossover, int p_mutaciones, int gen_limit, Graph *grafo); // Daniel
		virtual ~GeneticSolver();

		Genoma crossover(Genoma g1, Genoma g2) const; // Daniel
		Genoma mutacion(Genoma g) const; // Luis

		void seleccionNatural();  // Luis
		void primeraGeneracion(); // Daniel
		void siguienteGeneracion(); // Luis

		std::vector<Genoma> getSuperiores() const;
		int getGenCounter() const;

		void solve(); // Daniel

		/**
		 * Esta función retorna un vertice aleatorio que no
		 * sea ni la fuente ni el destino. Efectivamente el rango
		 * es [1 , (m_grafo->order()-2)].
		 * @return El valor aleatorio generado.
		 */
		int randVert();

		/**
		 * Esta función retorna una posición aleatoria de un
		 * vector de tamaño size, tal que no sea ni la primera
		 * ni la ultima.
		 * @param size Tamaño del vector.
		 * @return Indíce dentro del rango [1, size-2].
		 */
		int randPos(size_t size);

	private:

		Graph *m_grafo;
		int m_crossover;
		int m_mutaciones;
		int m_gen_limit;

		std::list<Genoma> genepool;
		std::list<Genoma> superiores;

		// Miembros para la generacion aleatoria
		// Un generador
		std::mt19937 Rng;

		// Distribución para vertices
		std::uniform_int_distribution<int> vertexDist;

		bool esSolucion(std::vector<int> genoma, Graph grafo);

		double sumarTrayectorias(std::vector<int> genoma, Graph grafo);


};




#endif
