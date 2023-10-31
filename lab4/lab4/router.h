#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct cost_path
{
    unsigned int cost;
    string path;
};

class Router
{
private:
    string name;
    unordered_map<string, cost_path> vertecesCosts;
    unordered_map<string, unsigned int> localVerteces;

public:
    Router();
    Router(string name, unordered_map<string, unsigned int> localVerteces);
    void addEdge(string name2, unsigned int cost);
    void removeEdge(string name2);

    string getName() const;
    void setName(const string &newName);
    unordered_map<string, cost_path> getVertecesCosts() const;
    void setVertecesCosts(const unordered_map<string, cost_path> &newVertecesCosts);
    unordered_map<string, unsigned int> getLocalVerteces() const;
    void setLocalVerteces(const unordered_map<string, unsigned int> &newLocalVerteces);
};

#endif // ROUTER_H
