#include "CDeque.h"
#include <stdio.h>
#include <cassert>
#include <iostream>

int main() {
	CDeque q;
	while( true ) {
		char command1 = 0;
		char command2 = 0;
		std::cin >> command1 >> command2;
		if( std::cin.eof() ){
			return 0;
		}
		int key;
		switch( command1 ) {
		case '+':
			switch( command2 ) {
			case 'f':
				std::cin >> key;
				q.push_front( key );
				break;
			case 'b':
				std::cin >> key;
				q.push_back( key );
				break;
			}
			break;
		case '-':
			switch( command2 ) {
			case 'f':
				key=q.pop_front();
				std::cout << key;
				break;
			case 'b':
				key=q.pop_back();
				std::cout << key;
				break;
			}
			break;
		}
	}
	return 0;
}