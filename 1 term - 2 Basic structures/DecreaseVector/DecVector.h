#pragma once

class CVector {
public:
	// ����������� �� ���������
	CVector(); 
	// ����������� � �������� ��������� ��������
	explicit CVector( int size );
	// ����������� � �������� ��������� �������� � ��������� �� ���������
	CVector( int size, int defValue );
	// ����������
	~CVector();
	// �������� �������
	void push_back( int element );
	// ������� �������
	int pop_back();
	// �������� []
	int& operator [] ( const int index );
	// ����������� �������� []
	const int& operator [] ( const int index ) const;
	// ���������� ��������� � �������
	int size() const { return vectorSize; };

private:
	int bufferSize;
	int* buffer;
	int vectorSize;
	// ���������� ������� �������
	void grow();
	// ���������� ������� �������
	void decrease();
};