#pragma once
#include "Heap.h"
#pragma  once
#include <algorithm>

class LeftistHeap : public Heap {
public:
	// конструктор по умолчанию
	LeftistHeap();
	// конструктор по заданному первому элементу
	LeftistHeap( int key );
	virtual ~LeftistHeap();
	// добавление элемента
	virtual void Insert( int key );
	// извлечь минимум
	virtual int ExtractMin();
	// слияние куч
	virtual void Meld( Heap* heapForMerge );
	bool isEmpty() const { return head == nullptr; }

protected:
	// структура вершины
	struct HeapNode	{
		HeapNode() : dist( 0 ), leftChild( nullptr ), rightChild( nullptr ) {} 
		HeapNode( int element ) : key( element ), dist( 0 ), leftChild( nullptr ), rightChild( nullptr ) {}
		~HeapNode() {}
		// храним ключ, расстояние до выхода, правого и левого сыновей
		int key;
		int dist;
		HeapNode* leftChild;
		HeapNode* rightChild;
	};
	// храним только указатель на корень
	HeapNode* head; 

	virtual bool swapCondition( HeapNode* node ) const;
	// слияние вершин
	HeapNode* Merge( HeapNode* node1, HeapNode* node2 ) {
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
			node1->rightChild = Merge( node1->rightChild, node2 );
			// восстанавливаем свойство левосторонней кучи, если необходимо
			if( swapCondition( node1 ) ) {
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
};