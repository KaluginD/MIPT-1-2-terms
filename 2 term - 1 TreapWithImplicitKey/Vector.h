#pragma once

#include <vector>

class Vector {
public:
	Vector();
	~Vector();
	int Sum( int l, int r );	// сумма на подотрезке
	void Push( int index, int count );	// добавление в i-ую позицию
	void Assign( int index, int count );	// обновление i-ого эл-та
	bool NextPermutation( int l, int r );
//	void write();

private:
	std::vector< int > buffer;
};