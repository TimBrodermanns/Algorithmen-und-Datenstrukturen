#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>
#include <Queue>


namespace Graphsearch {


	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		*/

	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {

		std::cout << v;
		
		marked[v] = true;

		for (int j = 0; j < G.getAdj(v).size(); j++) {

			int w = G.getAdj(v)[j].other(v);
			
			if (marked[w] == false) {
				edgeTo[w] = v;
				std::cout << " -> ";
				DFS_recursive(G, w, marked, edgeTo);
			}

		}
	}

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		bool ret = true;
		marked.clear();
		marked.resize(G.getV(), false);
		edgeTo.clear();
		edgeTo.resize(G.getV(), -1);
		DFS_recursive(G, v, marked, edgeTo);
		std::cout << std::endl;
		for (bool value : marked) ret = ret && value;
		return ret;
	}

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		bool ret = true;
		marked.clear();
		marked.resize(G.getV(), false);
		edgeTo.clear();
		edgeTo.resize(G.getV(), -1);
		std::queue<int> q;
		q.push(v);
		std::string out = "";
		bool firstLoop = true;
		while (!q.empty()) {
			v = q.front();
			q.pop();
			if (marked[v]) continue;
			marked[v] = true;
			if (firstLoop) out += std::to_string(v);
			else out += " -> " + std::to_string(v);
			firstLoop = false;
			bool first = true;
			for (int j = 0; j < G.getAdj(v).size(); j++) {
				int w = G.getAdj(v)[j].other(v);
				if (marked[w] == false) {
					edgeTo[w] = v;
					q.push(w);
				}
			}
		}
		std::cout << out << std::endl;
		for (bool value : marked) ret = ret && value;
		return ret;
	}
}
