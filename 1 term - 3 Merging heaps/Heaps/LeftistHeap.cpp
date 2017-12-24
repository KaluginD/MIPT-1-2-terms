#include "LeftistHeap.h"
#include <queue>

LeftistHeap::LeftistHeap() {
	head = new HeapNode(); 
}

LeftistHeap::LeftistHeap( int key ) {
	head = new HeapNode( key );
}
// деструтор работает по принципу BFS
LeftistHeap::~LeftistHeap() {
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
void LeftistHeap::Insert( int key ) {
	HeapNode* nodeForMerge = new HeapNode( key );
	head = Merge( head, nodeForMerge );
}
// извлечение минимума - удаление корня - слияние его поддеревьев
int LeftistHeap::ExtractMin() {
	int min = head->key;
	head = Merge( head->leftChild, head->rightChild );
	return min;
}
// слияние соответствует слиянию вершин
void LeftistHeap::Meld( Heap* heapForMerge ) {
	LeftistHeap* leftistHeapForMerge = dynamic_cast<LeftistHeap*> ( heapForMerge );
	if( leftistHeapForMerge == nullptr )
		return;
	head = Merge( head, leftistHeapForMerge->head );
}
// условие для замены детей при слиянии
bool LeftistHeap::swapCondition( HeapNode* node ) const {
	if(( node->leftChild == nullptr ) || ( node->leftChild->dist < node->rightChild->dist ))
		return true;
	else
		return false;
}