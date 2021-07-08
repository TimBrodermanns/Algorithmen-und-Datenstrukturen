#include "KruskalMST.h"

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G        Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{


    treeID.resize(G.getV());
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    std::vector<Edge> e = G.edges(); // liefert alle Kanten von G
    for (int i = 0; i < e.size(); i++) pq.push(e[i]);
    // zu Beginn ist jeder Knoten ein eigener Baum
    for (int i = 0; i < G.getV(); i++) treeID[i] = i;

    while (!pq.empty()) {
        Edge e = pq.top();
        pq.pop();
        int v = e.either(); int w = e.other(v);
        // Wenn Knoten v und w zu unterschiedlichen Bäumen gehört,
        // können diese mit der Kante e ohne Zykel verbunden werden
        if (treeID[v] != treeID[w]) {
            mst.push_back(e);
            int treeID_w = treeID[w];
            for (int i = 0; i < G.getV(); i++) { // BaumID von v und w
                if (treeID[i] == treeID_w) // angleichen
                    treeID[i] = treeID[v];
            }
        }
    }
    /*
     * TODO
     */
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> KruskalMST::edges() const
{
    /*
     * TODO
     */
    return this->mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
    /*
     * TODO
     */

    double gew = 0.0;
    for (Edge e : this->mst) {

        gew += e.weight();
    }
    return gew;
}