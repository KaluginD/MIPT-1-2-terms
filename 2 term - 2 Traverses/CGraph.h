#pragma once

#include <vector>

class  CGraph {
public:
	class  Edge;
	class Vertex {
	public:
		Vertex( int newNumber ) {
			Number = newNumber;
			Value = defValue;
		}
		Vertex( int newNumber, int newValue ) {
			Number = newNumber;
			Value = newValue;
		}
		~Vertex() {}
		int Number;
		int Value;
		std::vector< Edge* > Neighbours;
	};
	class Edge {
	public:
		Edge( Vertex* newFrom, Vertex* newTo, int newWeight ) {
			From = newFrom;
			To = newTo;
			weight = newWeight;
		}
		Edge( Vertex* newFrom, Vertex* newTo ) {
			Edge( newFrom, newTo, defWeight );
		}
		~Edge() {}
		Vertex* From;
		Vertex* To;
		int weight;
	};
	CGraph();
	~CGraph();

	void AddVertex( Vertex* newVertex );
	void AddEdge( Edge* newEdge );
	int GetSize() const;
	Vertex* getVertex( int i ) const;
private:
	std::vector< Vertex* > Graph;
	static int defValue;
	static int defWeight;
};