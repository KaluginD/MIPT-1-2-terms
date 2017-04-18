#include "BinomialHeap.h"
#include <queue>

BinomialHeap::BinomialHeap() {
	head = new Node();
}

BinomialHeap::BinomialHeap( int element ) {
	head = new Node();
	head->sibling = new Node( element );
}
// ���������� �������� �� �������� BFS 
BinomialHeap::~BinomialHeap() {
	std::queue< Node* > queue;
	queue.push( head );
	while( !queue.empty() ) {
		Node* top = queue.front();
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
void BinomialHeap::Add( int key ) {
	BinomialHeap* heapForMerge = new BinomialHeap( key );
	Merge( heapForMerge );	 
}
// ������� ���� ���. ������ ������� ��� ������� � ���� ���� � ������� ����������� �������
// ����� �������� �� ��������� ����, ���� ��������� ������� ���������� �������, ������� �� � ����
void BinomialHeap::Merge( BinomialHeap* heap1 ) {
	// heap1 � heap2 - ����, ������� ��������� � �������
	BinomialHeap* heap2 = new BinomialHeap();
	std::swap( head, heap2->head );
	// ��������� �� ���� ������� ��������� � ������ �� ���
	Node* headNow1 = heap1->head->sibling;
	Node* headNow2 = heap2->head->sibling;
	Node* headNow = head;
	// �������� �� ������� ����� �� ���
	if( headNow1 == nullptr ) {
		headNow->sibling = headNow2;
		return;
	}
	if( headNow2 == nullptr ) {
		headNow->sibling = headNow1;
		return;
	}
	// ������� ������� �� ����� ��� � ����
	// 1 ��������� - ������� ������ (������ �������), 2 ��������� - ����� (����� �������)
	while( headNow1 != nullptr && headNow2 != nullptr ) {
		if( headNow1->degree < headNow2->degree || 
		  ( headNow1->degree == headNow2->degree &&  headNow1->key < headNow2->key ) ) {
			headNow->sibling = headNow1;
			headNow1 = headNow1->sibling;
		}
		else
		if( headNow2->degree < headNow1->degree || 
		  ( headNow2->degree == headNow1->degree && headNow2->key < headNow1->key ) ) {
			headNow->sibling = headNow2;
			headNow2 = headNow2->sibling;
		}
		headNow = headNow->sibling;
	}
	// �.�. ���� �� ��� ��������� ������, ��������� ������
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
	// ���������� �� ��������� ���� � ������� ������� ������� ������� 
	headNow = head->sibling;
	while( headNow != nullptr && headNow->sibling != nullptr ) {
		// ���� ����� ������� ���������� �������
		if( headNow->degree == headNow->sibling->degree ) {
			// ������ ������ ���� ������ � ������� ������
			if( headNow->key > headNow->sibling->key ) {
				Node* sibling = headNow->sibling;
				std::swap( headNow->sibling, headNow->sibling->sibling );
				std::swap( *headNow, *sibling );
			}
			// ����������� ������ ������ � ������� ������� � �������������� ����� ������� ������
			Node* next = headNow->sibling->sibling;

			headNow->sibling->sibling = headNow->child;
			headNow->sibling->parent = headNow;
			++headNow->degree;
			headNow->child = headNow->sibling;

			headNow->sibling = next;
		}
		headNow = headNow->sibling;
	}

}
// ��� ������ �������� ����������� �� ������ ��������
int BinomialHeap::Minimum() {
	Node* headNow = head->sibling;
	int min = headNow->key;
	while( headNow->sibling != nullptr ) {
		if( headNow->key < min ){
			min = headNow->key;
		}
		headNow = headNow->sibling;
	}
	return min;
}
// ���������� ��������. �������  �������, ��������� ��� � ������� ���������� ���� � ����� �� ����� ������������ ������
int BinomialHeap::ExtractMin() {
	// ������ ������� ������, �������������� ������  � ���������(��� ��������������� ��� �����)
	int min = head->sibling->key;
	Node* headNow = head;
	Node* nodeWithMin = headNow; 
	while( headNow->sibling != nullptr ) {
		if( headNow->sibling->key < min ){
			min = headNow->sibling->key;
			nodeWithMin = headNow;
		}
		headNow = headNow->sibling;
	}
	// ������� ���� ����� ������ � ���������, ������� ������ � ���������� �����
	BinomialHeap* heapForMerge = new BinomialHeap();
	Node* nodeForMegre = nodeWithMin->sibling->child;
	// ������ � ���� ���� ������� ��� ��������
	if( nodeWithMin->sibling->child != nullptr )
		nodeWithMin->sibling->child->parent = nullptr;
	nodeWithMin->sibling = nodeWithMin->sibling->sibling;
	headNow = heapForMerge->head;
	// ���������� � ���� ���� ����� ������ � ���������
	while( nodeForMegre != nullptr ) {
		headNow->sibling = nodeForMegre;
		headNow = headNow->sibling;
		nodeForMegre = nodeForMegre->sibling;
	}
	Merge( heapForMerge );
	return min;
}
