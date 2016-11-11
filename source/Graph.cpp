#include "Graph.h"
#include <limits>
#include <iostream>

typedef std::numeric_limits<double> D;

Graph::Graph()
{

}

Graph::Graph(int nodes): adjMatrix( nodes, std::vector<double>(nodes, D::infinity()) )
{
	for (size_t i = 0; i < adjMatrix.size(); i ++) {
		adjMatrix[i][i] = 0;
	}

}

Graph::~Graph()
{

}

int Graph::addVertex()
{
	int size = adjMatrix.size();
	for (auto it = adjMatrix.begin(); it != adjMatrix.end(); it++) {
		it->emplace_back(D::infinity());
	}
	adjMatrix.emplace_back(size + 1, D::infinity());
	adjMatrix[size][size] = 0;
	return size+1;
}

bool Graph::addEdge(int source, int dest, double weight)
{
	int size = adjMatrix.size();
	if (source < size && dest < size) {
		if (source == dest) {
			std::cerr << "Da fuck!" << std::endl;
			return false;
		}
		adjMatrix[source][dest] = weight;
		return true;
	}
	return false;
}

bool Graph::addEdgeBidir(int source, int dest, double weight)
{
	int size = adjMatrix.size();
	if (source < size && dest < size) {
		if (source == dest) {
			std::cerr << "Da fuck!" << std::endl;
			return false;
		}
		adjMatrix[source][dest] = weight;
		adjMatrix[dest][source] = weight;
		return true;
	}
	return false;
}

std::vector<double> Graph::getNeighbors(int v) const
{
	return std::vector<double>();
}

bool Graph::isEdge(int source, int dest) const
{
	return false;
}

double Graph::getEdge(int source, int dest) const
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
	for (auto it1 = adjMatrix.begin(); it1 != adjMatrix.end(); it1++) {
		for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << std::endl;
	}

}
