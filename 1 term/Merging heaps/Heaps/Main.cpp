#include "Heap.h"
#include "BinomialHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>

// структура команды
// command  = 0 - AddHeap( int key );
// command  = 1 - Insert( int index1, int key );
// command  = 2 - ExtractMin( int index1 );
// command  = 3 - Meld( int index1, int index2 );

struct Command {
	Command() {}
	Command( int com, int k, int i1, int i2 ) {
		command = com;
		key = k;
		index1 = i1;
		index2 = i2;
	}
	int command;
	int key;
	int index1;
	int index2;
};

int main() {
	std::vector< LeftistHeap* > leftistHeaps;
	std::vector< SkewHeap* > skewHeaps;
	std::vector< BinomialHeap* > binomialHeaps;
	std::vector< int > leftAns;
	std::vector< int > skewAns;
	std::vector< int > binAns;
	std::vector< Command > commands;
	std::vector< int > heaps;
	// N - количество случайных команд
	int N = 0;
	std::cin >> N;
	int firstKey = rand() % 10000;
	leftistHeaps.push_back( new LeftistHeap( firstKey ) );
	skewHeaps.push_back( new SkewHeap( firstKey ) );
	binomialHeaps.push_back( new BinomialHeap( firstKey ) );
	heaps.push_back( 1 );
	--N;
	int number = 1;
	int flag = 0;
	
	while ( N > 0 ) {
		int command = rand() % 4;
		int key = rand() % 10000;
		int index1 = rand() % heaps.size();
		int index2 = rand() % heaps.size();
		int f = 1;
		switch ( command )
		{
		case 0:
			heaps.push_back( 1 );
			break;
		case 1:
			++heaps[ index1 ];
			break;
		case 2:
			if( ( heaps[ index1 ] == 1 && number > 1 ) ||  heaps[ index1 ] > 1  )
				--heaps[ index1 ];
			else 
				f = 0;
			if( heaps[ index1 ] == 0 ) {
				heaps[ index1 ] = heaps[ heaps.size() - 1 ];
				heaps.pop_back();
			}
			break;
		case 3:
			if( index1 != index2 ) {
				heaps[ index1 ] += heaps[ index2 ];
				heaps[ index2 ] = heaps[ heaps.size() - 1 ];
				heaps.pop_back();
			}
			else f = 0;
		}
		if( f == 1 ) {
			commands.push_back( Command( command, key, index1, index2 ) );
			--N;		
		}
	}

	time_t time = clock();
	for( int i = 0; i < commands.size(); ++i ) {
		switch ( commands[i].command )
		{
		case 0:
			leftistHeaps.push_back( new LeftistHeap( commands[i].key ) );
			break;
		case 1:
			leftistHeaps[ commands[i].index1 ]->Insert( commands[i].key );
			break;
		case 2:
			if( !leftistHeaps[ commands[i].index1 ]->isEmpty() ) {
				int minL = leftistHeaps[ commands[i].index1 ]->ExtractMin();
				leftAns.push_back( minL );
			}
			if( leftistHeaps[ commands[i].index1 ]->isEmpty() ) {
				leftistHeaps[ commands[i].index1 ] = leftistHeaps[ leftistHeaps.size() - 1 ];
				leftistHeaps.pop_back();
			}
			break;
		case 3:
			if( commands[i].index1 != commands[i].index2 ) {
				leftistHeaps[ commands[i].index1 ]->Meld( leftistHeaps[ commands[i].index2 ] );
				leftistHeaps[ commands[i].index2 ] = leftistHeaps[ leftistHeaps.size() - 1 ];
				leftistHeaps.pop_back();		
			}
		}
	}
	time_t timeLeft = clock() - time;
	std::cout << "LeftistHeaps time: " << timeLeft << std::endl;

	time = clock();
	for( int i = 0; i < commands.size(); ++i ) {
		switch ( commands[i].command )
		{
		case 0:
			skewHeaps.push_back( new SkewHeap( commands[i].key ) );
			break;
		case 1:
			skewHeaps[ commands[i].index1 ]->Insert( commands[i].key );
			break;
		case 2:
			if( !skewHeaps[ commands[i].index1 ]->isEmpty() ) {
				int minS = skewHeaps[ commands[i].index1 ]->ExtractMin();
				skewAns.push_back( minS );
			}
			if( skewHeaps[ commands[i].index1 ]->isEmpty() ) {
				skewHeaps[ commands[i].index1 ] = skewHeaps[ skewHeaps.size() - 1 ];
				skewHeaps.pop_back();
			}
			break;
		case 3:
			if( commands[i].index1 != commands[i].index2 ) {
				skewHeaps[ commands[i].index1 ]->Meld( skewHeaps[ commands[i].index2 ] );
				skewHeaps[ commands[i].index2 ] = skewHeaps[ skewHeaps.size() - 1 ];
				skewHeaps.pop_back();		
			}
		}
	}
	time_t timeSkew = clock() - time;
	std::cout << "SkewHeaps time: " << timeSkew << std::endl;

	time = clock();
	for( int i = 0; i < commands.size(); ++i ) {
		switch ( commands[i].command )
		{
		case 0:
			binomialHeaps.push_back( new BinomialHeap( commands[i].key ) );
			break;
		case 1:
			binomialHeaps[ commands[i].index1 ]->Insert( commands[i].key );
			break;
		case 2:
			if( !binomialHeaps[ commands[i].index1 ]->isEmpty() ) {
				int minB = binomialHeaps[ commands[i].index1 ]->ExtractMin();
				binAns.push_back( minB );
			}
			if( binomialHeaps[ commands[i].index1 ]->isEmpty() ) {
				binomialHeaps[ commands[i].index1 ] = binomialHeaps[ skewHeaps.size() - 1 ];
				binomialHeaps.pop_back();
			}
			break;
		case 3:
			if( commands[i].index1 != commands[i].index2 ) {
				binomialHeaps[ commands[i].index1 ]->Meld( binomialHeaps[ commands[i].index2 ] );
				binomialHeaps[ commands[i].index2 ] = binomialHeaps[ binomialHeaps.size() - 1 ];
				binomialHeaps.pop_back();		
			}
		}
	}

	time_t timeBin = clock() - time;
	std::cout << "BinomialHeaps time: " << timeBin << std::endl;
	if( leftAns.size() != skewAns.size() || leftAns.size() != binAns.size() )
		flag = 1;
	else 
		for( int i = 0; i < leftAns.size(); ++i ) 
			if( leftAns[i] != skewAns[i] || leftAns[i] != binAns[i] ) 
				flag = 1;

	if( flag == 0 ) 
		std::cout << "Test finished successfuly" << std::endl;
	else
		std::cout << "ALERT! WRONG ANSWER!" << std::endl;
	system("pause");
	return 0;
}