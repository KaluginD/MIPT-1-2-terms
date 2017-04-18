#pragma once

#include <string>
#include <vector>

// Хеш-таблица, разрешающая коллизии методом открытой адрессации.
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
	std::string* table;
	size_t tableSize;
	size_t keysCount;
	int myHash( const std::string& key ) const;
	void rehash();
};