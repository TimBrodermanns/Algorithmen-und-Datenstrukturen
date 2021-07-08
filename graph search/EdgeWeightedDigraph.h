#pragma once
#include <vector>
#include <string>

class DirectedEdge
{
private:
	int _from;		// Startknoten
	int _to;		// Endknoten
	double _weight;	// Gewicht der Kante
public:
	DirectedEdge()
		: _from{ 0 }
		, _to{ 0 }
		, _weight{ 0 }
	{}

	DirectedEdge(int from, int to, double weight)
		: _weight{ weight }
		, _from{ from }
		, _to{ to }
	{}

	double weight() const { return _weight; }
	int from() const { return _from; }
	int to() const { return _to; }
};

inline bool operator==(const DirectedEdge& lhs, const DirectedEdge& rhs) { return lhs.weight() == rhs.weight(); }
inline bool operator!=(const DirectedEdge& lhs, const DirectedEdge& rhs) { return !operator==(lhs, rhs); }
inline bool operator< (const DirectedEdge& lhs, const DirectedEdge& rhs) { return lhs.weight() < rhs.weight(); }
inline bool operator> (const DirectedEdge& lhs, const DirectedEdge& rhs) { return  operator< (rhs, lhs); }
inline bool operator<=(const DirectedEdge& lhs, const DirectedEdge& rhs) { return !operator> (lhs, rhs); }
inline bool operator>=(const DirectedEdge& lhs, const DirectedEdge& rhs) { return !operator< (lhs, rhs); }

class EdgeWeightedDigraph {
private:
	int V;													// Anzahl Knoten von G
	int E;													// Anzahl Kanten von G
	std::vector<std::vector<DirectedEdge>> adj;				// Adjazenzliste
	bool validateVertex(int v) const;
	void validateVertexWithError(int v) const;
public:
	EdgeWeightedDigraph(int V);								// Leeren Digraphen mit v Knoten erstellen
	EdgeWeightedDigraph(std::string filename);				// Graph einlesen aus Textdatei
	void add(DirectedEdge e);								// gerichtete Kante hinzufügen
	int getV() const;										// liefert Anzahl Knoten	
	int getE() const;										// liefert Anzahl der Kanten
	std::vector<std::vector<DirectedEdge>> getAdj() const;	// liefert die gestamte Kantenliste
	std::vector<DirectedEdge> getAdj(int v) const;			// liefert Array der adjazenten Kanten zu v
	std::vector<DirectedEdge> edges() const;				// alle Kanten dieses Graphen
	const std::vector<DirectedEdge> operator[](int v) const;
};

