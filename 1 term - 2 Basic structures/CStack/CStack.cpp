#include "CStack.h"
#include <assert.h>

const int InitualSize = 64;

CStack::CStack() : 
	bufferSize( InitualSize ),
	top( -1 )
{
	buffer = new int[InitualSize];
}

CStack::CStack( int _bufferSize ) : 
	bufferSize( _bufferSize ),
	top( -1 )
{
	buffer = new int[bufferSize];
}

CStack::~CStack() 
{
	delete[] buffer;
}

void CStack::Push( int element ) 
{
	assert( top + 1 < bufferSize );
	buffer[++top] = element;
}

int CStack::Pop()
{
	assert( top != -1 );
	return buffer[ top-- ];
}