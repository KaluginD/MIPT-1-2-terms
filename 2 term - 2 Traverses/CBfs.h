#pragma once

#include <vector>

#include "Traverse.h"

class CBfs : public Traverse {
public:
	CBfs();
	virtual ~CBfs();

	virtual void Traverse( const CGraph* Graph );
private:
	std::vector< Color > Vertices;
	bool CheckCorrect();
};