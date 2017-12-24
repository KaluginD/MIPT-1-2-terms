#include "CQueue.h"
#include "CStack.h"
#include <assert.h>

void CQueue::Push( int element )
{

	stackForPush.Push( element );
}

int CQueue::Pop()
{
	if( !stackForPop.IsEmpty() )
		return stackForPop.Pop();
	assert( !stackForPush.IsEmpty() );
	reload();
	return stackForPop.Pop();
}

void CQueue::reload() 
{
	while( !stackForPush.IsEmpty() )
		stackForPop.Push( stackForPush.Pop() );
}