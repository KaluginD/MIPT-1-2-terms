#pragma once
#include "CStack.h"

class CDeque {
public:
	CDeque() {}
	~CDeque() {}
	void push_back( int element );
	void push_front( int element );
	int pop_back();
	int pop_front();
	bool IsEmpty() const { return stackLeft.IsEmpty() && stackRight.IsEmpty(); }
private:
	CStack stackLeft;
	CStack stackRight; 
	void rightToLeft();
	void leftToRight();
};