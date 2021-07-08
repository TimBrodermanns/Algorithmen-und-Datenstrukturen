#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"

using namespace std;

bool isInGrapf(EdgeWeightedGraph gr, int v) {
	if (v > gr.getV()) return false;
	else return true;
}

void PrintGrapf(EdgeWeightedGraph g) {

	vector<vector<Edge>> adj = g.getAdj();
	
	cout << endl;
	for (int i = 0; i < g.getV(); i++) {
		cout << i << " -> ";
		for (int j = 0; j < adj[i].size(); j++) {
			cout << adj[i][j].other(i) << "[" << adj[i][j].weight() << "]";
			if (j < adj[i].size() - 1) {
				cout << " -> ";
			}
		}
		cout << endl;
	}
}


void print_digraph(EdgeWeightedDigraph graph) {

	int prev = -1;
	for (DirectedEdge e : graph.edges()) {
		if (e.from() != prev) {
			cout << endl << e.from();
		}
		cout << " -> " << e.to() << " [" << e.weight() << "] ";
		prev = e.from();
	}

	cout << endl << endl;
}


void main_menu() {
	string graph;
	while (true) {
		cout << endl << "Praktikum 5: Graphenalgorithem:" << endl
			<< "1) Graph einlesen" << endl
			<< "2) Tiefensuche" << endl
			<< "3) Breitensuche" << endl
			<< "4) MST nach Prim" << endl
			<< "5) MST nach Kruskal" << endl
			<< "6) Kuerzeste Wege nach Dijkstra" << endl
			<< "7) Ausgabe der Adjazenzliste" << endl
			<< "8) Programm beenden" << endl
			<< "? > ";

		string input;
		cin >> input;
		if (input == "1") {
			int auswahl;
			cout << endl << "Graph einlesen" << endl;
			cout << "1) Graph1" << endl;
			cout << "2) Graph2" << endl;
			cout << "3) Graph3" << endl;
			cout << "?> ";
			cin >> auswahl;
			if (auswahl == 1) {
				cout << endl << "Graph 1 wurde eingelesen" << endl;
				graph = "graph1.txt";
			}
			else if (auswahl == 2) {
				cout << endl << "Graph 2 wurde eingelesen" << endl;
				graph = "graph2.txt";
			}
			else if (auswahl == 3) {
				cout << endl << "Graph 3 wurde eingelesen" << endl;
				graph = "graph3.txt";
			}
			else {
				cout << endl << "Graph nicht gefunden" << endl;
			}
		}

		EdgeWeightedGraph gra(graph);
		EdgeWeightedDigraph wgra(graph);

		if (graph == "") {
			cout << endl << "Bitte Graphen einlesen" << endl;
			continue;
		}
		if (input == "2") {
			int such;
			cout << endl << "Suche nach ?> ";
			cin >> such;
			vector<bool> marked;
			vector<int>  edgeTo;
			
			if (!isInGrapf(gra, such)) {
				cout << "Unzulässiege eingabe" << endl;
				continue;
			}

			cout << "Tiefensuche(Depth - First - Search(DFS)) - Startknoten: " << such << endl;
			cout << "Besuchsreihenfolge :" << endl;
			if (Graphsearch::DFS(gra, such, marked, edgeTo)) cout << endl << "Graph ist zusammenhaengend" << endl;
			else cout << endl << "Graph ist nicht zusammenhaengend" << endl;
			
		}
		else if (input == "3") {
			int such;
			cout << endl << "Startpunkt ?> ";
			cin >> such;
			vector<bool> marked;
			vector<int>  edgeTo;
			
			if (!isInGrapf(gra, such)) {
				cout << "Unzulässiege eingabe" << endl;
				continue;
			}

			cout << "Breitensuche (Breadth-First-Search (BFS)) - Startknoten: " << such << endl;
			cout << "Besuchsreihenfolge :" << endl;
			if (Graphsearch::BFS(gra, such, marked, edgeTo)) cout << endl << "Graph ist zusammenhaengend" << endl;
			else cout << endl << "Graph ist nicht zusammenhaengend" << endl;

		}

		else if (input == "4") {
			int start = 0;
			cout << endl << "Start Knoten ?> ";
			cin >> start;


			if (!isInGrapf(gra, start)) {
				cout << "Unzulässiege eingabe" << endl;
				continue;
			}

			PrimMST test(gra, start);
			cout << "Minimaler Spannbaum(MST) nach Prim :" << endl;
			cout << "Gewicht: " << test.weight();
			vector<Edge> mst = test.edges();

			vector<int> vorhan;
			cout << endl;
			for (Edge e : mst) {
				int vorhanden = 0;
				for (int i : vorhan) { if (e.either() == i) { vorhanden++; } }
				if (vorhanden == 0) {
					cout << e.either();
					for (Edge z : mst) {
						if (z.either() == e.either()) {
							cout << " -> " << z.other(z.either()) << " [" << z.weight() << "] ";
						}
					}
					cout << endl;
				}
				vorhan.push_back(e.either());
			}
		}
		else if (input == "5") {
			KruskalMST test(gra);

			cout << "Minimaler Spannbaum(MST) nach Kruskal :" << endl;
			cout << "Gewicht: " << test.weight();
			vector<Edge> mst = test.edges();

			vector<int> vorhan;
			cout << endl;
			for (Edge e : mst) {
				int vorhanden = 0;
				for (int i : vorhan) { if (e.either() == i) { vorhanden++; } }
				if (vorhanden == 0) {
					cout << e.either();
					for (Edge z : mst) {
						if (z.either() == e.either()) {
							cout << " -> " << z.other(z.either()) << " [" << z.weight() << "] ";
						}
					}
					cout << endl;
				}
				vorhan.push_back(e.either());
			}
		}

		else if (input == "6") {
			int start = 0;
			int ziel = 0;

			cout << endl << "Start Knoten ?> ";
			cin >> start;

			if (!isInGrapf(gra, start)) {
				cout << "Unzulässiege eingabe" << endl;
				continue;
			}
			cout << endl << "Ziel Knoten ?>";
			cin >> ziel;

			if (!isInGrapf(gra, ziel)) {
				cout << "Unzulässiege eingabe" << endl;
				continue;
			}

			DijkstraSP dijkstra(wgra, start);
			vector<DirectedEdge> path = dijkstra.pathTo(ziel);
			print_digraph(wgra);
			double kosten = 0.0;
			string out = "";
			cout << "Pfad: ";
			for (DirectedEdge de : path) {
				kosten += de.weight();
				out += to_string(de.from()) + " [" + to_string(de.weight()) + "] " + " -> ";
			}

			if (kosten == 0.0) {
				cout << "Kein Weg gefunden" << endl;
				continue;
			}

			cout << out;
			cout << path[path.size() - 1].to() << endl;
			cout << "Kosten: " << kosten << endl;
		}
		else if (input == "7") {
			PrintGrapf(gra);
		}
		else if (input == "8") {
			break;
		}
	}
}

