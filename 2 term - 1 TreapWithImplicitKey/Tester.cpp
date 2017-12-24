#pragma once

#include "Tester.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>

Tester::Tester( int Number, int Range ) {
	commandNumber = Number;
	commandRange = Range;
	createCommands();	// ���������� �������
	vectorTesting();	// ��������� �� �������
	treapTesting();		// ��������� �� ������
	bool flag = ( vectorAns.size() == treapAns.size() );	// ���������� ���������� ������� ��� � ���
	if( !flag ) 
		std::cout << "- Answers have different size. - " << std::endl;
	int k = 0;
	// ���� �� ������� - ���������� ������
	if( flag )
		for( int i = 0; i < vectorAns.size(); ++i ) {
			flag = ( vectorAns[i] == treapAns[i] );	
			if( !flag ) {
				++k;
			}
		}
	// ������� ��������� ������������
	if( flag )
		std::cout << "+ Answers are the same. Tested succesfuly. + " << std::endl;
	else
		std::cout << "- Answers are different. Tested unsuccesfuly. - . Number of wrong answers " << k << std::endl;
};

Tester::~Tester() {

};

void Tester::createCommands () {
	std::srand( clock() );	
	// ������ ������� - push
	int count = std::rand() % commandRange;
	Commands.push_back( std::make_pair( test( 1 ), std::make_pair( 0, count ) ) );
	int elementsNumber = 1;
	// ������� ��������� �������
	for( int i = 1; i < commandNumber; ++i ) {
		test command = test( rand() % 4 );
		int index1 = rand() % elementsNumber;	// ������ ������� - ������
		// ������ - �������, ���� push ��� assign, ������ - ���� sum ��� nextPerm
		if( command == 1 || command == 2 ) {
			count = std::rand() % commandRange;
		} else {
			count = std::rand() % elementsNumber;
			// ������� - ������ �� ������ �������
			if( command == 3 ) {
				if( count == elementsNumber - 1 )
					count = 0;
				if( index1 == elementsNumber - 1)
					index1 = 0;
			}
			if( count < index1 )
				std::swap( index1, count );
		}
		Commands.push_back( std::make_pair( command, std::make_pair( index1, count ) ) ); 
		// ���� ������� - push - ���-�� ��������� + 1
		if ( command == 1 ) 
			++elementsNumber;
	}
	std::cout << "Tests are ready" << std::endl;
};

// ������������ �������
void Tester::vectorTesting() {
	clock_t time = clock();	// �������� �����
	for( int i = 0; i < commandNumber; ++i ) {
		int ans = 0;
		switch ( Commands[i].first )
		{
		case 0 :
			ans = Vector.Sum( Commands[i].second.first, Commands[i].second.second );
			vectorAns.push_back(ans);	// ��������� ��������� � ������
			break;
		case 1 :
			Vector.Push( Commands[i].second.first, Commands[i].second.second );
			break;
		case 2 :
			Vector.Assign( Commands[i].second.first, Commands[i].second.second );
			break;
		case 3:
			Vector.NextPermutation( Commands[i].second.first, Commands[i].second.second );
			break;
		}
	}
	clock_t result = clock() - time; //������� �����
	std::cout << " Vector is tested. Testing time - " << result << std::endl;
};

// ������������ ������
void Tester::treapTesting() {
	clock_t time = clock();	// �������� �����
	for( int i = 0; i < commandNumber; ++i ) {
		int ans = 0;
		switch ( Commands[i].first )
		{
		case 0 :
			ans = Treap.Sum( Commands[i].second.first, Commands[i].second.second );
			treapAns.push_back(ans);	// ��������� ��������� � ������
			break;
		case 1 :
			Treap.Push( Commands[i].second.first, Commands[i].second.second );
			break;
		case 2 :
			Treap.Assign( Commands[i].second.first, Commands[i].second.second );
			break;
		case 3:
			Treap.NextPermutation( Commands[i].second.first, Commands[i].second.second );
			break;
		}
	}
	clock_t result = clock() - time;	//������� �����
	std::cout << " Treap is tested. Testing time - " << result << std::endl;
};
