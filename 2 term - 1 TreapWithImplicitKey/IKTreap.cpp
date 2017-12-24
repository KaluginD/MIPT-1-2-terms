#pragma once

#include "IKTreap.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

IKTreap::IKTreap() {
	MAX_PRIORITY = 1e+6;
	head = nullptr;
}

IKTreap::IKTreap( int key, int priority ) {
	MAX_PRIORITY = 1e+6;
	head = new TreapNode( key, priority );
};

IKTreap::~IKTreap() {
	delete head;
};

// �������� ������ ��������� - ����� ���������� - � ����� ����� �� ���������
// ������� ����� - ������� �������
int IKTreap::Sum( int l, int r ) {
	TreapNode* right;
	TreapNode* left1;
	split( head, r + 1, left1, right );
	TreapNode* left;
	TreapNode* sumNode;
	split( left1, l, left, sumNode );
	int sum = sumNode->sum;
	left1 = Merge( left, sumNode );
	head = Merge( left1, right );
	return sum;
};

// �������� ������ ���-�� ��-��, ������ � ���� ������ � ������� �� ������ ��-��
void IKTreap::Push( int index, int newKey ) {
	if( head == nullptr ) {
		head = new TreapNode( newKey, rand() % MAX_PRIORITY );
		return;
	}

	TreapNode* left = nullptr;
	TreapNode* right = nullptr;
	split( head, index, left, right );

	TreapNode* nodeForInsert = new TreapNode( newKey, rand() % MAX_PRIORITY );
	TreapNode* newLeft = Merge( left, nodeForInsert );
	head = Merge( newLeft, right );
};

// �������� ������ ��-�, ���������, ������� �������
void IKTreap::Assign( int index, int newKey ) {
	TreapNode* right;
	TreapNode* left1;
	split( head, index + 1, left1, right);
	TreapNode* left;
	TreapNode * mid;
	split(left1, index, left, mid );
	mid->key = newKey;
	postUpdate(mid);
	left1 = Merge(left, mid);
	head = Merge(left1, right);

};

bool IKTreap::NextPermutation( int l, int r ) {
	// �������� ������, � ������� ����� ������� nextPerm
	TreapNode* right;
	TreapNode* left1;
	split( head, r + 1, left1, right);
	TreapNode* left;
	TreapNode * mid;
	split(left1, l, left, mid );
	bool ans = true;
	// ���� ��������� - �� ������������ - ��������� ����������� - ������������� ���
	if( mid->suffix == mid->C ) {
		mid->deferredReverse = !mid->deferredReverse;
		ans = false;
	} else {   // �����
		// �������� ��������
		TreapNode* postfix;
		TreapNode* unPostfix;
		split( mid, mid->C - mid->suffix, unPostfix, postfix );
		// ������� ����� ���������� - �����
		TreapNode* pivot;
		split(unPostfix, unPostfix->C - 1, unPostfix, pivot);
		// ��������� �������� �� ����� ������
		TreapNode* leftPostfix;
		TreapNode* rightPostfix;
		keySplit( postfix, pivot->key, leftPostfix, rightPostfix );
		// �������� �������, ������� ������ ������� � �������
		TreapNode* swapPivot;
		split( leftPostfix, leftPostfix->C - 1, leftPostfix, swapPivot );
		std::swap( pivot, swapPivot );	// ������ ����� � ������ ��-�� �������
		// ������� ��� �������
		leftPostfix = Merge( leftPostfix, swapPivot );
		postfix = Merge( leftPostfix, rightPostfix );
		postfix->deferredReverse = !postfix->deferredReverse;	// �������� - �������������
		unPostfix = Merge( unPostfix, pivot );
		mid = Merge( unPostfix, postfix );
	}
	// ������� ��������� �������
	postUpdate(mid);
	left1 = Merge(left, mid);
	head = Merge(left1, right);
	return ans;
};

// ��������� ���������� �������� - ������ ������� �����,
// ����� ������ � ����� ����� ��������, ������� � �������
void IKTreap::preUpdate( TreapNode* node ) {
	if( node == nullptr )
		return;
	if( node->deferredReverse ) {
		std::swap(node->leftChild, node->rightChild);
		std::swap(node->leftmost, node->rightmost);
		std::swap(node->prefix, node->suffix);
		
		if(node->leftChild != nullptr) {
			node->leftChild->deferredReverse = !node->leftChild->deferredReverse;
		}
		if(node->rightChild != nullptr) {
			node->rightChild->deferredReverse = !node->rightChild->deferredReverse;
		}
		node->deferredReverse = false;
	}
};