int main() {
	// Starte Unit-Tests
	Catch::Session().run();


	//------------------------------------------------------------------------
	// 1. Ausgabe eines Graphen als Adjazenzliste implementieren
	//------------------------------------------------------------------------

	/*EdgeWeightedGraph G1("graph1.txt");

	PrintGrapf(G1);
	*/
	//------------------------------------------------------------------------
	// 2. Suche in Graphen
	//------------------------------------------------------------------------
	// Verwenden Sie hierfür die Vorlagen in Graphsearch.h
	//
	// Beispielaufruf der Tiefensuche: 
	// vector<bool> marked;
	// vector<int>  edgeTo;
	// bool connected = Graphsearch::DFS(G1, start, marked, edgeTo);

	/*vector<bool> marked;
	vector<int> edgeTo;
	int start = 0;
	bool connected = Graphsearch::DFS(G1, start, marked, edgeTo);*/

	//------------------------------------------------------------------------
	// 3. Minimaler Spannbaum mit Prim und Kruskal
	//------------------------------------------------------------------------
	// Vorlage für Prim ist die Klasse PrimMST (PrimMST.h + PrimMST.cpp)
	// Vorlage für Kruskal ist die Klasse KruskalMST (KruskalMST.h + KruskalMST.cpp)
	//
	// Beispielaufruf von Prim:
	// PrimMST prim(G, 0);

	/*PrimMST prim(G1, 0);*/

	//------------------------------------------------------------------------
	// 4. Kuerzeste Wege mit Dijkstra
	//------------------------------------------------------------------------
	// Beispielaufruf von Dijkstra
	//
	// EdgeWeightedDigraph G1_directed("graph1.txt");
	// Dijkstra dijkstra(G1_directed, start);
	// path = dijkstra.pathTo(target);



	//------------------------------------------------------------------------
	// 5. Menü für Benutzereingaben
	//------------------------------------------------------------------------
	// Alle Funktionalitäten aus der Aufgabenstellung muessen umgesetzt werden


	main_menu();



	return 0;
}