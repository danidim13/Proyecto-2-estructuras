#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include "Graph.h"

bool esSolucion(std::vector<int> genoma, Graph grafo);

double sumarTrayectorias(std::vector<int> genoma, Graph grafo);

#endif
