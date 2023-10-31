#include "router.h"

Router::Router()
{
    name = "";
    localVerteces = {};
}

Router::Router(string name, unordered_map<string, unsigned int> localVerteces)
{
    this->name = name;
    this->localVerteces = localVerteces;
}

void Router::addEdge(string name2, unsigned int cost)
{
    localVerteces[name2] = cost;
}

void Router::removeEdge(string name2)
{
    localVerteces.erase(name2);
}

string Router::getName() const
{
    return name;
}

void Router::setName(const string &newName)
{
    name = newName;
}

unordered_map<string, cost_path> Router::getVertecesCosts() const
{
    return vertecesCosts;
}

void Router::setVertecesCosts(const unordered_map<string, cost_path> &newVertecesCosts)
{
    vertecesCosts = newVertecesCosts;
}

unordered_map<string, unsigned int> Router::getLocalVerteces() const
{
    return localVerteces;
}

void Router::setLocalVerteces(const unordered_map<string, unsigned int> &newLocalVerteces)
{
    localVerteces = newLocalVerteces;
}
