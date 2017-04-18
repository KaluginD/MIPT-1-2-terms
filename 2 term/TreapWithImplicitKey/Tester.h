#pragma once

#include "Vector.h"
#include "IKTreap.h"
#include <algorithm>
#include <vector>

// команда
enum test {
	SUM,
	PUSH,
	ASSIGN,
	NEXTPERMUTATION
};

class Tester {
public:
	Tester( int Number, int Range );
	~Tester();
private:
	int commandNumber;	// количество команд
	int commandRange;	// диапазон значений
	void createCommands();	// создание команд
	std::vector< std::pair< test, std::pair< int, int > > > Commands;	// вектор команд
	IKTreap Treap;	
	Vector Vector;
	void vectorTesting();	// тестирование на реализации в лоб
	void treapTesting();	// тестирование реализации на дереве
	std::vector< int > vectorAns;	// вектор ответов лобовой реализации
	std::vector< int > treapAns;	// вектор ответов реализации на дереве
};