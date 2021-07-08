/*************************************************
* ADS Praktikum 5
* Unit-Testdatei
* Stand: 01.06.2021
*
*************************************************
* Änderungen untersagt!
*************************************************/
#include "catch.h"
#include <string>
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDigraph.h"
#include "DijkstraSP.h"
#include "KruskalMST.h"
#include "PrimMST.h"

namespace Graphsearch {
	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo);
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo);
}

/***********************************************
 * Testroutine des Graphen:
	- Adjazenzlisten
	- Tiefensuche mit zusammenhängenden Graphen
	- Tiefensuche mit nicht zusammenhängenden Graphen
	- Breitensuche mit zusammenhängenden Graphen
	- Breitensuche mit nicht zusammenhängenden Graphen
	- Prim mit bestimmten Ergebnissen
	- Kruskal mit bestimmten Ergebnissen
	- Dijkstra
 */
TEST_CASE("Graph Test: Adjazenzliste") {
	EdgeWeightedGraph G1("graph1.txt");
	EdgeWeightedGraph G2("graph2.txt");
	EdgeWeightedGraph G3("graph3.txt");

	SECTION("Adjazenzliste des ersten Graphen (graph1.txt)") {
		REQUIRE(G1.getV() == 7);
		REQUIRE(G1.getE() == 11);

		auto adj = G1.getAdj();
		REQUIRE(adj[0][0].either() == 0);
		REQUIRE(adj[0][0].other(0) == 1);
		REQUIRE(adj[0][0].weight() == 7.0);

		REQUIRE(adj[4][3].either() == 4);
		REQUIRE(adj[4][3].other(4) == 5);
		REQUIRE(adj[4][3].weight() == 8.0);
	}

	SECTION("Adjazenzliste des zweiten Graphen (graph2.txt)") {
		REQUIRE(G2.getV() == 20);
		REQUIRE(G2.getE() == 60);

		auto adj = G2.getAdj();
		REQUIRE(adj[0][0].either() == 0);
		REQUIRE(adj[0][0].other(0) == 1);
		REQUIRE(adj[0][0].weight() == 6.0);

		REQUIRE(adj[13][5].either() == 13);
		REQUIRE(adj[13][5].other(13) == 19);
		REQUIRE(adj[13][5].weight() == 25.0);
	}

	SECTION("Adjazenzliste des dritten Graphen (graph3.txt)") {
		REQUIRE(G2.getV() == 20);
		REQUIRE(G2.getE() == 60);

		auto adj = G2.getAdj();
		REQUIRE(adj[0][0].either() == 0);
		REQUIRE(adj[0][0].other(0) == 1);
		REQUIRE(adj[0][0].weight() == 6.0);

		REQUIRE(adj[13][5].either() == 13);
		REQUIRE(adj[13][5].other(13) == 19);
		REQUIRE(adj[13][5].weight() == 25.0);
	}
}

