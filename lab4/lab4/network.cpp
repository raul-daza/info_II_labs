#include "network.h"

#define INF (unsigned int)-1

Network::Network()
{
    network = {};
}

Network::Network(string path)
{
    loadNetwork(path);
    updateRouters();
}

void Network::updateRouter(string currentVertex)
{
    string updatedVertex = currentVertex;
    unordered_map<string, cost_path>vertecesCosts;
    unordered_set<string>vertecesVisited;
    list<string>path;
    // se itera por los nodos de la red y acada vertice le asigna un costo infinito para llegar
    for (const auto &node: network)
    {
        string vertex = node.first;
        vertecesCosts[vertex] = {INF,""};
    }
    // le asigna 0 para llegar al vertice inicial, lo agrega a los vertices visitados y lo añade al camino tomado
    vertecesCosts[currentVertex] = {0,currentVertex};
    // mientras no se haya visitado a todos los vertices
    while (vertecesVisited.size() != network.size())
    {
        vertecesVisited.insert(currentVertex);
        path.push_back(currentVertex);
        // estos son los valores del nodo al que nos vamos a mover
        unsigned int minEdge = INF; // guarda el costo de la arista de menor costo
        string minVertex = currentVertex; // guarda el vertice al cual conecta minEdge
        // itera por los nodos con los que tiene conexion el vertice current
        for(const auto &adjacentNode: network[currentVertex]->getLocalVerteces())
        {
            string adjacentVertex = adjacentNode.first; // el primer elemento del nodo es su vertice
            unsigned int adjacentEdge = adjacentNode.second; // el segundo elemento del nodo es el costo de su arista
            // si por el camino current el costo es menor que por el camino calculado anteriormente, lo intercambia por el costo camino current
            if ((vertecesCosts[currentVertex].cost+adjacentEdge) < vertecesCosts[adjacentVertex].cost)
            {
                string newPath = vertecesCosts[currentVertex].path + "->" + adjacentVertex;
                unsigned int newCost = vertecesCosts[currentVertex].cost+adjacentEdge;
                for (auto &node: vertecesCosts)
                {
                    string vertex = node.first;
                    string path = node.second.path;
                    size_t pos = path.find(adjacentVertex);
                    if(vertex != currentVertex && pos != string::npos)
                    {
                        path = path.substr(pos+1);
                        node.second.path = newPath+path;
                        node.second.cost = node.second.cost - vertecesCosts[adjacentVertex].cost + newCost;
                    }
                }
                vertecesCosts[adjacentVertex].cost = newCost;
                vertecesCosts[adjacentVertex].path = newPath;
            }
            // currentiza el valor de minEdge y minVertex siempre y cuando no se haya visitado ese vertice
            if ((adjacentEdge < minEdge) && (vertecesVisited.count(adjacentVertex) == 0))
            {
                minEdge = adjacentEdge;
                minVertex = adjacentVertex;
            }
        }
        // si no me pude mover de vertice es porque todos los vetices adjacentes han sido visitados, por lo tanto me devuelvo al vertice anterior
        if ((minVertex == currentVertex) && (vertecesVisited.size() != network.size()))
        {
            path.pop_back();
            minVertex = path.back();
            path.pop_back();
        }
        currentVertex = minVertex;
    }
    network[updatedVertex]->setVertecesCosts(vertecesCosts);
}

void Network::updateRouters()
{
    for(const auto &routermap : network)
    {
        updateRouter(routermap.first);
    }
}

void Network::addRouter(string name)
{

    network[name] = new Router(name, {});
}

void Network::removeRouter(const string &name)
{
    delete network[name];
    network.erase(network.find(name));

    for (auto &router : network)
    {
        router.second->removeEdge(name);
    }
    updateRouters();
}
void Network::addEdge(string name1, string name2, unsigned int cost)
{
    network[name1]->addEdge(name2, cost);
    network[name2]->addEdge(name1, cost);
}

void Network::removeEdge(string name1, string name2)
{
    network[name1]->removeEdge(name2);
    network[name2]->removeEdge(name1);
}

cost_path Network::pathBetweenRouters(string a, string b)
{
    return network[a]->getVertecesCosts()[b];
}

void Network::displayNetwork()
{
    cout << "  ";
    for(const auto &routermap1 : network)
    {
        cout << routermap1.first << ' ';
    }
    cout << endl;
    for(const auto &routermap1 : network)
    {
        cout << routermap1.first << ' ';
        for(const auto &routermap2: network)
        {
            cout << network[routermap1.first]->getVertecesCosts()[routermap2.first].cost << ' ';
        }
        cout << endl;
    }
}

void Network::loadNetwork(string path)
{
    fstream file;
    file.open(path, ios::in);
    if (!file.is_open())
    {
        cout << "not opened" << endl;
    }
    string line, cost, currentVertex, vertex;
    size_t pos;
    unordered_map<string, unsigned int> localVerteces;
    list<string> names;
    list<string>::iterator it;
    getline(file, line);
    while (true)
    {
        pos = line.find(',');
        if(pos == string::npos)
        {
            break;
        }
        vertex = line.substr(0,pos);
        names.push_back(vertex);
        line.erase(0,pos+1);
    }
    names.push_back(line);
    it = names.begin();
    while(getline(file, line))
    {
        pos = line.find(':');
        currentVertex = line.substr(0,pos);
        line.erase(0,pos+1);
        while (true)
        {
            pos = line.find(',');
            if(pos == string::npos)
            {
                break;
            }
            cost = line.substr(0,pos);
            line.erase(0,pos+1);
            if (cost == "0" || cost == "INF")
            {
                it++;
                continue;

            }

            localVerteces[*it] = stoul(cost);
            it++;
        }
        if (line != "INF" && line != "0")
        {
            localVerteces[*it] = stoul(line);
        }
        it = names.begin();
        network[currentVertex] = new Router(currentVertex, localVerteces);
        localVerteces = {};
    }
}

Network::~Network()
{
    for (auto &Node: network)
    {
        delete Node.second;
    }
}
