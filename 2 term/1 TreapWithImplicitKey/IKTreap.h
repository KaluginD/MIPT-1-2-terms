#pragma once

#include <algorithm>

class IKTreap {
	struct TreapNode {
		TreapNode();
		TreapNode( int newKey, int newPriority ) {
			key = newKey;
			priority = newPriority;
			C = 1;
			leftChild = nullptr;
			rightChild = nullptr;

			sum = newKey;
			
			leftmost = newKey;
			rightmost = newKey;
			deferredReverse = false;
			prefix = 1;
			suffix = 1;
		};
		~TreapNode() {
			delete leftChild;
			delete rightChild;
		};

		int key;	// ����
		int priority;	// ���������
		int C;	// ���-�� ��-�� � ���������
		TreapNode* leftChild;
		TreapNode* rightChild;

		int sum;	// ����� � ���������

		int leftmost;	// �������� ������ ������ ��-�� � ���������
		int rightmost;	// �������� ������ ������� ��-�� � ���������
		bool deferredReverse;	// ��������� ��������
		int prefix;	// ������ �������� ������������� ��������
		int suffix;	// ������ �������� ���������� ���������
	};
public:
	IKTreap();
	IKTreap( int key, int priority );
	~IKTreap();
	int Sum( int l, int r );	// ����� �� ����������
	void Push( int index, int newKey );	// ���������� � i-�� �������
	void Assign( int index, int newKey );	// ���������� i-��� ��-��
	bool NextPermutation( int l, int r );
//	void write();

private:
	TreapNode* head;	// ��������� �� ������
	static void preUpdate( TreapNode* node );	// ���������� ����������� ���������
	static void postUpdate( TreapNode* node );	// ���������� ���� ��������������� �������
	static void split( TreapNode* nodeForSplit, int number, TreapNode*& left, TreapNode*& right );	// ��������� number ��-��
	static void keySplit( TreapNode* nodeForSplit, int splitKey, TreapNode*& left, TreapNode*& right );	// ���������� �������� ���������� ��������� �� �����
	static TreapNode* Merge( TreapNode* left, TreapNode* right );	// �������
	static int LeftSonSize( TreapNode* node );	// ���-�� ��-�� � ��������� ������ ����
	int MAX_PRIORITY;	// ������������ ���������
	static void inOrder( TreapNode* node );
};
// CHECKING COMMENT