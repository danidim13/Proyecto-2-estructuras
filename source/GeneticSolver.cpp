#include "GeneticSolver.h"
#include <cmath>
#include <chrono> 
#include <utility>
#include <iostream>

GeneticSolver::GeneticSolver(int p_crossover, int p_mutaciones, int gen_limit, Graph *grafo):
	m_grafo(grafo), m_crossover(p_crossover),
	m_mutaciones(p_mutaciones), m_gen_limit(gen_limit),
	Rng(std::chrono::system_clock::now().time_since_epoch().count()),
	vertexDist(1, grafo->order() - 2),
	sizeDist(2, grafo->order())
{

}

GeneticSolver::~GeneticSolver()
{

}

//Genoma GeneticSolver::crossover(Genoma g1, Genoma g2) const{}
;
Genoma GeneticSolver::mutacion(const Genoma &g){
	if(esSolucion(g.genes,*m_grafo)){
		Genoma g_mutado = g;

		int iter = 0;
		int orig;
		int i;
		do {
			i = randPos(g_mutado.genes.size());
			orig = g.genes[i];
			g_mutado.genes[i] = randVert();
			iter ++;
		} while ( orig == g_mutado.genes[i] && !esSolucion(g_mutado.genes, *m_grafo) && iter < 5);

		return g_mutado;

	}

	else{
		std::cerr << "El genoma a mutar no es solucion" << std::endl;
		return Genoma();
	}

}

void GeneticSolver::seleccionNatural(){}

void GeneticSolver::primeraGeneracion()
{

	genepool.clear();
	/* Se debe definir el tamaño del pool inicial, se agregarán un cierto número de posibles soluciones
	 * generadas de manera aleatoria, luego para cada una de estas se comprobará si es una solución
	 * real. El tamaño de este conjunto debe ser lo suficientemente grande para encontrar varias soluciones
	 * diferentes. Se puede alterar la estrategia para definir este numero con los macros POOL_<estrategia>.
	 * En el análisis de este parámetro toma como 'n' el número de vértices. Además cabe destacar
	 * que el número de aristas para un grafo bidireccional en el cual existe una solucion se encuentra
	 * dentro del rango [n-1, n*(n+1)/2]. Es decir, O(n) ~ O(n^2).
	 */
	int max_pool_size;
	int n = m_grafo->order();

#if defined POOL_LINEAL
	max_pool_size = n;
#elif defined POOL_LOGRAIZ
	max_pool_size = (size_t)(std::sqrt(n)*std::log2(n+1));
#elif defined POOL_RAIZ
	max_pool_size = (size_t)(std::sqrt(n));
#else 
	// Caso por defecto
	max_pool_size = 20;
#endif

	// Luego se debe llenar el pool.
	genepool.clear();

	// El maximo tamaño de una solución es n.
	Genoma tmp;
	tmp.genes.reserve(n);

	for (int i = 0; i < max_pool_size; i++) {

		/* Se genera una posible solución de manera
		 * aleatoria. No se verifica si hay repetidos.
		 */
		int next_size = randSize();
		tmp.genes.push_back(0);
		for (int i = 1; i < next_size - 1; i++) {
			tmp.genes.push_back(randVert());
		}
		tmp.genes.push_back(n-1);

		// Luego esta se agrega al genepool.
		genepool.push_back(std::move(tmp));
		tmp.genes.clear();

	}

	// Una vez que se genero el pool inicial se deben
}

void GeneticSolver::siguienteGeneracion(){}

//std::vector<Genoma> GeneticSolver::getSuperiores() const{}

//int GeneticSolver::getGenCounter() const{}

Genoma GeneticSolver::solve(){}

int GeneticSolver::randVert()
{
	return vertexDist(Rng);
}

int GeneticSolver::randPos(size_t size)
{
	std::uniform_int_distribution<int> dist(1, size-2);
	return dist(Rng);
}

int GeneticSolver::randSize()
{
	return sizeDist(Rng);
}

bool GeneticSolver::esSolucion(const std::vector<int> &genes, const Graph &grafo) const{
		if(genes.size() != 0){
  			if(genes[0] == 0 && genes[genes.size() - 1] == grafo.order() -1){
        		if(std::isfinite(sumarTrayectorias(genes,grafo)) )
          		return true;

        		else
          		return false;
      }
     else
       return false;
  	 } else std::cerr << "Error: genes vacios" << std::endl;
}


double GeneticSolver::sumarTrayectorias(const std::vector<int> &genes, const Graph &grafo)const{

    double suma_pesos = 0;

    for(size_t i = 0; i < genes.size() - 1; i++){
      suma_pesos = suma_pesos + grafo.getEdge(genes[i], genes[i+1]);
    }
    return suma_pesos;
}