TEST_CASE("Graph Test: Tiefensuche (DFS)") {

	EdgeWeightedGraph G1("graph1.txt");
	EdgeWeightedGraph G2("graph2.txt");
	EdgeWeightedGraph G3("graph3.txt");

	std::vector<bool> marked;
	std::vector<int>  edgeTo;

	SECTION("Tiefensuche mit erstem Graphen (graph1.txt") {
		marked.resize(42, false);	// Dummy values, damit die unit-Tests mit 
		edgeTo.resize(42, -1);		// der Vorlage durchlaufen ohne Programmabsturz

		for (int i = 0; i < G1.getV(); i++) {
			bool connected = Graphsearch::DFS(G1, i, marked, edgeTo);
			REQUIRE(connected == true);
		}

		// edgeTo-Array der Tiefensuche mit Startknoten 0 testen 
		Graphsearch::DFS(G1, 0, marked, edgeTo);
		REQUIRE(edgeTo[0] == -1);
		REQUIRE(edgeTo[1] == 0);
		REQUIRE(edgeTo[2] == 1);
		REQUIRE(edgeTo[3] == 4);
		REQUIRE(edgeTo[4] == 2);
		REQUIRE(edgeTo[5] == 3);
		REQUIRE(edgeTo[6] == 5);
	}

	SECTION("Tiefensuche mit zweiten Graphen (graph2.txt)") {
		marked.resize(42, false);	// Dummy values, damit die unit-Tests mit 
		edgeTo.resize(42, -1);		// der Vorlage durchlaufen ohne Programmabsturz

		for (int i = 0; i < G2.getV(); i++) {
			bool connected = Graphsearch::DFS(G2, i, marked, edgeTo);
			REQUIRE(connected == true);
		}

		Graphsearch::DFS(G2, 0, marked, edgeTo);
		REQUIRE(edgeTo[0] == -1);
		REQUIRE(edgeTo[1] == 0);
		REQUIRE(edgeTo[7] == 4);
		REQUIRE(edgeTo[8] == 9);
		REQUIRE(edgeTo[19] == 13);
	}

	SECTION("Tiefensuche mit dritten Graphen (graph3.txt)") {
		marked.resize(42, false);	// Dummy values, damit die unit-Tests mit 
		edgeTo.resize(42, -1);		// der Vorlage durchlaufen ohne Programmabsturz

		for (int i = 0; i < G3.getV(); i++) {
			bool connected = Graphsearch::DFS(G3, i, marked, edgeTo);
			REQUIRE(connected == false);
		}

		Graphsearch::DFS(G3, 0, marked, edgeTo);
		REQUIRE(marked[0] == true);
		REQUIRE(marked[4] == true);
		REQUIRE(marked[18] == true);

		Graphsearch::DFS(G3, 1, marked, edgeTo);
		REQUIRE(marked[0] == false);
		REQUIRE(marked[4] == false);
		REQUIRE(marked[18] == false);
	}
}

TEST_CASE("Graph Test: Breitensuche (BFS)") {

	EdgeWeightedGraph G1("graph1.txt");
	EdgeWeightedGraph G2("graph2.txt");
	EdgeWeightedGraph G3("graph3.txt");

	std::vector<bool> marked;
	std::vector<int>  edgeTo;

	SECTION("Breitensuche mit erstem Graphen (graph1.txt") {
		marked.resize(42, false);	// Dummy values, damit die unit-Tests mit 
		edgeTo.resize(42, -1);		// der Vorlage durchlaufen ohne Programmabsturz

		for (int i = 0; i < G1.getV(); i++) {
			bool connected = Graphsearch::BFS(G1, i, marked, edgeTo);
			REQUIRE(connected == true);
		}

		// edgeTo-Array der Breitensuche mit Startknoten 0 testen 
		Graphsearch::BFS(G1, 0, marked, edgeTo);
		REQUIRE(edgeTo[0] == -1);
		REQUIRE(edgeTo[1] == 0);
		REQUIRE(edgeTo[2] == 1);
		REQUIRE(edgeTo[3] == 1);
		REQUIRE(edgeTo[4] == 2);
		REQUIRE(edgeTo[5] == 4);
		REQUIRE(edgeTo[6] == 5);
	}

	SECTION("Breitensuche mit zweiten Graphen (graph2.txt)") {
		marked.resize(42, false);	// Dummy values, damit die unit-Tests mit 
		edgeTo.resize(42, -1);		// der Vorlage durchlaufen ohne Programmabsturz

		for (int i = 0; i < G2.getV(); i++) {
			bool connected = Graphsearch::BFS(G2, i, marked, edgeTo);
			REQUIRE(connected == true);
		}

		// edgeTo-Array der Breitensuche mit Startknoten 0 testen 
		Graphsearch::BFS(G2, 0, marked, edgeTo);
		REQUIRE(edgeTo[0] == -1);
		REQUIRE(edgeTo[1] == 0);
		REQUIRE(edgeTo[2] == 17);
		REQUIRE(edgeTo[6] == 9);
		REQUIRE(edgeTo[11] == 5);
		REQUIRE(edgeTo[15] == 10);
		REQUIRE(edgeTo[19] == 0);
	}

	SECTION("Breitensuche mit dritten Graphen (graph3.txt)") {
		marked.resize(42, false);	// Dummy values, damit die unit-Tests mit 
		edgeTo.resize(42, -1);		// der Vorlage durchlaufen ohne Programmabsturz

		for (int i = 0; i < G3.getV(); i++) {
			bool connected = Graphsearch::BFS(G3, i, marked, edgeTo);
			REQUIRE(connected == false);

			// Hinweis: Die Knoten {0,4,18} bilden einen Teilgraphen
			if (i == 0 || i == 4 || i == 18) {
				REQUIRE(marked[0] == true);
				REQUIRE(marked[4] == true);
				REQUIRE(marked[18] == true);
			}
			else {
				REQUIRE(marked[0] == false);
				REQUIRE(marked[4] == false);
				REQUIRE(marked[18] == false);
			}
		}
	}
}

