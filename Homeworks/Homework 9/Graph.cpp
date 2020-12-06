#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <list>
#include <climits>
using namespace std;

int findVertex(string start, vector<vertex*> vertices){
    for(int i = 0; i < vertices.size(); i++)
        if(vertices[i]->name == start)
            return i;
    return -1;
}

void Graph::createEdge(string v1, string v2, int num){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == v2 && i != j){
                    adjVertex av;
                    av.weight = num;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);

                    adjVertex av2;
                    av2.v = vertices[i];
                    av2.weight = num;
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::insertVertex(string n){
    if(findVertex(n, vertices) == -1){
        vertex *node;
        node->name = n;
        vertices.push_back(node);
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    // cout<<"here"<<vertices.size()<<endl;
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<endl;
        for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
            cout<<" --> "<< vertices[i]->adj[j].v->name << " "<<vertices[i]->adj[j].weight<<endl;
        }
        cout<<endl;
    }
}

struct compareWeight{
    bool operator()(const vertex *v1, const vertex *v2){
        return v1->distance > v2->distance;
    }
};

void Graph::traverseWithDijkstra(string start){
    priority_queue<vertex*, vector<vertex*>, compareWeight> unsolved; //creat a priortiy queue sorted by the distance to the starting node
    for(int i = 0; i < vertices.size(); i++){ //initialize some stuff
        vertices[i]->distance = INT_MAX - 100;
        unsolved.push(vertices[i]);
    }
    vertex *vStart = vertices[findVertex(start, vertices)]; //find the starting vertex and set its starting distance to zero
    vStart->distance = 0;
    vertex *n;
    while (!unsolved.empty()){ //while there are still nodes that are not solved, do this
        n = unsolved.top(); 
        unsolved.pop(); //get min distance node
        for(int i = 0; i < n->adj.size(); i++){ //operate on the min nodes adjacents
            if(n->distance + n->adj[i].weight < n->adj[i].v->distance){ //if the current distance of the adjacent is larger than the current distance + weight
                n->adj[i].v->distance = n->distance + n->adj[i].weight;
                unsolved.push(n->adj[i].v); //put it back on the p queue to check if adj distances need to be updated again. 
            }
        }    
    }
}

void depthFirstTraversalHelper(vertex *vStart){
    if(!vStart->visited){
        vStart->visited = true;
        cout << vStart->name << " -> ";
        for(int i = 0; i < vStart->adj.size(); i++)
            depthFirstTraversalHelper(vStart->adj[i].v);
    }
}

void Graph::depthFirstTraversal(string sourceVertex){
    vertex *vStart;
    for(int i = 0; i < vertices.size(); i++)
        if(vertices[i]->name == sourceVertex)
            vStart = vertices[i];
    cout << vStart->name << " -> ";
    vStart->visited = true;
    depthFirstTraversalHelper(vStart->adj[0].v);
    cout << "DONE" << endl;
}

void Graph::minDistPath(string source, string destination) {
    vector<vertex*> solved;
    vector<vertex*> finalPath;
    vertex* destPtr;
    int minDistance = INT_MAX;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i]->visited = false;
        vertices[i]->pred = NULL;
        vertices[i]->distance = INT_MAX;
        if(vertices[i]->name == source){
            vertices[i]->visited = true;
            vertices[i]->distance = 0;
            solved.push_back(vertices[i]);
        }
        if(vertices[i]->name == destination){
            destPtr = vertices[i];
        }
    }
    vertex* minV;
    vertex* minU;
    while(destPtr->visited == false){
        minDistance = INT_MAX;
        for(int i = 0; i < solved.size(); i++){
            vertex* ptrU = solved[i];
            for(int j = 0; j < ptrU->adj.size(); j++){
                vertex* ptrV = ptrU->adj[j].v;              
                if(ptrV->visited == false){
                    ptrV->distance = ptrU->distance + ptrU->adj[j].weight; 
                    if(minDistance > ptrV->distance){
                        minDistance = ptrV->distance;
                        minV = ptrV;                    
                        minU = ptrU;
                    }
                }
            }
        }
        solved.push_back(minV);
        minV->distance = minDistance;
        minV->pred = minU;
        minV->visited = true;
    }
    finalPath.push_back(minV);
    while(minV->pred != NULL){
        minV = minV->pred;
        finalPath.push_back(minV);
    }
    while(!finalPath.empty()){
        cout << finalPath.back()->name << " -> ";
        finalPath.pop_back();
    }
    cout <<"DONE [" << minDistance << "]" << endl;
}
