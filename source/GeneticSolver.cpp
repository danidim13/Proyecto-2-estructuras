#include "GeneticSolver.h"

GeneticSolver::GeneticSolver(int p_crossover, int p_mutaciones, int gen_limit, Graph *grafo){}

GeneticSolver::~GeneticSolver(){}

Genoma GeneticSolver::crossover(Genoma g1, Genoma g2) const{}

Genoma GeneticSolver::mutacion(Genoma g) const {}

void GeneticSolver::seleccionNatural(){}

void GeneticSolver::primeraGeneracion(){}

void GeneticSolver::siguienteGeneracion(){}

std::vector<Genoma> GeneticSolver::getSuperiores() const{}

int GeneticSolver::getGenCounter() const{}

void GeneticSolver::solve(){}

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
