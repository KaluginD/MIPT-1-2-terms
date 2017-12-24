#include "CBfs.h"

#include <queue>

CBfs::CBfs() {
};

CBfs::~CBfs() {
};

void CBfs::Traverse( const CGraph* Graph ) {
	std::queue< CGraph::Vertex* > queue;
	queue.push( Graph->getVertex( 0 ) );
	while( !queue.empty() ) {
		CGraph::Vertex* vertex = queue.front();
		queue.pop();
		Vertices[vertex->Number] = BLACK;
		for(int i = 0; i < vertex->Neighbours.size(); ++i ) 
			if( Vertices[vertex->Neighbours[i]->To->Number] == WHITE ) {
				Vertices[vertex->Neighbours[i]->To->Number] = GREY;
				queue.push( vertex->Neighbours[i]->To );
			}
	}
};

bool CBfs::CheckCorrect() {
	for( int i = 0; i < Vertices.size(); ++i )
		if( Vertices[i] != BLACK )
			return false;
	return true;
};