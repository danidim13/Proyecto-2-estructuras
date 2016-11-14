#include <vector>
#include <limits>
#include <cmath>

#include "Functions.h"


typedef std::numeric_limits<double> D;

bool esSolucion(std::vector<int> genoma, Graph grafo){
  if(genoma[0] == 0 && genoma[genoma.size() - 1] == grafo.order() -1 ){

      if(std::isfinite(sumarTrayectorias(genoma,grafo)) )
        return true;

      else
        return false;
   }
   else
    return false;
}

double sumarTrayectorias(std::vector<int> genoma, Graph grafo){

  double suma_pesos = 0;

  for(int i = 0; i < genoma.size(); i++){
    suma_pesos = suma_pesos + grafo.getEdge(genoma[i], genoma[i+1]);
  }
  return suma_pesos;
}
