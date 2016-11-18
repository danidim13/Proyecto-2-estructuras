#ifndef GENETICSOLVER_H
#define GENETICSOLVER_H

#include "Graph.h"
#include <vector>
#include <list>
#include <cmath>

/**
 * Struct: Genoma
 * Contiene una lista de vertices y la suma de los pesos entre cada vertice
 */

struct Genoma {
	std::vector<int> genes;
	double peso_total;
};

class GeneticSolver {
	public:
		typedef std::vector<int> gene_t;

		/**
		 * Constructor
		 * Recibe el numero de mutaciones y crossovers que se van a realizar por generacion,
		 * y un parametro gen_limit para terminar de iterar despues de un cierto numero de generaciones
		 */

		GeneticSolver(int p_crossover, int p_mutaciones, int gen_limit, Graph *grafo); // Daniel

		/**
		 * Destructor
		 */

		virtual ~GeneticSolver();

		/**
		 * Toma dos genomas y los cruza para generar uno nuevo
		 * @return Genoma cruzado
		 * @param g1 El primer genoma
		 * @param g2 El segundo genoma
		 */
		Genoma crossover(Genoma g1, Genoma g2) const; // Daniel

		/**
		 * Toma un genoma y devuelve una mutacion aleatoria del mismo
		 * @return Genoma la mutacion del g
		 * @param g Genoma por mutar
		 */
		Genoma mutacion(Genoma g) const; // Luis

		/**
		 * FIXME no me acuerdo que hace seleccionNatural
		 *
		 */

		void seleccionNatural(); // Luis

		/**
		 * Crea una primera generacion de genomas para comenzar a iterar
		 * Llena el genepool con 10 individuos generados aleatoriamente.
		 */
		void primeraGeneracion(); // Daniel

		/**
		 * Crea un nuevo genepool mutando los mejores genomas del actual genepool
		 */

		void siguienteGeneracion(); // Luis


		/**
		 * Devuelve una lista de genomas con los mejores que se encuentren en el genepool
		 * @return vector<genoma> La lista de mejores genomas
		 */

		std::vector<Genoma> getSuperiores() const;

		/**
		 * FIXME no me acuerdo que hace getGenCounter
		 */

		int getGenCounter() const;

		/**
		 * Realiza las iteraciones de generaciones correspondientes hasta encontrar una solucion adecuada
		 * @return Genoma el mejor de los individuos del genepool/solucion optima
		 */

		Genoma solve(); // Daniel

	private:

		Graph *m_grafo; /**<Puntero hacia el grafo por resolver.*/
		int m_crossover; /**<Numero de crossovers por realizar en el proceso de evolucion.*/
		int m_mutaciones; /**<Numero de mutaciones por realizar en el proceso de evolucion.*/
		int m_gen_limit; /**<Numero de generaciones por evolucionar antes de devolver la solucion optima.*/

		std::list<Genoma> genepool; /**<Genepool: poblacion de genomas que son solucion del grafo.*/
		std::list<Genoma> superiores; /**<Individuos del genepool con el minimo peso de todos.*/

    bool esSolucion(const std::vector<int> &genoma, const Graph &grafo)const; /**<Determina si un genoma es solucion del grafo.*/

    double sumarTrayectorias(const std::vector<int> &genoma, const Graph &grafo)const; /**<Suma los pesos entre vertices de un genoma.*/


};




#endif
