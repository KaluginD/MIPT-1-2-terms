#include "SkewHeap.h"
#include <queue>

SkewHeap::SkewHeap() {
	head = new HeapNode(); 
}

SkewHeap::SkewHeap( int key ) {
	head = new HeapNode( key );
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
void SkewHeap::Insert( int key ) {
	HeapNode* nodeForMerge = new HeapNode( key );
	head = Merge( head, nodeForMerge );
}
// извлечение минимума - удаление корня - слияние его поддеревьев
int SkewHeap::ExtractMin() {
	int min = head->key;
	head = Merge( head->leftChild, head->rightChild );
	return min;
}
// слияние соответствует слиянию вершин
void SkewHeap::Meld( Heap* heapForMerge ) {
	SkewHeap* leftistHeapForMerge = dynamic_cast<SkewHeap*> ( heapForMerge );
	if( leftistHeapForMerge == nullptr )
		return;
	head = Merge( head, leftistHeapForMerge->head );
}
// условие для замены детей при слиянии
bool SkewHeap::swapCondition( HeapNode* node ) const {
	return true;
}

/*
SkewHeap::SkewHeap() {
	head = new HeapNode(); 
}

SkewHeap::SkewHeap( int key ) {
	head = new HeapNode( key );
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
*/