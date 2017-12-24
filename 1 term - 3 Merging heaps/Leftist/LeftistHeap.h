#pragma once
#include <algorithm>

class LeftistHeap {
private:
	// структура вершины
	struct HeapNode	{
		HeapNode() : dist( 0 ), leftChild( nullptr ), rightChild( nullptr ) {} 
		explicit HeapNode( int element ) : key( element ), dist( 1 ), leftChild( nullptr ), rightChild( nullptr ) {}
		// храним ключ, расстояние до выхода, правого и левого сыновей
		int key;	
		int dist;
		HeapNode* leftChild;
		HeapNode* rightChild;
	};
	// слияние вершин
	HeapNode* Meld( HeapNode* node1, HeapNode* node2 ) {
		// если одна из вершин пустая, возвращаем другую
		if( node1 == nullptr ) {
			return node2;
		}
		if( node2 == nullptr ) {
			return node1;
		}
		// считаем, что ключ node1 меньше ключа node2
		if( node2->key < node1->key ) {
			std::swap( node1, node2 );
		}
		// сливаем вершины вправо
		node1->rightChild = Meld( node1->rightChild, node2 );
		// восстанавливаем свойство левосторонней кучи, если необходимо
		if( ( node1->leftChild == nullptr ) || ( node1->leftChild->dist < node1->rightChild->dist ) ) {
			std::swap( node1->leftChild, node1->rightChild );
		}
		// обновляем глубину текущей вершины
		if( node1->rightChild == nullptr) {
			node1->dist = 1;
		}
		else {
			node1->dist = node1->rightChild->dist + 1;
		}
		// возвращаем текущую вершину
		return node1;
	}
public:
	// конструктор по умолчанию
	LeftistHeap();
	// конструктор по заданному первому элементу
	explicit LeftistHeap( int element );
	~LeftistHeap();
	// добавление элемента
	void Add( int element );
	// слияние куч
	void Merge( LeftistHeap* heapForMerge );
	// получить минимум
	int GetMin();
	// извлечь минимум
	int ExtractMin();

	HeapNode* head;
};