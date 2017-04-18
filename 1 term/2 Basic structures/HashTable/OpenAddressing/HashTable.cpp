#include "HashTable.h"

// Начальный размер хеш-таблицы. Взаимнопрост с параметром хеш-функции.
const int InitialSize = 16;
// Параметр хеш-функции.
const int HashParameter = 91;


CHashTable::CHashTable() : 
	keysCount( 0 ),
	tableSize( InitialSize )
{
	table = new std::string[ InitialSize ];
	for( size_t i = 0; i < tableSize; ++i ){
		table[i] = "NULL";
	}
}

CHashTable::~CHashTable()
{
	delete[] table;
}

bool CHashTable::Has( const std::string& key ) const
{
	int hash = myHash( key );
	int i = 0;
	while( table[hash] != "NULL" && i <= keysCount ) {
		if( table[hash] == key) {
			return true;
		}
		hash = (hash + ++i ) %tableSize;
	}
	return false;
}

bool  CHashTable::Add( const std::string& key )
{
	if( tableSize * 2 / 3 < keysCount ) {
		rehash();
	}
	int hash = myHash( key );
	int i = 1;
	while( table[hash] != "NULL" ) {
		if( key == table[hash] ) {
			return false;
		}
		hash = ( hash + i + 1 ) % tableSize;
		++i;
	}
	table[hash] = key;
	++keysCount;
	return true;
}

bool CHashTable::Remove( const std::string& key )
{
	int hash = myHash( key );
	int i = 1;
	while( table[hash] != key && table[hash] != "NULL" && i <= keysCount ){
		hash = ( hash + ++i ) % tableSize;
	}
	if( table[hash] == "NULL" ) {
		return false;
	}
	if( table[hash] == key ) {
		table[hash] = "DELETED";
		return true;
	}
	--keysCount;
	return true;
}

// Полиномиальная хеш-функция строки, вычисляемая методом Горнера.
int CHashTable::myHash( const std::string& key ) const
{
	int hash = 0;
	for( size_t  i = 0; i < key.length(); ++i ) {
		hash = ( hash * HashParameter + key[i] ) % tableSize; 
	}
	return hash;
}

// Перехеширование с  удвоением таблицы.
void CHashTable::rehash()
{
	tableSize *= 2;
	std::string* oldTable = new std::string[ tableSize ];
	std::swap( table, oldTable );
	for( size_t i = 0; i < tableSize; ++i ) {
		table[i] = "NULL";
	}
	for( size_t i = 0; i < tableSize / 2; ++i ) {
		if( oldTable[i] != "NULL" ) {
			Add( oldTable[i] );
		}
	}
	delete[] oldTable;

}