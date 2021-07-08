
#include <assert.h>
#include "DijkstraSP.h"

/**
 * Füge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verläuft und deren
 * Ziel w dem Startknoten s am nächsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
	void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	/*
	 * TODO
	 */

	std::vector<DirectedEdge> edges = G[v];	//adjazente Knoten zum Knoten v
	for (DirectedEdge e : edges) {
		int w = e.to();
		if (distToVect[w] > distToVect[v] + e.weight()) {
			distToVect[w] = distToVect[v] + e.weight();
			edgeTo[w] = e;
			if (pq.contains(w)) pq.change(w, distToVect[v]);
			else pq.push(w, distToVect[w]);
		}
	}
}

/**
 * Fuehrt den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	/*
	 * TODO
	 */

	 //Initialisiere distToVect mit "unendlich"
	distToVect.resize(G.getV());
	for (int v = 0; v < G.getV(); v++) {
		distToVect[v] = DBL_MAX;
	}
	//Setze die Kosten für Startknoten auf 0
	distToVect[s] = 0.0;

	pq.push(s, 0.0);
	//Füge immer eine Kante mit minimalen Pfadkosten zu s hinzu
	while (!pq.empty()) {
		int min_node = pq.top().value;
		pq.pop();

		//Füge immer eine Kante mit minimalen Pfadkosten zu s der PQ hinzu
		relax(G, min_node);
	}
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v) const
{
	/*
	 * TODO
	 */
	return distToVect[v];
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
	/*
	 * TODO
	 */

	if (distToVect[v] == DBL_MAX) return false;
	return true;
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v)
{
	/*
	 * TODO
	 */

	std::vector<DirectedEdge> path;
	DirectedEdge e = edgeTo[v];

	while (true) {
		path.push_back(e);
		if (edgeTo.count(e.from()) > 0) {
			e = edgeTo[e.from()];
		}
		else break;
	}
	std::reverse(path.begin(), path.end());
	return path;
}