#include "GeneticSolver.h"
#include <cmath>
#include <chrono>
#include <utility>
#include <iostream>
#include <map>
#include <unordered_map>

GeneticSolver::GeneticSolver(int p_crossover, int p_mutaciones, int p_indel, int p_indelS, int gen_limit, int p_pool, Graph *grafo):
	m_grafo(grafo),
	m_crossover(p_crossover),
	m_mutaciones(p_mutaciones),
	m_indel(p_indel),
	m_indelS(p_indelS),
	m_gen_limit(gen_limit),
	superiores(p_pool),
	Rng(std::chrono::system_clock::now().time_since_epoch().count()),
	vertexDist(1, grafo->order() - 2),
	sizeDist(2, grafo->order())
{
	double e, v;
	e = grafo->size();
	v = grafo->order();
	density = e/(v*(v-1));
	cant_superiores = p_pool;
	std::cout << "Creando GeneticSolver con " << m_gen_limit << " generaciones" << std::endl;
}

GeneticSolver::~GeneticSolver()
{

}

Genoma GeneticSolver::crossover(const Genoma &g1, const Genoma &g2)
{
	Genoma nuevo;
	size_t pos_cruzar1;
	size_t pos_cruzar2;

	/*
	if (g1.genes.size() == 2 || g2.genes.size() == 2){
		return (g1.total_size < g2.total_size) ? g1 : g2;
	}
	*/

	// La primera forma de hacer crossover es elegir un vertice al azar
	// en g1 y buscarlo en g2, si se encuentra entonces combinar ambos
	// genes en ese punto.

	int tries = 0;
	bool v_comun = false;
	while (tries < 6 && !v_comun) {

		// Se elige un vertice al azar del gen1
		pos_cruzar1 = randPosCross(g1.genes.size());
		int v1 = g1.genes[pos_cruzar1];
		pos_cruzar2 = 1;
		while (pos_cruzar2 < g2.genes.size() && !v_comun) {
			if (g2.genes[pos_cruzar2] == v1)
				v_comun = true;
			else
				pos_cruzar2++;
		}
		tries++;
	}
	if (!v_comun)
		//std::cerr << "No common vertex..." << std::endl;

	// Si la primera forma falla se intenta otra manera, se eligen dos posiciones al azar
	// de ambos genes y se determina si existe un arco entre ambos, en cuyo caso

	tries = 0;
	while (tries < 6 && !v_comun) {
		pos_cruzar1 = randPosCross(g1.genes.size());
		pos_cruzar2 = 1 + randPosCross(g2.genes.size());

		if (m_grafo->isEdge(g1.genes[pos_cruzar1], g2.genes[pos_cruzar2]))
			v_comun = true;
		else
			tries++;
	}
	if (!v_comun)
		//std::cerr << "No common edge..." << std::endl;

	// Una vez se probaron ambas formas se verifica si se encontró un cruce válido.
	if (v_comun) {

		g1.genes[pos_cruzar1] != g2.genes[pos_cruzar2] ? pos_cruzar1++ : 0;
		nuevo.genes.reserve(pos_cruzar1 + g2.genes.size() - pos_cruzar2);

		for (size_t i = 0; i < pos_cruzar1; i++) {
			nuevo.genes.push_back(g1.genes[i]);
		}

		for (size_t i = pos_cruzar2; i < g2.genes.size(); i++) {
			nuevo.genes.push_back(g2.genes[i]);
		}

		nuevo.peso_total = sumarTrayectorias(nuevo.genes, *m_grafo);
		return nuevo;
	}

	// Si aún así no se encontró un cruce válido entonces se retorna el genoma 1.
	//std::cout << "I gave up!" << std::endl;
	return g1;
}

Genoma GeneticSolver::mutacion(const Genoma &g){
	if(esSolucion(g.genes,*m_grafo)){
		if (g.genes.size() == 2) {
			//std::cerr << "Genoma inmutable" << std::endl;
			return g;
		}
			
		Genoma g_mutado = g;

		int iter = 0;
		int orig;
		size_t i;
		do {
			i = randPos(g_mutado.genes.size());
			orig = g.genes[i];
			g_mutado.genes[i] = randVert();
			iter ++;
		} while ( orig == g_mutado.genes[i] && !esSolucion(g_mutado.genes, *m_grafo) && iter < 5);

		g_mutado.peso_total = sumarTrayectorias(g_mutado.genes, *m_grafo);
		return g_mutado;

	}

	else{
		//std::cerr << "El genoma a mutar no es solucion" << std::endl;
		return g;
	}

}

