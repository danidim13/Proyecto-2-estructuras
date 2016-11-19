#include "GeneticSolver.h"
#include <chrono> 

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
//Genoma GeneticSolver::mutacion(Genoma g) const {}

void GeneticSolver::seleccionNatural(){}

void GeneticSolver::primeraGeneracion(){}

void GeneticSolver::siguienteGeneracion(){}

//std::vector<Genoma> GeneticSolver::getSuperiores() const{}

//int GeneticSolver::getGenCounter() const{}

void GeneticSolver::solve(){}

int GeneticSolver::randVert()
{
	return vertexDist(Rng);
}

int GeneticSolver::randPos(size_t size)
{
	std::uniform_int_distribution<int> dist(1, size-2);
	return dist(Rng);
}

int GeneticSolver::ranSize()
{
	return sizeDist(Rng);
}

bool GeneticSolver::esSolucion(std::vector<int> genoma, Graph grafo){

  if(genoma[0] == 0 && genoma[genoma.size() - 1] == grafo.order() -1 ){

      if(std::isfinite(sumarTrayectorias(genoma,grafo)) )
        return true;

      else
        return false;
   }
   else
    return false;
}

double GeneticSolver::sumarTrayectorias(std::vector<int> genoma, Graph grafo){

    double suma_pesos = 0;

    for(int i = 0; i < genoma.size(); i++){
      suma_pesos = suma_pesos + grafo.getEdge(genoma[i], genoma[i+1]);
    }
    return suma_pesos;
}

