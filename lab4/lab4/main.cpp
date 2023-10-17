#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>

#define INF (unsigned int)-1

using namespace std;

struct cost_path
{
    unsigned int cost;
    string path;
};

int main()
{
    unordered_map<string, unordered_map<string,unsigned int>>network;
    unordered_map<string, cost_path>vertecesCosts;
    unordered_set<string>vertecesVisited;
    list<string>path;
    network["A"] = {{"F",2},{"C",3}};
    network["B"] = {{"G",2},{"D",1},{"E",2},{"F",6}};
    network["C"] = {{"A",3},{"F",2},{"E",1},{"D",4}};
    network["D"] = {{"C",4},{"B",1}};
    network["E"] = {{"C",1},{"F",3},{"B",2}};
    network["F"] = {{"A",2},{"C",2},{"E",3},{"B",6},{"G",5}};
    network["G"] = {{"E",5},{"B",2}};
    string actualVertex = "A";
    // se itera por los nodos de la red y acada vertice le asigna un costo infinito para llegar
    for (const auto &node: network)
    {
        string vertex = node.first;
        vertecesCosts[vertex] = {INF,""};
    }
    // le asigna 0 para llegar al vertice inicial, lo agrega a los vertices visitados y lo añade al camino tomado
    vertecesCosts[actualVertex] = {0,actualVertex};
    // mientras no se haya visitado a todos los vertices
   while (vertecesVisited.size() != network.size())
    {
        vertecesVisited.insert(actualVertex);
        path.push_back(actualVertex);
        // estos son los valores del nodo al que nos vamos a mover
        unsigned int minEdge = INF; // guarda el costo de la arista de menor costo
        string minVertex = actualVertex; // guarda el vertice al cual conecta minEdge
        // itera por los nodos con los que tiene conexion el vertice actual
        for(const auto &adjacentNode: network[actualVertex])
        {
            string adjacentVertex = adjacentNode.first; // el primer elemento del nodo es su vertice
            unsigned int adjacentEdge = adjacentNode.second; // el segundo elemento del nodo es el costo de su arista
            // si por el camino actual el costo es menor que por el camino calculado anteriormente, lo intercambia por el costo camino actual
            if ((vertecesCosts[actualVertex].cost+adjacentEdge) < vertecesCosts[adjacentVertex].cost)
            {
                vertecesCosts[adjacentVertex].cost = vertecesCosts[actualVertex].cost+adjacentEdge;
                vertecesCosts[adjacentVertex].path = vertecesCosts[actualVertex].path + "->" + adjacentVertex;
            }
            // actualiza el valor de minEdge y minVertex siempre y cuando no se haya visitado ese vertice
            if ((adjacentEdge < minEdge) && (vertecesVisited.count(adjacentVertex) == 0))
            {
                minEdge = adjacentEdge;
                minVertex = adjacentVertex;
            }
        }
        // si no me pude mover de vertice es porque todos los vetices adjacentes han sido visitados, por lo tanto me devuelvo al vertice anterior
        if ((minVertex == actualVertex) && (vertecesVisited.size() != network.size()))
        {
            path.pop_back();
            minVertex = path.back();
            path.pop_back();
        }
        actualVertex = minVertex;
    }
    cout << "Finished" << endl;
    return 0;
}

