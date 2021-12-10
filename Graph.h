//
// Created by Cally on 12/3/2021.
//

#ifndef COP3530_FINAL_GRAPH_H
#define COP3530_FINAL_GRAPH_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include <map>
#include <utility>
#include <algorithm>
#include <queue>
#include "Node.h"

using namespace std;

class Graph {
public:

    int vertices;
    map<int, vector<pair<Node, int>>> adjList;
    map<string, Node> nMap;

    Graph();

    bool insertEdge(Node from, Node to, int weight);
    int getWeight(Node from, Node to);
    void insertTo(Node node);

};

Graph::Graph() {
    vertices = 0;
}

bool Graph::insertEdge(Node from, Node to, int weight)
{
    if (adjList.find(from.index) == adjList.end()) {
        vector<pair<Node, int>> v;
        adjList.insert(make_pair(from.index, v));
    }
    if (adjList.find(to.index) == adjList.end()) {
        vector<pair<Node, int>> v;
        adjList.insert(make_pair(to.index, v));
    }

    // Add the nodes to the node map if they do not exist in there
    if (nMap.find(from.name + from.author) == nMap.end()) {
        nMap.insert(make_pair(from.name + from.author, from));
    }
    if (nMap.find(to.name + to.author) == nMap.end()) {
        nMap.insert(make_pair(to.name + to.author, to));
    }

    // if each one has less than 20 connections, insert them to one another
    if (adjList[from.index].size() < 21 && adjList[to.index].size() < 51) {
        adjList[from.index].push_back(make_pair(to, weight));
        adjList[to.index].push_back(make_pair(from, weight));
        ++vertices;
        return true;
    }
    return false;
}


int Graph::getWeight(Node from, Node to)
{
    vector<pair<Node, int>>::iterator it;

    if (adjList.find(from.index) != adjList.end()) {
        for (it = adjList.at(from.index).begin(); it != adjList.at(from.index).end(); it++) {
            if ((*it).first.index == to.index) {
                return (*it).second;
            }
        }
    }
    return 0;
}

void Graph::insertTo(Node node){
    priority_queue<pair<float, string>, vector<pair<float,string>>, greater<pair<float, string>>> pq;
    map<string, Node>::iterator it;
    float weight;
    string strIn;

    for(it = nMap.begin(); it != nMap.end(); it++){
        weight = node.calcWeight(it->second);
        pq.push(make_pair(weight, it->first));
    }

    int count = 0;
    while(!pq.empty() && count < 25) {
        weight = pq.top().first;
        strIn = pq.top().second;
        if(insertEdge(node, nMap.at(strIn), weight)){
            count++;
        }
        pq.pop();
    }
}


#endif //COP3530_FINAL_GRAPH_H

