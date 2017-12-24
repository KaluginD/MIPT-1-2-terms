#pragma once

class CVector {
public:
	// конструктор по умолчанию
	CVector(); 
	// конструктор с заданным начальным размером
	explicit CVector( int size );
	// конструктор с заданным начальным размером и значением по умолчанию
	CVector( int size, int defValue );
	// деструктор
	~CVector();
	// добавить элемент
	void push_back( int element );
	// достать элемент
	int pop_back();
	// оператор []
	int& operator [] ( const int index );
	// константный оператор []
	const int& operator [] ( const int index ) const;
	// количество элементов в векторе
	int size() const { return vectorSize; };

private:
	int bufferSize;
	int* buffer;
	int vectorSize;
	// увеличение размера вектора
	void grow();
	// уменьшение размера вектора
	void decrease();
};