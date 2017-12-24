#include "SkewHeap.h"
#include <queue>

SkewHeap::SkewHeap() {
	head = new HeapNode(); 
}

SkewHeap::SkewHeap( int key ) {
	head = new HeapNode( key );
}
// ��������� �������� �� �������� BFS
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
// ���������� - ������� � ����� �� ������ ��������
void SkewHeap::Insert( int key ) {
	HeapNode* nodeForMerge = new HeapNode( key );
	head = Merge( head, nodeForMerge );
}
// ���������� �������� - �������� ����� - ������� ��� �����������
int SkewHeap::ExtractMin() {
	int min = head->key;
	head = Merge( head->leftChild, head->rightChild );
	return min;
}
// ������� ������������� ������� ������
void SkewHeap::Meld( Heap* heapForMerge ) {
	SkewHeap* leftistHeapForMerge = dynamic_cast<SkewHeap*> ( heapForMerge );
	if( leftistHeapForMerge == nullptr )
		return;
	head = Merge( head, leftistHeapForMerge->head );
}
// ������� ��� ������ ����� ��� �������
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
// ��������� �������� �� �������� BFS
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