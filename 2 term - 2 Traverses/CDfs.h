#pragma once

#include <vector>

#include "Traverse.h"

class CDfs : public Traverse {
public:
	CDfs();
	virtual ~CDfs();

	virtual void Traverse( const CGraph* Graph );
private:
	std::vector< Color > Vertices;
	bool CheckCorrect();
};