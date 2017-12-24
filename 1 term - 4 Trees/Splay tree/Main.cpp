#include "Tester.h"
#include "SplayTree.h"
#include "AVLtree.h"
#include <iostream>
#include <assert.h>
#include <string>

int main() {
	int N;
	std::cin >> N;
	Tester< std::string > tester( N );
	tester.testing();
	system( "pause" );
	return 0;
}