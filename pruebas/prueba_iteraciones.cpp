/** @file prueba_iteraciones.cpp
 * Prueba1.
 * Recibe por linea de comandos:
 * <num_pruebas> <prueba>
 * donde prueba es un numero entre 1 y 4.
 */

#include <iostream>
#include "GeneticSolver.h"
#include "Graph.h"
#include <ctime>
#include <fstream>
#include <cstdlib>


using namespace std;

int main(int argc, char* argv[])
{
    // Comparar tiempos de ejecucion para diferentes tamaños de matrices

	// Numero de pruebas
    int n_pruebas = atoi(argv[1]); 

	// Cantidad de pruebas a promediar
    int promedio = 30;

	// Eje x de la grafica -> cantidad de Vertices
    double *vert_size = new double[n_pruebas];
	 
	// Eje Y -> Tiempos de las diferentes iteraciones
    double exe_times[n_pruebas][promedio];
    double *exe_times_prom = new double[n_pruebas];

    // Abrir archivo donde se van a escribir los resultados de la prueba
    std::ofstream outFile;       
    
    cout << "Prueba para diferentes valores de V." << endl;
    
	outFile.open("prueba_iteraciones1.txt");
	cout << "Corriendo " << n_pruebas << " pruebas para GeneticSolver" << endl;

    
    outFile.precision(10);

    // Se corren las pruebas varias veces para
    // promediar los resultados.
    int vertices;   

    for(int p = 0; p < promedio; p++){
        for(int i = 0; i < n_pruebas; i++){
            vertices = 20 + ((double)i*2);    

			// Crear grafo
			Graph g(vertices);

			double r;
			for (int i = 1; i < g.order(); i++) {
				for (int j = 0; j < i; j++) {
					r = ((double) rand() / (RAND_MAX));
					(i-j <= (g.order()-2)) ? g.addEdgeBidir(i,j,70+r*100) : 0 ;
				}
			}
			// Camino mas corto!
			// 0 -> 7 -> 3 -> 5 -> 11 -> 18 -> 19: 65.62
			g.addEdgeBidir(0,7,5.2);
			g.addEdgeBidir(7,3,1.9);
			g.addEdgeBidir(3,5,11.4);
			g.addEdgeBidir(5,11,16.4);
			g.addEdgeBidir(11,18,8.92);
			g.addEdgeBidir(18,19,22);
			
			// otro camino corto!
			// 0 -> 15 -> 6 -> 3 -> 12 -> 19: 35.7 
			g.addEdge(0,15,3.1);
			g.addEdge(15,6,9.9);
			g.addEdge(6,3,12.2);
			g.addEdge(3,12,2.8);
			g.addEdge(12,19,7.7);
			//
			// 0 -> 7 -> 3 -> 12 -> 19 : 17.6
			// 0 -> 15 -> 6 -> 3 -> 5 -> 11 -> 18 -> 19: 83.92


			// Crear solver
          	int crossover = 4;
			int mutaciones = 4;
			int indel = 4;
			int indelS = 4;
			int gen_limit = 60;
			int pool = 4;
			GeneticSolver s(crossover, mutaciones, indel, indelS, gen_limit, pool, &g);
    
			// Medir el tiempo de solucion del algoritmo
			clock_t begin = clock(); 
            s.solve();
            clock_t end = clock();
            double elapsed_secs = ((double)(end - begin)) / CLOCKS_PER_SEC;
    
			// Asignar los valores correspondientes
            exe_times[i][p] = elapsed_secs;
            if (p == 0) {
                vert_size[i] = vertices;
            }
        }
    }
    
	// Calcular promedios y escribir al archivo
    for (int i = 0; i < n_pruebas; i++){
        double sum = 0;
        for (int p = 0; p < promedio; p++) {
            sum += exe_times[i][p];
        }
        exe_times_prom[i] = sum/promedio;
        outFile << exe_times_prom[i] << "\t" << vert_size[i] << endl;
    }
    
    delete[] exe_times_prom;
    delete[] vert_size;
    outFile.close();
    cout << "Finalizando pruebas!" << endl << endl;
    
    return 0;
}
