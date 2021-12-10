#include <iostream>
#include <string>
#include<sstream>
#include<vector>
#include <map>
#include <utility>
#include <algorithm>
#include <queue>
#include <fstream>
#include <set>
#include <stack>
#include "Graph.h"
#include "Node.h"

using namespace std;

void menu(Node& song1, Node& song2, Graph& graph) {
    ifstream input;
    string songFrom, songTo, artFrom, artTo;
    string song1From, song1To, art1From, art1To;
    bool songFound = false;

    cin.get();
    while(!songFound) {
        songFrom = "";
        artFrom = "";
        cout << "Insert First Song Name:";

        getline(cin, song1From);
        cout << "Insert Name of the Artist:";
        getline(cin, art1From);

        for (int i = 0; i < song1From.size(); i++) {
            songFrom.push_back(tolower(song1From[i]));
        }
        for (int i = 0; i < art1From.size(); i++) {
            artFrom.push_back(tolower(art1From[i]));
        }

        if (graph.nMap.find(songFrom + artFrom) == graph.nMap.end()) {
            cout << "This song and artist is not in the program. Please use a different song." << endl;
        }
        else {
            song1.name = songFrom;
            song1.author = artFrom;
            songFound = true;
        }
    }

    songFound = false;
    while (!songFound) {
        songTo = "";
        artTo = "";

        cout << "Insert Second Song Name:";
        getline(cin, song1To);
        cout << "Insert the Second Artist Name:";
        getline(cin, art1To);

        for (int i = 0; i < song1To.size(); i++) {
            songTo.push_back(tolower(song1To[i]));
        }
        for (int i = 0; i < art1To.size(); i++) {
            artTo.push_back(tolower(art1To[i]));
        }

        if (graph.nMap.find(songTo + artTo) == graph.nMap.end()) {
            cout << "This song and artist is not in the program. Please use a different song." << endl;
        }
        else {
            song2.name = songTo;
            song2.author = artTo;
            if (song1.name == song2.name && song1.author==song2.author){
                cout<<"Song name and artist already chosen"<<endl;
                continue;
            }

            songFound= true;
        }
    }
}

void readData(Graph& g, string filePath) {

    ifstream file;
    string index;
    string energy;
    string live;
    string dance;
    string acoustic;
    string exp;
    string instrumentals;
    string key;
    string valence;
    string popularity;
    string tempo;
    string speech;
    string mode;
    string author;
    string name;
    string id;
    string loud;
    string notUsed;
    int i = 0;

    Node curr;
    file.open(filePath);

    if (file.is_open()) {
        getline(file, notUsed);
        file.get();

        while (!file.eof() && i < 200000) { 
            getline(file, id, ',');
            getline(file, name, ',');
            getline(file, notUsed, ',');
            getline(file, notUsed, ',');
            getline(file, author, ',');
            author = author.substr(2, author.length()-4);
            getline(file, notUsed, ',');
            getline(file, notUsed, ',');
            getline(file, notUsed, ',');
            getline(file, notUsed, ',');
            getline(file, dance, ',');
            getline(file, energy, ',');
            getline(file, key, ',');
            getline(file, loud, ',');
            getline(file, mode, ',');
            getline(file, speech, ',');
            getline(file, acoustic, ',');
            getline(file, instrumentals, ',');
            getline(file, live, ',');
            getline(file, valence, ',');
            getline(file, tempo, ',');
            getline(file, notUsed, ',');
            getline(file, notUsed, ',');
            getline(file, notUsed, ',');
            getline(file, notUsed);

            curr = Node(i, stof(energy), stof(live), stof(dance), stof(acoustic), stof(loud), stof(instrumentals), stof(key), stof(valence), stof(tempo), stof(speech),
                        stof(mode), author, name);

            if (i == 0) {
                g.nMap.insert(make_pair(curr.name + curr.author,curr));
            }
            else {
                g.insertTo(curr);
            }
            ++i;
        }
    }
}

/*takes in 2 vertices returns list of songs visited
 * source vertex: song 1
*/


