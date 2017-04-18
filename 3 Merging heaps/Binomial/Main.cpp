#include "BinomialHeap.h"
#include <vector>
#include <string>
#include <iostream>

int main() {
	std::vector< BinomialHeap* > Heaps;
	std::string command;
	while( true ) {
		std::cin >> command;
		if( !std::cin ) {
			break;
		}
		if( command == "add" ) {
			int element;
			std::cin >> element;
			BinomialHeap* heap = new BinomialHeap( element );
			Heaps.push_back( heap );
			continue;
		}
		if( command == "insert" ) {
			int index;
			int element;
			std::cin >> index >> element;
			Heaps[ index ]->Add( element );
			continue;
		}
		if( command == "meld" ) {
			int index1;
			int index2;
			std::cin >> index1 >> index2;
			Heaps[ index1 ]->Merge( Heaps[ index2 ] );
			Heaps[ index2 ] = Heaps[ Heaps.size() - 1 ];
			Heaps.pop_back();
			continue;
		}
		if( command == "min" ) {
			int index;
			std::cin >>  index;
			int answer = Heaps[ index ]->ExtractMin();
			std::cout << answer << std::endl;
			if ( Heaps[ index ]->head->sibling == nullptr ) {
				Heaps[ index ] = Heaps[ Heaps.size() - 1 ];
				Heaps.pop_back();
			}
			continue;
		}
	}
	return 0;
}