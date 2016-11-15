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

bool GeneticSolver::esSolucion(std::vector<int> genoma, Graph grafo){}

double sumarTrayectorias(std::vector<int> genoma, Graph grafo){}
