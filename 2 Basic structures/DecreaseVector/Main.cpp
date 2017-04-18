#include "DecVector.h"

#include <iostream>
#include <stdio.h>
#include <assert.h>

int main() {
	CVector vector;
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
			vector.push_back( key );
			break;
		case '-':
			std::cout << vector.pop_back() << std::endl;
			break;
		case '[':
			int i;
			std::cin >> i >> command;
			std::cout << vector[i - 1] << std::endl;
			break;
		default:
			assert( false );
		}
	}
	return 0;
}