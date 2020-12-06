#include <stdio.h>
#include <iostream>
#include <vector>
#include "graph.h"
using namespace std;


int main() {




		Graph g1;
		g1.insertVertex(10);
		g1.insertVertex(12);
		g1.insertVertex(13);
		g1.insertEdge(10, 12);
		g1.insertEdge(10, 13);
		g1.insertEdge(13, 10);

		if(g1.detectCycle(10))
			cout<< "Test Case1 Passed\n";
		else
			cout<<"Test Case1 Failed\n";


		

	return 0;
}