Genoma GeneticSolver::indel(const Genoma &g)
{
	bool in = false;
	int tries;
	bool valid;
	
	// Si es de tamaño 2 a huevo es una inserción.
	if (g.genes.size() == 2)
		in = true;
	else
		in = (randVert()%2 == 0);


	// Lógica de inserción
	if (in) {
		// Posición despues de la cual insertar
		size_t pos_in = randPosCross(g.genes.size());


		// Vertice a insertar
		int v;
		valid = false;
		tries = 0;
		while (!valid && tries < 6) {
			v = randVert();
			if (v != g.genes[pos_in] && v != g.genes[pos_in+1]) {
				if ( m_grafo->isEdge(g.genes[pos_in], v) && m_grafo->isEdge(v, g.genes[pos_in+1]) )
					valid = true;
			}
			else
				++tries;
		}

		if (valid) {
			Genoma nuevo;
			for (size_t i = 0; i < g.genes.size(); i++) {
				nuevo.genes.push_back(g.genes[i]);
				if (i == pos_in) {
					nuevo.genes.push_back(v);
				}
			}
			nuevo.peso_total = sumarTrayectorias(nuevo.genes, *m_grafo);
			return nuevo;
		} else {
			//std::cerr << "Couldn't insert..." << std::endl;
			return g;
		}
	}

	// Logica de borrado
	if (!in) {
		size_t pos_del;

		valid = false;
		tries = 0;
		while (!valid && tries < 6) {
			pos_del = randPos(g.genes.size());
			if ( m_grafo->isEdge(g.genes[pos_del-1], g.genes[pos_del+1]) )
				valid = true;
			else
				++tries;
		}

		if (valid) {
			Genoma nuevo;
			for (size_t i = 0; i < g.genes.size(); i++) {
				if (i != pos_del)
					nuevo.genes.push_back(g.genes[i]);
			}
			nuevo.peso_total = sumarTrayectorias(nuevo.genes, *m_grafo);
			return nuevo;
		} else {
			//std::cerr << "Couldn't delete..." << std::endl;
			return g;
		}
	}

	std::cerr << "WTF en indel!" << std::endl;
	return g;
}

Genoma GeneticSolver::specialIndel(const Genoma &g1, const Genoma &g2)
{
	size_t g1_size = g1.genes.size();
	size_t g2_size = g2.genes.size();

	
	if ( g1.genes[g1_size-2] == g2.genes[1] ) {
		//std::cerr << "Las colas son iguales -_-" << std::endl;
		return g1;
	}
		
	// Vertice a insertar
	int v;
	bool valid = false;
	int tries = 0;
	while (!valid && tries < 6) {
		v = randVert();

		// El vertice tiene que ser diferente de los extremos
		if ( v != g1.genes[g1_size-2] && v!= g2.genes[1] ) {
			if ( m_grafo->isEdge(g1.genes[g1_size-2], v) && m_grafo->isEdge(v, g2.genes[1]) )
				valid = true;
		}
		else
			++tries;
	}

	if (valid) {
		Genoma nuevo;

		for (size_t i = 0; i < g1_size-1; i++) {
			nuevo.genes.push_back(g1.genes[i]);
		}

		nuevo.genes.push_back(v);

		for (size_t i = 1; i < g2_size; i++) {
			nuevo.genes.push_back(g2.genes[i]);
		}

		nuevo.peso_total = sumarTrayectorias(nuevo.genes, *m_grafo);
		return nuevo;
	} else {
		//std::cerr << "Couldn't special INDEL..." << std::endl;
		return g1;
	}
}

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
	max_pool_size = (size_t)(std::sqrt(n)*std::log2(n/2+1));
#elif defined POOL_RAIZ
	max_pool_size = (size_t)(std::sqrt(n));
#else
	// Caso por defecto
	max_pool_size = 20;
#endif

   	//Luego se debe llenar el pool.
	genepool.clear();

	// El maximo tamaño de una solución es n.
	Genoma tmp;
	tmp.genes.reserve(n);

	// Un mapa de int,bool para 'tachar'
	//std::map<int,bool> CheckList;
	//std::unordered_map<int,bool> CheckList(n);
	bool CheckList[n];
	for (int i=0; i < n; i++){
		CheckList[i] = false;
	}

	for (int i = 0; i < max_pool_size; i++) {

		int next_size = randSize();
		tmp.genes.push_back(0);

#if defined NO_CHECK_DUPLICATES
		// Generacion aleatoria pura
		for (int i = 1; i < next_size - 1; i++) {
			tmp.genes.push_back(randVert());
		}
#else
		// Generacion aleatoria comprobando con el checklist
		for (int i = 1; i < next_size - 1; i++) {
			int v;
			do {
				v = randVert();
			} while (CheckList[v]);
			CheckList[v] = true;

			tmp.genes.push_back(v);
		}
		// Se resetea el checklist
		for (int i=1; i < n-1; i++){
			CheckList[i] = false;
		}
#endif

		tmp.genes.push_back(n-1);


		// Luego esta se agrega al genepool.
		genepool.push_back(std::move(tmp));
		tmp.genes.clear();

	}

	// Una vez que se genero el pool inicial se deben
	// eliminar las que no son soluciones.

	for (auto it = genepool.begin(); it != genepool.end(); ) {
		if (esSolucion(it->genes,*m_grafo)){
			it->peso_total = sumarTrayectorias(it->genes,*m_grafo);
			it++;
		} else {
			it = genepool.erase(it);
		}
	}
}

