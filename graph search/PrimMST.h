#pragma once
#include <vector>
#include <queue>

#include "EdgeWeightedGraph.h"

class PrimMST
{
private:
	std::vector<bool> marked;	// MST-Knoten
	std::vector<Edge> mst;		// MST-Kanten
	/*
	 * PriorityQueue die alle Kanten speichert und mit pq.top()
	 * die Kante mit dem kleinsten Gewicht zurueck gibt.
	 */
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
public:
	PrimMST() {}
	PrimMST(EdgeWeightedGraph G, int s);
	void visit(EdgeWeightedGraph G, int v);
	std::vector<Edge> edges() const;
	double weight() const;
};