TEST_CASE("Graph Test: Prim") {
	EdgeWeightedGraph G1("graph1.txt");
	EdgeWeightedGraph G2("graph2.txt");
	EdgeWeightedGraph G3("graph3.txt");

	SECTION("Prim mit erstem Graph (graph1.txt)") {
		for (int i = 0; i < G1.getV(); i++) {
			PrimMST prim(G1, i);
			REQUIRE(prim.weight() == 39.0);

			auto edges = prim.edges();
			REQUIRE(edges.size() == 6);
			std::vector<Edge> mst;
			mst.push_back(Edge(0, 3, 5.0));
			mst.push_back(Edge(2, 4, 5.0));
			mst.push_back(Edge(3, 5, 6.0));
			mst.push_back(Edge(1, 4, 7.0));
			mst.push_back(Edge(0, 1, 7.0));
			mst.push_back(Edge(4, 6, 9.0));

			// Testen ob alle Edes des MST exitieren
			for (auto const& e : edges) {
				REQUIRE(std::find(mst.begin(), mst.end(), e) != mst.end());
			}
		}
	}

	SECTION("Prim mit zweitem Graph (graph2.txt)") {
		for (int i = 0; i < G2.getV(); i++) {
			PrimMST prim(G2, i);
			REQUIRE(prim.weight() == 150.0);
			auto edges = prim.edges();
			REQUIRE(edges.size() == 19);
		}
	}

	SECTION("Prim mit drittem Graphen (graph3.txt)") {
		// Graph 3 mit Strartknoten 0
		PrimMST prim_0(G3, 0);
		REQUIRE(prim_0.weight() == 16.0);
		// Graph 3 mit Strartknoten 16
		PrimMST prim_16(G3, 16);
		REQUIRE(prim_16.weight() == 168.0);
	}
}

TEST_CASE("Graph Test: Kruskal") {
	EdgeWeightedGraph G1("graph1.txt");
	EdgeWeightedGraph G2("graph2.txt");
	EdgeWeightedGraph G3("graph3.txt");

	SECTION("Kruskal mit erstem Graph (graph1.txt)") {
		KruskalMST kruskal(G1);
		REQUIRE(kruskal.weight() == 39.0);

		auto edges = kruskal.edges();
		REQUIRE(edges.size() == 6);
		std::vector<Edge> mst;
		mst.push_back(Edge(0, 3, 5.0));
		mst.push_back(Edge(2, 4, 5.0));
		mst.push_back(Edge(3, 5, 6.0));
		mst.push_back(Edge(1, 4, 7.0));
		mst.push_back(Edge(0, 1, 7.0));
		mst.push_back(Edge(4, 6, 9.0));

		// Testen ob alle Edes des MST exitieren
		for (auto const& e : edges) {
			REQUIRE(std::find(mst.begin(), mst.end(), e) != mst.end());
		}
	}

	SECTION("Kruskal mit zweitem Graph (graph2.txt)") {
		KruskalMST kruskal(G2);
		REQUIRE(kruskal.weight() == 150.0);
		REQUIRE(kruskal.edges().size() == 19);
	}

	SECTION("Kruskal mit drittem Graph (graph3.txt)") {
		KruskalMST kruskal(G3);
		REQUIRE(kruskal.weight() == 184.0);
		REQUIRE(kruskal.edges().size() == 18);
	}
}

