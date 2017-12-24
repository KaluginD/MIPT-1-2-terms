#include "CQueue.h"
#include <stdio.h>
#include <cassert>
#include <iostream>

int main() {
	CQueue q;
	while( true ) {
		char command = 0;
		std::cin >> command;
		if( std::cin.eof() ){
			return 0;
		}
		switch( command ) {
		case '+':
			int key;
			std::cin >> key;
			q.Push( key );
			break;
		case '-':
			std::cout << q.Pop() << std::endl;
			break;
		default:
			assert( false );
		}
	}
	return 0;
}