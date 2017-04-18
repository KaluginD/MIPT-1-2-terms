#include "Tester.h"

#include <random>

Tester::Tester( int vertexNumber ) {
	Graph = CreateGraph( vertexNumber );
};

Tester::~Tester(){
};

CGraph* Tester::CreateGraph( int vertexNumber ) {
	CGraph* Graph;
	for( int i = 0; i < vertexNumber; ++i ) {
		CGraph::Vertex* newVertex = new CGraph::Vertex( i );
		int edgeNumber = i;
		if( i > 1 ) edgeNumber = 1 + std::rand() % (i - 1); 
		for( int j = 0; j < edgeNumber; ++j ) {
			int vertexToNumber = 1; 

		}
	}
	return Graph;
};

bool Tester::Testing() {
	return true;
};
