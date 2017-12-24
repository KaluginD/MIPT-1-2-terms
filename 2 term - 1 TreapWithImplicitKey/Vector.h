#pragma once

#include <vector>

class Vector {
public:
	Vector();
	~Vector();
	int Sum( int l, int r );	// ����� �� ����������
	void Push( int index, int count );	// ���������� � i-�� �������
	void Assign( int index, int count );	// ���������� i-��� ��-��
	bool NextPermutation( int l, int r );
//	void write();

private:
	std::vector< int > buffer;
};