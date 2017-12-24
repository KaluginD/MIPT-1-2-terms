#pragma once
#include <algorithm>

class LeftistHeap {
private:
	// ��������� �������
	struct HeapNode	{
		HeapNode() : dist( 0 ), leftChild( nullptr ), rightChild( nullptr ) {} 
		explicit HeapNode( int element ) : key( element ), dist( 1 ), leftChild( nullptr ), rightChild( nullptr ) {}
		// ������ ����, ���������� �� ������, ������� � ������ �������
		int key;	
		int dist;
		HeapNode* leftChild;
		HeapNode* rightChild;
	};
	// ������� ������
	HeapNode* Meld( HeapNode* node1, HeapNode* node2 ) {
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
		node1->rightChild = Meld( node1->rightChild, node2 );
		// ��������������� �������� ������������� ����, ���� ����������
		if( ( node1->leftChild == nullptr ) || ( node1->leftChild->dist < node1->rightChild->dist ) ) {
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
public:
	// ����������� �� ���������
	LeftistHeap();
	// ����������� �� ��������� ������� ��������
	explicit LeftistHeap( int element );
	~LeftistHeap();
	// ���������� ��������
	void Add( int element );
	// ������� ���
	void Merge( LeftistHeap* heapForMerge );
	// �������� �������
	int GetMin();
	// ������� �������
	int ExtractMin();

	HeapNode* head;
};