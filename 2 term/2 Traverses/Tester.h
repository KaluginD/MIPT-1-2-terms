#pragma once


#include "CBfs.h"
#include "CDfs.H"
#include "Traverse.h"

class Tester {
public:
	Tester( int vertexNumber );
	~Tester();

private:
	CGraph* Graph;
	CGraph* CreateGraph( int vertexNumber );
	bool Testing();
};