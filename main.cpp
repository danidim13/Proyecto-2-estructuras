//#include <random>
//#include <functional>
//#include <chrono>
#include <iostream>
#include <cstdlib>
#include "Graph.h"
#include "GeneticSolver.h"

using namespace std;

int main(int argc, char* argv[]) {
	/*
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generador(seed1);
	std::uniform_int_distribution<int> uniform(0,9);
	auto mk2 = std::bind(uniform,generador);

	for (int i = 0; i < 100; i++) {
		if (i%20 == 0) {
			cout << endl;
		}
		cout << mk2() << " ";
	}

	cout << endl;

	for (int i = 0; i < 10; i++) {
		cout << generador() << endl;
	}

	*/

	
	cout << "Grafo" << endl;
	Graph g(5000);

	double r;
	for (int i = 1; i < g.order(); i++) {
		for (int j = 0; j < i; j++) {
			r = ((double) rand() / (RAND_MAX));
			g.addEdgeBidir(i,j,r*100);
		}
	}

	// g.print();
	GeneticSolver s(5,5,5,&g);

	/* Probar esSolucion
	g.addEdgeBidir(0,14,100);
	g.addEdgeBidir(0,5,950);
	g.addEdgeBidir(14,5,123);
	g.addEdgeBidir(0,2,101);
	g.addEdgeBidir(2,3,154);
	g.addEdgeBidir(3,5,434);

	g.addEdge(5,7,420);
	g.addEdge(0,7,-8);


	std::vector<int> v0 = {0,5,5,14};
	std::vector<int> v1 = {0,2,3,5};
	std::vector<int> v2 = {0,7,5,14};
	std::vector<int> v3 = {9,9};
	std::vector<int> v4 = {20,20};
	std::vector<int> v5 = {1,5,3,4,1,6,3};
	cout << "Probando esSolucion" << endl;
	if (s.esSolucion(v0,g))
		cout << "Exito" << endl;
	else
		cout << "FAIL" << endl;

	if (!s.esSolucion(v1,g))
		cout << "Exito" << endl;
	else
		cout << "FAIL" << endl;
	if (!s.esSolucion(v2,g))
		cout << "Exito" << endl;
	else
		cout << "FAIL" << endl;
	if (!s.esSolucion(v3,g))
		cout << "Exito" << endl;
	else
		cout << "FAIL" << endl;
	if (!s.esSolucion(v4,g))
		cout << "Exito" << endl;
	else
		cout << "FAIL" << endl;
	if (!s.esSolucion(v5,g))
		cout << "Exito" << endl;
	else
		cout << "FAIL" << endl;

	*/

	
	/*
	cout << "Vertices aleatorios" << endl;
	for (int i = 0; i < 20; i++) {
		cout << s.randVert() << endl;
	}
	cout << endl;
	
	cout << "Posiciones aleatorias size = 10" << endl;
	for (int i = 0; i < 20; i++) {
		cout << s.randPos(10) << endl;
	}
	cout << endl;
	*/

	cout << "Intento de primera generacion" << endl;
	s.primeraGeneracion();

	for (auto it = s.genepool.begin(); it != s.genepool.end(); it++) {
		for (auto it2 = it->genes.begin(); it2 != it->genes.end(); it2++) {
		cout << *it2 << " ";
		}
		cout << endl;
	}
	cout << "Fin!" << endl;
	cout << s.genepool.size() << " vectores generados" << endl;

	return 0;
}
