#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#pragma once

// Начальный размер хеш-таблицы. Взаимнопрост с параметром хеш-функции.
const int InitialSize = 4;
// Параметр хеш-функции.
const int HashParameter = 91;

// Хеш-таблица, разрешающая коллизии методом цепочек.
class CHashTable {
public:
	CHashTable();
	~CHashTable();

	// Проверка наличия ключа.
	bool Has( const std::string& key ) const;
	// Добавление ключа. Возвращает false если элемент уже есть 
	// Если число элементов становится больше размера table, то table расширяется.
	bool Add( const std::string& key ); 
	// Удаление ключа. Уменьшение таблицы не заложено. Взовращает false если элемента нет.
	bool Remove( const std::string& key );

private:
	// Элемент цепочки
	struct CListNode {
		std::string Key;
		CListNode* Next;
		CListNode(const std::string& key) : Key( key ), Next( 0 ) {}
		~CListNode() { delete Next; }
	};
	std::vector<CListNode*> table;
	size_t keysCount;
	int myHash( const std::string& key ) const;
	void rehash();
};

CHashTable::CHashTable() : 
	table( InitialSize, 0 ),
	keysCount( 0 )
{
}

CHashTable::~CHashTable()
{
	for( size_t i = 0; i< table.size(); ++i ) {
		delete table[i];
	}
}

bool CHashTable::Has( const std::string& key ) const
{
	const int hash = myHash( key );
	for( CListNode* current = table[hash]; current != 0; current = current -> Next ){
		if( current->Key == key ) {
			return true;
		}
	}
	return false;
}

bool  CHashTable::Add( const std::string& key )
{
	if( keysCount >= table.size() ) {
		rehash();
	}
	const int hash = myHash( key );
	for( CListNode*  current = table[hash]; current != 0; current = current->Next ){
		if( current->Key == key) {
			return false;
		}
	}
	CListNode* newNode = new CListNode( key );
	newNode->Next = table[hash];
	table[hash] = newNode;
	return true;
}

bool CHashTable::Remove( const std::string& key )
{
	const int hash = myHash( key );
	if( table[hash] == 0 ) {
		return false;
	}
	if( table[hash]->Key == key ){
		CListNode* nodeToDelete = table[hash];
		table[hash] = nodeToDelete->Next;
		nodeToDelete->Next = 0;
		delete nodeToDelete;
		return true;
	}
	CListNode* prev = table[hash];
	for( ; prev->Next != 0 && prev->Next->Key != key;	prev = prev->Next) {
	}
	if( prev->Next ==0 ){
		return false;
	}
	CListNode* nodeToDelete = prev->Next;
	prev->Next = nodeToDelete->Next;
	nodeToDelete->Next = 0;
	delete nodeToDelete;
	return true;
//	for( CListNode* current = table[hash]; current != 0; current = current->Next )
}

// Полиномиальная хеш-функция строки, вычисляемая методом Горнера.
int CHashTable::myHash( const std::string& key ) const
{
	int hash = 0;
	for( size_t  i = 0; i < key.length(); ++i ) {
		hash = ( hash * HashParameter + key[i] ) % table.size(); 
	}
	return hash;
}

// Перехеширование с  удвоением таблицы.
void CHashTable::rehash()
{
	std::vector<CListNode*> oldTable( table.size() *2, 0 );
	std::swap( table, oldTable );
	for(  size_t i = 0; i < oldTable.size(); ++i ) {
		for( CListNode* node = oldTable[i]; node != 0; node = node->Next) {
			Add( node->Key );
		}
		delete oldTable[i];
	}
}

int main() {
	CHashTable hashTable;
	while( true ) {
		char command = 0;
		std::cin >> command;
		if( std::cin.eof() ){
			return 0;
		}
		std::string key;
		std::cin >> key;
		switch( command ) {
		case '?':
			std::cout << ( hashTable.Has(key) ? "OK" : "FAIL" ) << std::endl;
			break;
		case '+':
			std::cout << ( hashTable.Add(key) ? "OK" : "FAIL" ) << std::endl;
			break;
		case '-':
			std::cout << ( hashTable.Remove(key) ? "OK" : "FAIL" ) << std::endl;
			break;
		default:
			assert( false );
		}
	}
	return 0;
}