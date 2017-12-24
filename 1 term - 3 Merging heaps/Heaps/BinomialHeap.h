#pragma once
#include "Heap.h"

class BinomialHeap : public Heap {
public:
	BinomialHeap();
	explicit BinomialHeap( int element );
	~BinomialHeap();

	virtual void Insert( int key );
	virtual void Meld( Heap* heapForMerge );
	virtual int ExtractMin();
	bool isEmpty() const;

protected:
	// ��������� �������
	struct HeapNode {
		HeapNode() {
			key = 0;
			child = nullptr;
			sibling = nullptr;
			degree  = 0;
		}
		explicit HeapNode( int element ) {
			key = element;
			child = nullptr;
			sibling = nullptr;
			degree = 0;
		}
		// ������ ����, �������, ��������� �� ��������, ������� ���� � ������ ����� 
		int key;
		HeapNode* child;
		HeapNode* sibling;
		int degree;
	};
	// ������ ������ ��������� �� ������
	HeapNode* head;
};