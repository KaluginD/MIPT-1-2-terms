#pragma once
#include "CStack.h"

class CQueue {
public:
	CQueue() {}
	~CQueue() {}
	void Push( int element );
	int Pop();
	bool IsEmpty() const { return stackForPop.IsEmpty() && stackForPush.IsEmpty(); }
private:
	CStack stackForPush;
	CStack stackForPop; 
	void reload();
};