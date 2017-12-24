#pragma once
#include "LeftistHeap.h"

class SkewHeap : public Heap {
public:
	// ����������� �� ���������
	SkewHeap();
	// ����������� �� ��������� ������� ��������
	SkewHeap( int key );
	virtual ~SkewHeap();
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
		HeapNode() : leftChild( nullptr ), rightChild( nullptr ) {} 
		HeapNode( int element ) : key( element ), leftChild( nullptr ), rightChild( nullptr ) {}
		~HeapNode() {}
		// ������ ����, ���������� �� ������, ������� � ������ �������
		int key;
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
			// ���������� ������� �������
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
	// ��������� �������
	struct HeapNode	{
		HeapNode() : leftChild( nullptr ), rightChild( nullptr ) {} 
		HeapNode( int element ) : key( element ), leftChild( nullptr ), rightChild( nullptr ) {}
		~HeapNode() {}
		// ������ ����, ���������� �� ������, ������� � ������ �������
		int key;
		HeapNode* leftChild;
		HeapNode* rightChild;
	};
	HeapNode* head;

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
			std::swap( node1->leftChild, node1->rightChild );
			// ���������� ������� �������
			return node1;
		}
};
*/