#pragma once

#include "CGraph.h"

class Traverse {
public:
	virtual ~Traverse() {};
	enum Color { 
		WHITE,
		GREY,
		BLACK
	};
	virtual void TraverseGraph( const CGraph& Graph ) = 0;
};