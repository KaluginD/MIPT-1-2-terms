#pragma once
#include "SkewHeap.h"
#include <queue>

SkewHeap::SkewHeap() {
	head = new HeapNode(); 
}

SkewHeap::SkewHeap( int element ) {
	head = new HeapNode( element );
}
// деструтор работает по принципу BFS
SkewHeap::~SkewHeap() {
	std::queue< HeapNode* > queue;
	queue.push( head );
	while( !queue.empty() ) {
		HeapNode* top = queue.front();
		queue.pop();
		if( top != nullptr ) {
			if( top->leftChild != nullptr )
				queue.push( top->leftChild  );
			if( top->rightChild != nullptr )
				queue.push( top->rightChild );
			delete top;
		}
	}
}
// добавление - слияние с кучей из одного элемента
void SkewHeap::Add( int element ) {
	HeapNode* nodeForMerge = new HeapNode( element );
	head = Meld( head, nodeForMerge );
}
// слияние соответствует слиянию вершин
void SkewHeap::Merge( SkewHeap* heapForMerge ) {
	head = Meld( head, heapForMerge->head );
}
// получение минимума - значение в корне
int SkewHeap::GetMin() {
	return head->key;
}
// извлечение минимума - удаление корня - слияние его поддеревьев
int SkewHeap::ExtractMin() {
	int min = head->key;
	head = Meld( head->leftChild, head->rightChild );
	return min;
}
