#include "CDfs.h"

#include <stack>

CDfs::CDfs() {
};

CDfs::~CDfs() {
};

void CDfs::Traverse( const CGraph* Graph ) {
	std::stack< CGraph::Vertex* > stack;
	stack.push( Graph->getVertex( 0 ) );
	while( !stack.empty() ) {
		CGraph::Vertex* vertex = stack.top();
		stack.pop();
		Vertices[vertex->Number] = BLACK;
		for(int i = 0; i < vertex->Neighbours.size(); ++i ) 
			if( Vertices[vertex->Neighbours[i]->To->Number] == WHITE ) {
				Vertices[vertex->Neighbours[i]->To->Number] = GREY;
				stack.push( vertex->Neighbours[i]->To );
			}
	}
};

bool CDfs::CheckCorrect() {
	for( int i = 0; i < Vertices.size(); ++i )
		if( Vertices[i] != BLACK )
			return false;
	return true;
};