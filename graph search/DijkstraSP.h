#pragma once
#include <vector>
#include <queue>
#include <map>
#include "EdgeWeightedDigraph.h"
#include "PriorityQueue.h"

class DijkstraSP
{
private:
	std::map<int, DirectedEdge> edgeTo;
	std::vector<double> distToVect;
	Utils::PriorityQueue<int> pq;
	void relax(EdgeWeightedDigraph G, int v);

public:
	DijkstraSP() {};
	DijkstraSP(EdgeWeightedDigraph G, int s);
	double distTo(int v) const;					// Abstände vom Startvertex zu v
	bool hasPathTo(int v) const;				// Überprüft die existens eines Pfades
	std::vector<DirectedEdge> pathTo(int v);	// Kanten des kürzsesten Weges
};

