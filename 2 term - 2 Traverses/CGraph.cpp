#include "CGraph.h"

CGraph::CGraph() {
};

CGraph::~CGraph() {
};

void CGraph::AddVertex( Vertex* newVertex ) {
	Graph.push_back( newVertex );
};

void CGraph::AddEdge( Edge* newEdge ) {
	Graph[newEdge->From->Number]->Neighbours.push_back( newEdge );
	Graph[newEdge->To->Number]->Neighbours.push_back( new Edge( newEdge->To, newEdge->From, newEdge->weight ) );
};

int CGraph::GetSize() const {
	return Graph.size();
};

CGraph::Vertex* CGraph::getVertex( int i ) const {
	return Graph[i];
};

int CGraph::defWeight = 1;

int CGraph::defValue = 1;
