#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

int Graph::insertVertex(int k) {
	Vertex* newVertex = new Vertex;
	newVertex->key = k;
	vertices.push_back(newVertex);
	return 0;
}

int Graph::insertEdge(int start, int end) {
	adjVertex* newEdge = new adjVertex;
	for (unsigned int i=0; i<vertices.size(); i++) {
		if (vertices[i]->key == start) { // find start @ index 'i'
			for (unsigned int j=0; j<vertices.size(); j++) {
				if (vertices[j]->key == end) { // find end @ index 'j'
					newEdge->v = vertices[j];
					vertices[i]->adjList.push_back(*newEdge);
					return 0;
				}
			}
			cout << "End node not found :(\n";
			return -1;
		}
	}
	cout << "Start node not found :(\n";
	return -1;
	//newEdge->v = ??; // Vertex reference containing the 'end' value;
}

Vertex* Graph::search(int k) {
	for (unsigned int i=0; i<vertices.size(); i++) {
		if (vertices[i]->key == k) {
			//cout << "Found it!\n";
			return vertices[i];
		}
	}
	cout << "Didn't find the key :(\n";
	return NULL;
}


bool detectCycleHelper(int key, vector<Vertex*> verticies){
	
}

bool Graph::detectCycle(int k) {
	Vertex* startV = search(k);
	for(int i = 0; i < vertices.size(); i++)
		vertices[i]->visited = false;
	
	return false;
}
