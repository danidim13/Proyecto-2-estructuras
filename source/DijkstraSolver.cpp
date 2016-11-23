#include "DijkstraSolver.h"
#include <iostream>

typedef std::numeric_limits<double> D;


DijkstraSolver::DijkstraSolver(int raiz, Graph *grafo):g(grafo){

	table.resize(g -> order());

	std::vector<double_bool> firstRow;

	firstRow.resize(grafo->order());

	double_bool null;

	null.value = 0;
	null.marked = 0;
	null.prev_marked = 0;

	double_bool initial;

	initial.value = D::infinity();
	initial.marked = 0;
	initial.prev_marked = 0;

	firstRow[0] = null;

	for(int i = 1; i <= grafo->order(); i++){

		firstRow[i] = initial;
	}

	table[0] = firstRow;

}

DijkstraSolver::~DijkstraSolver(){}

std::vector<double_bool> DijkstraSolver::nextRow(){



}

double DijkstraSolver::Min(int column, int row){

	if(!table[column][row].marked){

		double arg1 = table[column - 1][row].value;

		double arg2 = table[column][getPrevMarked(table[column])].value +

		g->getEdge(getPrevMarked(table[column -1]), row);

		return std::min(arg1,arg2);

	}
	else{
		std::cerr << "Element already marked" << std::endl;
	}

}

void DijkstraSolver::markMinimum(std::vector<double_bool> &fila){

	int index_min = getMinimum(fila);

	fila[index_min].marked = 1;
	fila[index_min].prev_marked = 1;

}

void DijkstraSolver::markActualMinimum(std::vector<double_bool> &fila){


}

int DijkstraSolver::getMinimum(std::vector<double_bool> &fila){

		int index_min = 0;

		auto it1 = fila.begin();
		it1 ++;

		for(auto it2 = fila.begin(); it2 != fila.end(); it2++){
			if((*it2).value < (*it1).value && !(*it2).marked)
					it1 = it2;
		}

		index_min = distance(fila.begin(), it1);

		std::cout << "El indice del minimo es: " << index_min << std::endl;

		return index_min;
}

int DijkstraSolver::getPrevMarked(std::vector<double_bool> &fila){

		for(int i = 0; i < fila.size(); i++){

				if(fila[i].prev_marked) return i;
		}
	//	std::cout << "No previously marked minumums" << std::endl;
		return 0;

}

void DijkstraSolver::nextRow(int column){

	// copiar los elementos marcados de la fila anterior
	table[column] = table[column-1];

	for(int i = 0; i < g->order(); i++ ){

		if(!table[column][i].marked){
			table[column][i].value = Min(column,i);
			//table[column][i].marked = 0;
			//table[column][i].prev_marked = 0;
		} else{
			table[column][i].prev_marked = 0;
		}

	}


}


double DijkstraSolver::solve(){

		markMinimum(table[0]);
		int i = 1;

		std::cout << "Entrando al do-while" << std::endl;
		do{

			nextRow(i);
			std::cout << "Filas Añadidas: " << i << std::endl;
			markMinimum(table[i]);
			i++;
			if(getMinimum(table[i]) == g->order() -1 )
				std::cout << "Solucion lista" << std::endl;
				//return table[10][10].value;

		}while(i< g->order());

		std::cout << "Saliendo del do-while" << std::endl;

		//double min_weight = table[i][g->order()].value;


		return 0;

}
