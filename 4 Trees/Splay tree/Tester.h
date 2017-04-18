#pragma once

#include "SplayTree.h"
#include "AVLtree.h"
#include <utility>
#include <vector>
#include <set>
#include <random>
#include <string>
#include <ctime>
#include <iostream>

enum testType {
	add,
	find,
	del,
	testNumber
};

enum testResult {
	OK,
	FAIL
};

template < typename T>
class Tester {

public:
	//using testpair = std::pair< testType, std::string >;
	//using testresult = std::pair< std::vector< testResult >, double >;
	typedef std::pair< testType, std::string > testpair;
	typedef std::pair< std::vector< testResult >, int > testresult;
	Tester() {}
	Tester( int n ) {
		testsNumber = n;
		std::vector< std::string > keys;
		srand( clock() );
		while( keys.size() < n / 5 || keys.size() < 1  )
			keys.push_back( randString( 4 ) );
		while( tests.size() < n ) {
			testType command = testType( rand() % testNumber );
			std::string key = keys[ rand() % keys.size() ];
			tests.push_back( std::make_pair( command, key ) );
		}
		std::cout  << "Tests are ready" << std::endl;
	}
	~Tester() {}

	void testing() {
		testresult splayResult = testingSplayTree();
		std::cout << "Splay Tree is tested" << std::endl;

		testresult avlResult = testingAVLTree();
		std::cout << "AVL Tree is tested" << std::endl;

		testresult setResult = testingSet();
		std::cout << "Set is tested" << std::endl; 

		bool correctSplay = true;
		bool correctAVL = true;
		for( int i = 0; i < testsNumber; ++i ) { 
			if( correctSplay ) {
				correctSplay = ( splayResult.first[i] == setResult.first[i] );
				if( !correctSplay )	
					std::cout << "FAIL" << std::endl;
			}
			if( correctAVL ) {
				correctAVL = ( avlResult.first[i] == setResult.first[i] );
			if( !correctAVL )	
					std::cout << "FAIL" << std::endl;
			}
		}

		if( !correctSplay )
			std::cout << "Splay Tree FAILS. Time = " << splayResult.second << std::endl;
		else
			std::cout << "Splay Tree finished test successfully. Time = " << splayResult.second << std::endl;
		if( !correctAVL )
			std::cout << "AVL Tree FAILS. Time = " << avlResult.second << std::endl;
		else
			std::cout << "AVL Tree finished test successfully. Time = " << avlResult.second << std::endl;
		std::cout << "Set time = " << setResult.second << std::endl;
	}

private:
	SplayTree< std::string > splayTree;
	AVLtree< std::string > avlTree;
	std::set< std::string > set;
	int testsNumber;
	std::vector< testpair > tests;

	static const std::string universe;
	std::string randString( int size ) {
		srand( clock() );
		std::string ans = "";
		while( ans.length() != size )
			ans += universe[ rand() % universe.length() ];
		return ans;
	}

	testresult testingSplayTree() {
		std::vector< testResult > ans;
		int time = clock();
		for( int i = 0; i < testsNumber; ++i ) {
			testpair test = tests[i];
			testResult result;
			bool res;
			switch ( test.first ) {
			case add:
				res = splayTree.Insert( test.second );
				break;
			case find:
				res = splayTree.Find( test.second );
				break;
			case del:
				res = splayTree.Remove( test.second );
				break;
			}
			if( res )
					result = OK;
				else
					result = FAIL;
			ans.push_back( result );
		}
		time = clock() - time;
		return std::make_pair( ans, time );
	}
	testresult testingAVLTree() {
		std::vector< testResult > ans;
		int time = clock();
		for( int i = 0; i < testsNumber; ++i ) {
			testpair test = tests[i];
			testResult result;
			bool res;
			switch ( test.first ) {
			case add:
				res = avlTree.Insert( test.second );
				break;
			case find:
				res = avlTree.Find( test.second );
				break;
			case del:
				res = avlTree.Remove( test.second );
				break;
			}
			if( res )
					result = OK;
				else
					result = FAIL;
			ans.push_back( result );
		}
		time = clock() - time;
		return std::make_pair( ans, time );
	}
	testresult testingSet() {
		std::vector< testResult > ans;
		int time = clock();
		for( int i = 0; i < testsNumber; ++i ) {
			testpair test = tests[i];
			testResult result;
			bool res;
			switch ( test.first ) {
			case add:
				res = set.insert( test.second ).second;
				break;
			case find:
				res = ( set.find( test.second ) != set.end() );
				break;
			case del:
				res = set.erase( test.second ) > 0;
				break;
			}
			if( res )
					result = OK;
				else
					result = FAIL;
			ans.push_back( result );
		}
		time = clock() - time;
		return std::make_pair( ans, time );
	}
};

template <typename T>
const std::string Tester<T>::universe = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";