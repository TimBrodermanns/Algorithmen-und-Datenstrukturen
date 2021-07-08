#pragma once
#include <string>
#include <vector>
#include <iomanip>

class Edge
{
private:
	int		_either;  // ein Knoten der Kante
	int		_other;   // der andere Knoten der Kante
	double	_weight;  // Kantengewicht
public:
	Edge(int either, int other, double weight)
		: _either{ either }
		, _other{ other }
		, _weight{ weight }
	{}

	double weight() const { return _weight; } // Gewicht dieser Kante
	int either() const { return _either; }    // einer der beiden Knoten
	int other(int vertex) const {			  // der von "vertex" verschiedene Knoten
		if (vertex == _either) return _other;
		else if (vertex == _other) return _either;
		else throw new std::invalid_argument("Illegal endpoint");
	}
};

inline bool operator==(const Edge& lhs, const Edge& rhs) { return lhs.weight() == rhs.weight(); }
inline bool operator!=(const Edge& lhs, const Edge& rhs) { return !operator==(lhs, rhs); }
inline bool operator< (const Edge& lhs, const Edge& rhs) { return lhs.weight() < rhs.weight(); }
inline bool operator> (const Edge& lhs, const Edge& rhs) { return  operator< (rhs, lhs); }
inline bool operator<=(const Edge& lhs, const Edge& rhs) { return !operator> (lhs, rhs); }
inline bool operator>=(const Edge& lhs, const Edge& rhs) { return !operator< (lhs, rhs); }


class EdgeWeightedGraph
{
private:
	int V;  // Anzahl Knoten von G
	int E;  // Anzahl Kanten von G
	std::vector<std::vector<Edge>> adj; // Adjazenzliste
	bool validateVertex(int v) const;
	void validateVertexWithError(int v) const;
public:
	EdgeWeightedGraph(int V);			     // Leeren Graph mit v Knoten erstellen
	EdgeWeightedGraph(std::string filename); // Graph einlesen aus Textdatei
	EdgeWeightedGraph(int V, std::vector<Edge> E);
	void add(Edge e);  						 // fügt Kante e dem Graphen hinzu
	int getV() const;            			 // liefert Anzahl Knoten
	int getE() const;            			 // liefert Anzahl der Kanten
	std::vector<Edge> getAdj(int v) const;	 // liefert Array der adjazenten Kanten zu v
	std::vector<std::vector<Edge>> getAdj() const;
	std::vector<Edge> edges() const;	 	 // alle Kanten dieses Graphen
	const std::vector<Edge> operator[](int v) const;
};

