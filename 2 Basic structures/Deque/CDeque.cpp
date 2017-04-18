#include "CDeque.h"
#include "CStack.h"
#include <assert.h>

void CDeque::push_back( int element )
{
	stackLeft.Push( element );
}

void CDeque::push_front( int element )
{
	stackRight.Push( element );
}

int CDeque::pop_back()
{
	if( !stackLeft.IsEmpty() ){
		return stackLeft.Pop();
	}
	assert( !stackRight.IsEmpty() );
	rightToLeft();
	return stackLeft.Pop();
}

int CDeque::pop_front()
{
	if( !stackRight.IsEmpty() ){
		return stackRight.Pop();
	}
	assert( !stackLeft.IsEmpty() );
	leftToRight();
	return stackRight.Pop();
}

void CDeque::leftToRight()
{
	while( !stackLeft.IsEmpty() )
		stackRight.Push( stackLeft.Pop() );
}

void CDeque::rightToLeft()
{
	while( !stackRight.IsEmpty() )
		stackLeft.Push( stackRight.Pop() );
}