Genoma GeneticSolver::minWeight(std::list<Genoma> &genepool){

	Genoma min;
	auto it_min = genepool.begin();

	for(auto it = genepool.begin(); it != genepool.end(); it++){
			if( (it->peso_total) < (it_min->peso_total) ){
				it_min = it;
			}

	}
		min = *it_min;
		genepool.erase(it_min);
		return min;
}

void GeneticSolver::seleccionNatural(){

	superiores[0] = minWeight(genepool);
	
	for(int i = 1; i < cant_superiores && !genepool.empty(); ){
		Genoma g = minWeight(genepool);
		if (g.peso_total != superiores[i-1].peso_total) {
			superiores[i] = g;
			i++;
		}
	}
}

void GeneticSolver::siguienteGeneracion(){

	// Primero se limpia el genepool
	genepool.clear();

	// Agregar superiores
	for (int i = 0; i < cant_superiores; i++) {
		genepool.push_back(superiores[i]);
	}

	// Crossover
	for(int i = 0; i<m_crossover ; i++){

		genepool.push_back( crossover(
				superiores[i%cant_superiores],
				superiores[(i+1)%cant_superiores]) );
	}

	// Mutaciones
	for(int i = 0; i<m_mutaciones; i++ ){
		genepool.push_back(
				mutacion(superiores[i%cant_superiores]));
	}

	
	// Special Indel
	for(int i = 0; i<m_indelS; i++ ){

		genepool.push_back( specialIndel(
				superiores[i%cant_superiores],
				superiores[(i+1)%cant_superiores]) );
	}

	// Indel
	for(int i = 0; i<m_indel; i++ ){

		genepool.push_back( indel(
				superiores[i%cant_superiores]));
	}
	

	return;
}

//std::vector<Genoma> GeneticSolver::getSuperiores() const{}

//int GeneticSolver::getGenCounter() const{}

void print(Genoma g) {
	for (size_t i = 0; i < g.genes.size(); i++) {
		std::cout << g.genes[i] << " ";
	}
	std::cout << "\tpeso: " << g.peso_total << std::endl;
}

void GeneticSolver::solve(){

	primeraGeneracion();

	/*
	std::cout << std::endl;
	std::cout << "Generacion inicial :" << std::endl << std::endl;
	for (auto it = genepool.begin(); it != genepool.end(); it++) {
		print(*it);
	}
	std::cout << std::endl;
	*/

	// Condicion de salida: n generaciones sin cambio
	//
	Genoma mejor_prev, peor_prev;
	int stasis = 0;
	int i = 0;

	seleccionNatural();

	while (stasis < m_gen_limit) {
		mejor_prev = superiores[0];
		peor_prev = superiores[cant_superiores-1];
		siguienteGeneracion();

		/*
		std::cout << std::endl;
		std::cout << "Generacion " << i << std::endl << std::endl;
		for (auto it = genepool.begin(); it != genepool.end(); it++) {
			print(*it);
		}
		std::cout << std::endl;
		*/

		seleccionNatural();
		if (mejor_prev.peso_total == superiores[0].peso_total && peor_prev.peso_total == superiores[cant_superiores-1].peso_total)
			stasis++;
		else
			stasis = 0;
		i++;
	}
	//


	// Condición de salida: n generaciones totales
	/*
	for(int i = 0; i < m_gen_limit; i++){

		seleccionNatural();
		siguienteGeneracion();

		//
		std::cout << std::endl;
		std::cout << "Generacion " << i << std::endl << std::endl;
		for (auto it = genepool.begin(); it != genepool.end(); it++) {
			print(*it);
		}
		std::cout << std::endl;
		//

	}

	seleccionNatural();
	*/

	genetic_solution = superiores[0];
	return;

}

int GeneticSolver::randVert()
{
	return vertexDist(Rng);
}

size_t GeneticSolver::randPosCross(size_t size)
{
	//if (size == 2)
		//return 0;
	std::uniform_int_distribution<size_t> dist(0, size-2);
	return dist(Rng);
}

size_t GeneticSolver::randPos(size_t size)
{
	if (size == 2)
		return 1;
	std::uniform_int_distribution<size_t> dist(1, size-2);
	return dist(Rng);
}

int GeneticSolver::randSize()
{
	return sizeDist(Rng);
}

bool GeneticSolver::esSolucion(const std::vector<int> &genes, const Graph &grafo) const{
	if(genes[0] == 0 && genes[genes.size() - 1] == grafo.order() -1){

		for(size_t i = 0; i < genes.size() - 1; i++){
			if ( !grafo.isEdge(genes[i], genes[i+1]) ) {
				//std::cout << "No hay link de " << genes[i] << " a " << genes[i+1] << std::endl;
				return false;
			}
		}
		return true;

	} else {
		return false;
	}
}


double GeneticSolver::sumarTrayectorias(const std::vector<int> &genes, const Graph &grafo)const{

	double suma_pesos = 0;

	for(size_t i = 0; i < genes.size() - 1; i++){
		suma_pesos = suma_pesos + grafo.getEdge(genes[i], genes[i+1]);
	}
	return suma_pesos;
}
