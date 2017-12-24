#pragma once

#include <string>
#include <vector>

// ���-�������, ����������� �������� ������� �������� ����������.
class CHashTable {
public:
	CHashTable();
	~CHashTable();

	// �������� ������� �����.
	bool Has( const std::string& key ) const;
	// ���������� �����. ���������� false ���� ������� ��� ���� 
	// ���� ����� ��������� ���������� ������ ������� table, �� table �����������.
	bool Add( const std::string& key ); 
	// �������� �����. ���������� ������� �� ��������. ���������� false ���� �������� ���.
	bool Remove( const std::string& key );

private:
	std::string* table;
	size_t tableSize;
	size_t keysCount;
	int myHash( const std::string& key ) const;
	void rehash();
};