vector<Node> dijkstra(const Graph& graph, Node& song1, Node& song2){
    vector<Node> songList;
    int vertices = graph.vertices;


    vector<int> distance(vertices, INT_MAX);
    vector<int> visited(vertices, 0);

    vector<string> prev(vertices);

    distance[song1.index] = 0;
    songList.push_back(song1);
    priority_queue<pair<int,string>,vector<pair<int,string>>, greater<pair<int, string>>> pq;
    pq.push(make_pair(0,song1.name+song1.author));
    while(!pq.empty())
    {
        pair<int,string> p = pq.top();
        pq.pop();
        string curr = p.second;
        int currInd = graph.nMap.at(curr).index;
        if(visited[currInd]==1)
            continue;
        visited[currInd]=1;
        vector<pair<Node, int>> vert = graph.adjList.at(currInd);
        for(int i=0; i<vert.size();i++)
        {
            Node dest = vert[i].first;
            int weight = vert[i].second;
            if(visited[dest.index]==1)
                continue;
            if(distance[dest.index] > distance[currInd] + weight)
            {

                distance[dest.index] = distance[currInd] + weight;
                pq.push(make_pair(distance[dest.index], dest.name+dest.author));
                prev[dest.index] = curr;

            }
        }
    }
    int counter=song2.index;
    vector<Node> back;
    Node node;
    back.push_back(song2);
    while(prev[counter]!=""){
        node = graph.nMap.at(prev[counter]);
        songList.push_back(node);
        counter = node.index;
    }
    return songList;
}

vector<Node> dfs(const Graph& graph, Node& src, Node& dest) {
    set<string> visited;
    stack<string> s;
    vector<Node> songList;

    string destIn = dest.name + dest.author;
    string strIn = src.name + src.author;

    visited.insert(strIn);
    s.push(strIn);

    while(!s.empty()){
        string curr = s.top();
        s.pop();
        songList.push_back(graph.nMap.at(curr));
        if(curr == destIn){
            return songList;
        }
        vector<pair<Node, int>> vect = graph.adjList.at(graph.nMap.at(curr).index);
        for(int i = 0; i < vect.size(); i++){
            strIn = vect[i].first.name + vect[i].first.author;
            if(visited.count(strIn) == 0){
                visited.insert(strIn);
                s.push(strIn);
            }
        }
    }
    return songList;
}

vector<Node> bfs(const Graph& graph, Node& src, Node& dest) {
    set<string> visited;
    queue<string> q;
    vector<Node> songList;

    string destIn = dest.name + dest.author;
    string strIn = src.name + src.author;

    visited.insert(strIn);
    q.push(strIn);

    while(!q.empty()){
        string curr = q.front();
        q.pop();
        songList.push_back(graph.nMap.at(curr));
        if(curr == destIn){
            return songList;
        }
        vector<pair<Node, int>> vect = graph.adjList.at(graph.nMap.at(curr).index);
        for(int i = 0; i < vect.size(); i++){
            strIn = vect[i].first.name + vect[i].first.author;
            if(visited.count(strIn) == 0){
                visited.insert(strIn);
                q.push(strIn);
            }
        }
    }
    return songList;
}

void printSongList(vector<Node> songList){
    string name, artist;
    cout << "-*-*-*-" <<endl;
    for(int i = 0; i < songList.size(); i++){
        name = songList[i].name;
        artist = songList[i].author;
        cout << i + 1 << ". "<< name << ", by: " << artist << endl;
    }
    cout << endl;
}


int main() {

    cout << "Welcome to the Playlist Randomizer!" << endl;
    cout << "By inputting the name and artist of two songs, I am able to produce a playlist.";
    cout << " If you chose to get a Dijkstra path between the songs, the playlist will include songs that are similar to the inputted songs.";
    cout << " However, if you chose to get a breadth first search or a depth first search between the songs, you will get randomized songs." << endl;
    cout<<"Loading Data... \n\n";

    Graph g;
    readData(g, "data.csv");

    int option=0;
    Node song1, song2;
    vector<Node> songList;
    song1.name="";
    song2.name="";

    do{
        //options:
        cout << "-*-*-*-" << endl;
        cout<<"Option 1: Dijkstra Search"<<endl;
        cout<<"Option 2: Breadth First Search"<<endl;
        cout<<"option 3: Depth First Search"<<endl;
        cout<<"Option 4: Exit Program" <<endl;
        cout << "-*-*-*-" << endl;
        cout<<"Enter option number"<<endl;

        option=0;
        cin>>option;
        switch (option) {
            case 1:
                menu(song1, song2, g);
                songList=dijkstra(g,song1,song2);
                printSongList(songList);
                break;
            case 2:
                menu(song1, song2, g);
                songList=bfs(g,song1,song2);
                printSongList(songList);
                break;
            case 3:
                menu(song1, song2, g);
                songList=dfs(g,song1,song2);
                printSongList(songList);
                break;
        }
    }while(option!=4);


    // Create Graph

    // Read + save data

    // Ask Input of Song 1
    // Ask input of Song 2

    // Make sure everything is lowercase

    // Ask which algorithm to use
    // Print



    return 0;
}


