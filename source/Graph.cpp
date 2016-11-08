#include "Graph.h"
#include <limits>

typedef std::numeric_limits<double> D;

Graph::Graph()
{
}

Graph::Graph(int nodes): adjMatrix(nodes, std::vector<int>(nodes, D::infinity() ))
{

}
