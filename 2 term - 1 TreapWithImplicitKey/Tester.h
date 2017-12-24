#pragma once

#include "Vector.h"
#include "IKTreap.h"
#include <algorithm>
#include <vector>

// �������
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
	int commandNumber;	// ���������� ������
	int commandRange;	// �������� ��������
	void createCommands();	// �������� ������
	std::vector< std::pair< test, std::pair< int, int > > > Commands;	// ������ ������
	IKTreap Treap;	
	Vector Vector;
	void vectorTesting();	// ������������ �� ���������� � ���
	void treapTesting();	// ������������ ���������� �� ������
	std::vector< int > vectorAns;	// ������ ������� ������� ����������
	std::vector< int > treapAns;	// ������ ������� ���������� �� ������
};