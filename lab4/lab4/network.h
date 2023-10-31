#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <iostream>
#include <fstream>
#include <set>

#include "router.h"

using namespace std;

class Network
{
private:
    unordered_map<string, Router*> network;

public:
    Network();
    Network(string path);
    void updateRouter(string actualVertex);
    void updateRouters();

    void addRouter(string name);
    void removeRouter(const string &name);
    void addEdge(string name1, string name2, unsigned int cost);
    void removeEdge(string name1, string name2);
    void loadNetwork(string path);
    cost_path pathBetweenRouters(string a, string b);
    void generateNetwork();
    void displayNetwork();
    void loadExampe();
    ~Network();
};

#endif // NETWORK_H