TEST_CASE("Graph Test: Dijkstra") {
	EdgeWeightedDigraph G1_directed("graph1.txt");
	EdgeWeightedDigraph G2_directed("graph2.txt");
	EdgeWeightedDigraph G3_directed("graph3.txt");

	int start, target;

	SECTION("Dijkstra beim ersten Graph - 0 nach 6 (graph1.txt)") {
		start = 0;
		target = 6;
		DijkstraSP dsp(G1_directed, start);
		auto path = dsp.pathTo(target);

		REQUIRE(dsp.distTo(target) == 22.0);
		REQUIRE(path.size() == 3);
		REQUIRE(path[0] == DirectedEdge(0, 3, 5.0));
		REQUIRE(path[1] == DirectedEdge(3, 5, 6.0));
		REQUIRE(path[2] == DirectedEdge(5, 6, 11.0));
	}

	SECTION("Dijkstra beim ersten Graph - 2 nach 6 (graph1.txt)") {
		start = 2;
		target = 6;
		DijkstraSP dsp(G1_directed, start);
		auto path = dsp.pathTo(target);

		REQUIRE(dsp.distTo(target) == 14.0);
		REQUIRE(path.size() == 2);
		REQUIRE(path[0] == DirectedEdge(2, 4, 5.0));
		REQUIRE(path[1] == DirectedEdge(4, 6, 9.0));
	}

	SECTION("Dijkstra beim zweiten Graph - 0 nach 6 (graph2.txt)") {
		start = 0;
		target = 6;
		DijkstraSP dsp(G2_directed, start);
		auto path = dsp.pathTo(target);

		REQUIRE(dsp.distTo(target) == 91.0);
		REQUIRE(path.size() == 3);
		REQUIRE(path[0] == DirectedEdge(0, 4, 47.0));
		REQUIRE(path[1] == DirectedEdge(4, 5, 36.0));
		REQUIRE(path[2] == DirectedEdge(5, 6, 8.0));
	}

	SECTION("Dijkstra beim zweiten Graph - 3 nach 9 (graph2.txt)") {
		start = 3;
		target = 9;
		DijkstraSP dsp(G2_directed, start);
		auto path = dsp.pathTo(target);

		REQUIRE(dsp.distTo(target) == 122.0);
		REQUIRE(path.size() == 4);
		REQUIRE(path[0] == DirectedEdge(3, 4, 46.0));
		REQUIRE(path[1] == DirectedEdge(4, 5, 36.0));
		REQUIRE(path[2] == DirectedEdge(5, 6, 8.0));
		REQUIRE(path[3] == DirectedEdge(6, 9, 32.0));
	}

	SECTION("Dijkstra beim dritten Graph - 0 nach 4 (graph3.txt)") {
		start = 0;
		target = 4;
		DijkstraSP dsp(G3_directed, start);
		auto path = dsp.pathTo(target);

		REQUIRE(dsp.distTo(target) == 47.0);
		REQUIRE(path.size() == 1);
		REQUIRE(path[0] == DirectedEdge(0, 4, 47.0));
	}

	SECTION("Dijkstra beim dritten Graph - 1 nach 16 (graph3.txt)") {
		start = 1;
		target = 16;
		DijkstraSP dsp(G3_directed, start);
		auto path = dsp.pathTo(target);

		REQUIRE(dsp.distTo(target) == 35.0);
		REQUIRE(path.size() == 2);
		REQUIRE(path[0] == DirectedEdge(1, 7, 9.0));
		REQUIRE(path[1] == DirectedEdge(7, 16, 26.0));
	}

	SECTION("Dijkstra beim dritten Graph - 3 nach 7 (graph3.txt)") {
		start = 3;
		target = 7;
		DijkstraSP dsp(G3_directed, start);
		auto path = dsp.pathTo(target);

		REQUIRE(dsp.distTo(target) == 42.0);
		REQUIRE(path.size() == 3);
		REQUIRE(path[0] == DirectedEdge(3, 5, 27.0));
		REQUIRE(path[1] == DirectedEdge(5, 6, 8.0));
		REQUIRE(path[2] == DirectedEdge(6, 7, 7.0));
	}
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// http://www.hashemall.com/
// Zeile 1 - 399 hat den SHA 256 Hashwert: 95E3A2710F2C1D7C484FCC4E05CAF45115810D9FA1715922C7AEAC13C08BF012
