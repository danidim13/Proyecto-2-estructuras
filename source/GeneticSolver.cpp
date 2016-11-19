#include "GeneticSolver.h"
#include <chrono>
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
do
	{
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

void GeneticSolver::primeraGeneracion(){}

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

    for(int i = 0; i < genes.size() - 1; i++){
      suma_pesos = suma_pesos + grafo.getEdge(genes[i], genes[i+1]);
    }
    return suma_pesos;
}
