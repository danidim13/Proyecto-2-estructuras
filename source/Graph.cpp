#include "Graph.h"
#include <limits>

typedef std::numeric_limits<double> D;

Graph::Graph()
{

}

Graph::Graph(int nodes): adjMatrix( nodes, std::vector<double>(nodes, D::infinity()) )
{

}

Graph::~Graph()
{

}

int Graph::addVertex()
{
	return 0;
}

bool Graph::addEdge(int source, int dest, double weight)
{
	return false;
}

std::vector<double> Graph::getNeighbors(int v) const
{
	return std::vector<double>();
}

bool Graph::isArc(int source, int dest) const
{
	return false;
}

double Graph::getArc(int source, int dest) const
{
	return 0;
}

int Graph::order() const
{
	return 0;
}

int Graph::size() const
{
	return 0;
}

void Graph::print() const
{

}
