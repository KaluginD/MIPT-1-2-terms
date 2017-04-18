#pragma once

class CStack {
public:
	CStack( int _bufferSize );
	CStack();
	~CStack();
	void Push( int elenemt );
	int Pop();
	bool IsEmpty() const { return top == -1; }
	int top;
private:
	int* buffer;
	int bufferSize;
};