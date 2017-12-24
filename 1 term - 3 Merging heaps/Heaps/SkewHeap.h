#pragma once
#include "LeftistHeap.h"

class SkewHeap : public Heap {
public:
	// конструктор по умолчанию
	SkewHeap();
	// конструктор по заданному первому элементу
	SkewHeap( int key );
	virtual ~SkewHeap();
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
		HeapNode() : leftChild( nullptr ), rightChild( nullptr ) {} 
		HeapNode( int element ) : key( element ), leftChild( nullptr ), rightChild( nullptr ) {}
		~HeapNode() {}
		// храним ключ, расстояние до выхода, правого и левого сыновей
		int key;
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
			// возвращаем текущую вершину
			return node1;
		}
};

/*
class SkewHeap : public LeftistHeap {
public:
	SkewHeap();
	SkewHeap( int key );
	virtual ~SkewHeap();

protected:
	// структура вершины
	struct HeapNode	{
		HeapNode() : leftChild( nullptr ), rightChild( nullptr ) {} 
		HeapNode( int element ) : key( element ), leftChild( nullptr ), rightChild( nullptr ) {}
		~HeapNode() {}
		// храним ключ, расстояние до выхода, правого и левого сыновей
		int key;
		HeapNode* leftChild;
		HeapNode* rightChild;
	};
	HeapNode* head;

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
			std::swap( node1->leftChild, node1->rightChild );
			// возвращаем текущую вершину
			return node1;
		}
};
*/