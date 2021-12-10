//
// Created by Cally on 12/7/2021.
//

#ifndef COP3530_FINAL_NODE_H
#define COP3530_FINAL_NODE_H

#include <string>
#include <cmath>

using namespace std;

struct Node {
    int index;
    float energy;
    float live;
    float dance;
    float acoustic;
    float loud;
    float instrumentals;
    float key;
    float valence;
    float tempo;
    float speech;
    float mode;
    string author;
    string name;
    float sum;

    Node();
    Node(int _ind, float _en, float _li, float _da, float _ac, float _lo, float _in, float _ke, float _va, float _te, float _sp, float _mo, string _au, string _na);

    float calcWeight(Node n);
};

Node::Node() {
    index = 0;
    energy = 0;
    live = 0;
    dance = 0;
    acoustic = 0;
    loud = 0;
    instrumentals = 0;
    key = 0;
    valence = 0;
    tempo = 0;
    speech = 0;
    mode = 0;
    author = "";
    name = "";
    sum = 0;
}

Node::Node(int _ind, float _en, float _li, float _da, float _ac, float _lo, float _in, float _ke, float _va, float _te, float _sp, float _mo,
           string _au, string _na) {
    index = _ind;
    energy = _en * 25;
    live = _li * 50;
    dance = _da*75;
    acoustic = _ac*25;
    loud = _lo + 60;
    instrumentals = _in*25;
    key = _ke;
    valence = _va*100;
    tempo = (_te-50)/2;
    speech = _sp*100;
    mode = _mo*25;

    for (int i = 0; i < _au.size(); i ++) {
        author.push_back(tolower(_au[i]));
    }

    for (int i = 0; i < _na.size(); i++) {
        name.push_back(tolower(_na[i]));
    }

    // need to come up with a way to ratio it all
    sum = energy + live + dance + acoustic + loud + instrumentals + key + valence + tempo + speech + mode;
}

float Node::calcWeight(Node n) {
    float weight = abs(this->sum - n.sum);
    if(this->author == n.author){
        weight -= 20;
    }
    return weight;
}

#endif //COP3530_FINAL_NODE_H