//  ���������� ���� ��������������� ������� ����� ��������� �������
void IKTreap::postUpdate( TreapNode* node ) {
	if( node == nullptr )
		return;
	// ��������� ���������� ��������� � ������� � �����
	preUpdate( node );
	preUpdate(node->leftChild);
	preUpdate(node->rightChild);
	// ��������� ���� ��� ����� �����
	node->C = 1;
	node->sum = node->key;
	node->leftmost = node->key;
	node->rightmost = node->key;
	node->prefix = 1;
	node->suffix = 1;
	// ��������� ����, ��������� � ����� ��������
	if( node->leftChild != nullptr ) {
		node->C += node->leftChild->C;
		node->sum += node->leftChild->sum;

		node->prefix = node->leftChild->prefix;
		node->leftmost = node->leftChild->leftmost;
		if( node->leftChild->C == node->leftChild->prefix && node->leftChild->rightmost <= node->key ) 
			++node->prefix;
	}
	// ��������� ���������� ��������
	if( node->rightChild != nullptr && node->prefix == node->C - node->rightChild->C
		&& node->key <= node->rightChild->leftmost )
		node->prefix += node->rightChild->prefix;
	// ��������� ����, ��������� � ������ ��������	 
	if( node->rightChild != nullptr ) {
		node->C += node->rightChild->C;
		node->sum += node->rightChild->sum;

		node->suffix = node->rightChild->suffix;
		node->rightmost = node->rightChild->rightmost;
		if( node->rightChild->C == node->rightChild->suffix && node->rightChild->leftmost <= node->key ) 
			++node->suffix;
	}
	// ��������� ���������� ��������
	if( node->leftChild != nullptr && node->suffix == node->C - node->leftChild->C 
		&& node->key <= node->leftChild->rightmost )
		node->suffix += node->leftChild->suffix;

};

// �������� �������� ���-�� ��-���
void IKTreap::split( TreapNode* nodeForSplit, int number, TreapNode*& left, TreapNode*& right ) {
	if( nodeForSplit == nullptr) {
		left = nullptr;
		right = nullptr;
		return;
	}
	
    preUpdate( nodeForSplit );

	int leftkey = LeftSonSize( nodeForSplit );

	if( leftkey >= number ) {
		split( nodeForSplit->leftChild, number, left, nodeForSplit->leftChild );
		right = nodeForSplit;
		postUpdate( right );
		postUpdate( left );
	} else {
		split( nodeForSplit->rightChild, number - leftkey - 1, nodeForSplit->rightChild, right );
		left = nodeForSplit;
		postUpdate( left );
		postUpdate( right );
	}
};

// ������� ��� ���������, ��� � ������� ���-�� ������
IKTreap::TreapNode* IKTreap::Merge( TreapNode* left, TreapNode* right ) {
	if( left == nullptr )
		return right;
	if( right == nullptr )
		return left;

	if( left->priority > right->priority ) {
		preUpdate(left);
		left->rightChild = Merge( left->rightChild, right );
		postUpdate( left );
		return left;
	} else {
		preUpdate(right);
		right->leftChild = Merge( left, right->leftChild );
		postUpdate( right );
		return right;
	}
};

// �� ������������ �������� - ������� ���. ������ �� ������. ��� ����� ��������� �� �����
void IKTreap::keySplit( TreapNode* nodeForSplit, int splitKey, TreapNode*& left, TreapNode*& right ) {
	if( nodeForSplit == nullptr ) {
		left = nullptr;
		right = nullptr;
		return;
	}
	preUpdate( nodeForSplit );
	if ( nodeForSplit->key > splitKey ) {
		keySplit( nodeForSplit->rightChild, splitKey, nodeForSplit->rightChild, right );
		left = nodeForSplit;
		postUpdate( left );
		postUpdate( right );
		return;
	} else {
		keySplit( nodeForSplit->leftChild, splitKey, left, nodeForSplit->leftChild );
		right = nodeForSplit;
		postUpdate( left );
		postUpdate( right );
	}

};

void IKTreap::inOrder( TreapNode* node ) {
	if( node == nullptr )
		return;
	inOrder( node->leftChild );
	std::cout << node->key << " ";
	inOrder( node->rightChild );
}
/*
void IKTreap::write() {
	std::cout << "treapArray:  ";
	inOrder( head );
	std::cout << std::endl;
};
*/ 
int IKTreap::LeftSonSize( TreapNode* node ) {
	if( node->leftChild == nullptr ) 
		return 0;
	return node->leftChild->C;
};