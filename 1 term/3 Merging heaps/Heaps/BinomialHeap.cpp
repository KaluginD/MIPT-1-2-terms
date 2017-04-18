#include "BinomialHeap.h"
#include <queue>

BinomialHeap::BinomialHeap() {
	head = new HeapNode();
}

BinomialHeap::BinomialHeap( int element ) {
	head = new HeapNode();
	head->sibling = new HeapNode( element );
}
// ���������� �������� �� �������� BFS 
BinomialHeap::~BinomialHeap() {
	std::queue< HeapNode* > queue;
	queue.push( head );
	while( !queue.empty() ) {
		HeapNode* top = queue.front();
		queue.pop();
		if( top != nullptr ) {
			if( top->child != nullptr )
				queue.push( top->child  );
			if( top->sibling != nullptr )
				queue.push( top->sibling );
			delete top;
		}
	}
}

// ���������� ���� - ������� � ����� � 1 ������
void BinomialHeap::Insert( int key ) {
	BinomialHeap* heapForMerge = new BinomialHeap( key );
	Heap* heapForSend = dynamic_cast < Heap* > ( heapForMerge );
	Meld( heapForSend );	 
}

// ������� ���� ���. ������ ������� ��� ������� � ���� ���� � ������� ����������� �������
// ����� �������� �� ��������� ����, ���� ��������� ������� ���������� �������, ������� �� � ����
void BinomialHeap::Meld( Heap* heapForMerge ) {
	BinomialHeap* heap1 = dynamic_cast< BinomialHeap* > ( heapForMerge );
	BinomialHeap* heap2 = new BinomialHeap();
	std::swap( head, heap2->head );

	HeapNode* headNow1 = heap1->head->sibling;
	HeapNode* headNow2 = heap2->head->sibling;
	HeapNode* headNow = head;

	if( headNow1 == nullptr ) {
		headNow->sibling = headNow2;
		return;
	}
	if( headNow2 == nullptr ) {
		headNow->sibling = headNow1;
		return;
	}

	while( headNow1 != nullptr && headNow2 != nullptr ) {
		if( headNow1->degree < headNow2->degree)
		//	||	  ( headNow1->degree == headNow2->degree &&  headNow1->key < headNow2->key ) ) 
		{
			headNow->sibling = headNow1;
			headNow1 = headNow1->sibling;
		}
		else
		if( headNow2->degree <= headNow1->degree)
		//	||	  ( headNow2->degree == headNow1->degree && headNow2->key < headNow1->key ) )
		{
			headNow->sibling = headNow2;
			headNow2 = headNow2->sibling;
		}
		headNow = headNow->sibling;
	}
	while( headNow1 != nullptr ) {
		headNow->sibling = headNow1;
		headNow = headNow->sibling;
		headNow1 = headNow1->sibling;
	}
	while( headNow2 != nullptr ) {
		headNow->sibling = headNow2;
		headNow = headNow->sibling;
		headNow2 = headNow2->sibling; 
	}

	headNow = head->sibling;
	while( headNow != nullptr && headNow->sibling != nullptr ) {
		if( headNow->degree == headNow->sibling->degree ) {
			if( headNow->sibling->sibling != nullptr && headNow->sibling->degree == headNow->sibling->sibling->degree ) {
				headNow = headNow->sibling;
			}
			if( headNow->key > headNow->sibling->key ) {
				HeapNode* sibling = headNow->sibling;
				std::swap( headNow->sibling, headNow->sibling->sibling );
				std::swap( *headNow, *sibling );
			}
			
			HeapNode* next = headNow->sibling->sibling;

			headNow->sibling->sibling = headNow->child;
			++headNow->degree;
			headNow->child = headNow->sibling;

			headNow->sibling = next;
		}
		else
			headNow = headNow->sibling;
	}
}

// ���������� ��������. �������  �������, ��������� ��� � ������� ���������� ���� � ����� �� ����� ������������ ������
int BinomialHeap::ExtractMin() {
	// ������ ������� ������, �������������� ������  � ���������(��� ��������������� ��� �����)
	int min = head->sibling->key;
	HeapNode* headNow = head;
	HeapNode* nodeWithMin = headNow; 
	while( headNow->sibling != nullptr ) {
		if( headNow->sibling->key < min ){
			min = headNow->sibling->key;
			nodeWithMin = headNow;
		}
		headNow = headNow->sibling;
	}
	// ������� ���� ����� ������ � ���������, ������� ������ � ���������� �����
	BinomialHeap* heapForMerge = new BinomialHeap();
	HeapNode* nodeForMegre = nodeWithMin->sibling->child;
	nodeWithMin->sibling = nodeWithMin->sibling->sibling;
	headNow = heapForMerge->head;
	// ���������� � ���� ���� ����� ������ � ���������
	while( nodeForMegre != nullptr ) {
		headNow->sibling = nodeForMegre;
		headNow = headNow->sibling;
		nodeForMegre = nodeForMegre->sibling;
	}
	Heap* heapForSend = dynamic_cast< Heap* > ( heapForMerge );
	Meld( heapForSend );
	return min;
}

bool BinomialHeap::isEmpty() const
{
	return head == nullptr;
}