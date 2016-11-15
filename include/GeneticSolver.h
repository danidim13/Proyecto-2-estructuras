#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H

#include "Graph.h"
#include <vector>
#include <list>
#include <cmath>

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

	private:

		Graph *m_grafo;
		int m_crossover;
		int m_mutaciones;
		int m_gen_limit;

		std::list<Genoma> genepool;
		std::list<Genoma> superiores;

    bool esSolucion(std::vector<int> genoma, Graph grafo);

    double sumarTrayectorias(std::vector<int> genoma, Graph grafo);


};




#endif
