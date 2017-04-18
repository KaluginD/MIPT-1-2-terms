#pragma once
#include "Heap.h"
#pragma  once
#include <algorithm>

class LeftistHeap : public Heap {
public:
	// ����������� �� ���������
	LeftistHeap();
	// ����������� �� ��������� ������� ��������
	LeftistHeap( int key );
	virtual ~LeftistHeap();
	// ���������� ��������
	virtual void Insert( int key );
	// ������� �������
	virtual int ExtractMin();
	// ������� ���
	virtual void Meld( Heap* heapForMerge );
	bool isEmpty() const { return head == nullptr; }

protected:
	// ��������� �������
	struct HeapNode	{
		HeapNode() : dist( 0 ), leftChild( nullptr ), rightChild( nullptr ) {} 
		HeapNode( int element ) : key( element ), dist( 0 ), leftChild( nullptr ), rightChild( nullptr ) {}
		~HeapNode() {}
		// ������ ����, ���������� �� ������, ������� � ������ �������
		int key;
		int dist;
		HeapNode* leftChild;
		HeapNode* rightChild;
	};
	// ������ ������ ��������� �� ������
	HeapNode* head; 

	virtual bool swapCondition( HeapNode* node ) const;
	// ������� ������
	HeapNode* Merge( HeapNode* node1, HeapNode* node2 ) {
			// ���� ���� �� ������ ������, ���������� ������
			if( node1 == nullptr ) {
				return node2;
			}
			if( node2 == nullptr ) {
				return node1;
			}
			// �������, ��� ���� node1 ������ ����� node2
			if( node2->key < node1->key ) {
				std::swap( node1, node2 );
			}
			// ������� ������� ������
			node1->rightChild = Merge( node1->rightChild, node2 );
			// ��������������� �������� ������������� ����, ���� ����������
			if( swapCondition( node1 ) ) {
				std::swap( node1->leftChild, node1->rightChild );
			}
			// ��������� ������� ������� �������
			if( node1->rightChild == nullptr) {
				node1->dist = 1;
			}
			else {
				node1->dist = node1->rightChild->dist + 1;
			}
			// ���������� ������� �������
			return node1;
		}
};