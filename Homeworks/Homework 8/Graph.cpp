#include "Graph.hpp"
#include <list>
#include <queue>

using namespace std;


void Graph::addEdge(string v1, string v2){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == v2 && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }
}

void Graph::addVertex(string name){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == name){
            found = true;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->name = name;
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i]->name;
        cout << " --> ";
        for(int j = 0; j < vertices[i]->adj.size(); j++)
            cout << vertices[i]->adj[j].v->name << " ";
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vertex *vStart = NULL;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == sourceVertex)
            vStart = vertices[i];
        vertices[i]->visited = false;
    }
    queue<vertex*> myQueue;
    myQueue.push(vStart);
    vStart->visited = true;
    vertex* s;
    cout << "Starting vertex (root): " << vStart->name << "-> ";
    while(!myQueue.empty()){
        s = myQueue.front();
        myQueue.pop();      
        for(int i = 0; i < s->adj.size(); i++ ){
            if(!s->adj[i].v->visited){ 
                s->adj[i].v->visited = true;
                s->adj[i].v->distance = s->distance + 1;
                cout << s->adj[i].v->name << "(" << s->adj[i].v->distance << ") ";
                myQueue.push(s->adj[i].v);
            }
        }
    }
}

void depthFirstSearch(vertex *vSource){
    if(!vSource->visited){
        vSource->visited = true;
        for(int i = 0; i < vSource->adj.size(); i++)
            depthFirstSearch(vSource->adj[i].v);
    }
}

int Graph::getConnectedBuildings(){
    int count = 0;
    for(int i = 0; i < vertices.size(); i++)
        vertices[i]->visited = false;
    for(int i = 0; i < vertices.size(); i++)
        if(!vertices[i]->visited){
            depthFirstSearch(vertices[i]);
            count++;
        }
    return count;
}