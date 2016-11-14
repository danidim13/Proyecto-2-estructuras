#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>

bool esSolucion(std::vector<double> genoma);

double sumarTrayectorias(std::vector<double> genoma, std::vector<std::vector<double>> adjMatrix);

#endif
