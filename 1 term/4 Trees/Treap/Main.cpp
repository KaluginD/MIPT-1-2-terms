#include <iostream>
#include <utility>
#include <queue>
#include <algorithm>

class Treap {
	struct CTreapNode {
		CTreapNode() {}
		CTreapNode( std::pair< int, int > element ) :
			key( element.first ),
			priority( element.second ),
			leftChild( 0 ),
			rightChild( 0 )
		{}

		int key;
		int priority;
		CTreapNode* leftChild;
		CTreapNode* rightChild;
	};

public:
	Treap();
	Treap( std::pair< int, int > element ); 
	~Treap();
	void Insert( std::pair< int, int > element );
	int GetDepth( CTreapNode* node );
	CTreapNode* GetHead(); 

private:
	CTreapNode* head;

	void Split( CTreapNode* treap, int key, CTreapNode *&treap1, CTreapNode *&treap2 );
};

Treap::Treap() {
	head = new CTreapNode();
}

Treap::Treap( std::pair< int, int > element ) {
	head = new CTreapNode( element );
}

Treap::~Treap() {
	std::queue< CTreapNode* > queue;
	queue.push( head );
	while( !queue.empty() ) {
		CTreapNode* node = queue.front();
		queue.pop();
		if( node != NULL ) {
			if( node->leftChild != NULL )
				queue.push( node->leftChild );
			if( node->rightChild != NULL )
				queue.push( node->rightChild );
			delete node;
		}
	}
}

void Treap::Split( CTreapNode* treap, int key, CTreapNode *&treap1, CTreapNode *&treap2 ) {
	if( treap == NULL ) {
		treap1 = NULL;
		treap2 = NULL;
		return;
	}
	if( treap->key < key ) {
		Split( treap->rightChild, key, treap->rightChild, treap2 );
		treap1 = treap;
		return;
	}
	else {
		Split( treap->leftChild, key, treap1, treap->leftChild );
		treap2 = treap;
	}
}

// спускаемся по дереву поиска, пока приоретет больше
// разрезаем по текущему ключу
// подвешиваем полученые деревья к текущей вершине
void Treap::Insert( std::pair< int, int > element ) {
	CTreapNode* parrentNow = NULL;
	CTreapNode* headNow = head;
	while( headNow != NULL && element.second < headNow->priority ) {
		if( headNow->key < element.first ) {
			parrentNow = headNow;
			headNow = headNow->rightChild;
		}
		else {
			parrentNow = headNow;
			headNow = headNow->leftChild;
		}
	}
	CTreapNode* treap1 = nullptr;
	CTreapNode* treap2 = nullptr;
	Split( headNow, element.first, treap1, treap2 );
	CTreapNode* nodeForInsert = new CTreapNode( element );
	nodeForInsert->leftChild = treap1;
	nodeForInsert->rightChild = treap2;
	if( parrentNow == NULL ) {
		head = nodeForInsert;
		return;
	}
	if( parrentNow->key < element.first ) {
		parrentNow->rightChild = nodeForInsert;
	}
	else {
		parrentNow->leftChild = nodeForInsert;
	}
}

int Treap::GetDepth( CTreapNode* node ) {
	if( node == NULL )
		return 0;
	return std::max( GetDepth( node->leftChild ), GetDepth( node->rightChild ) ) + 1;
}

Treap::CTreapNode* Treap::GetHead() {
	return head;
}

class NaiveTree {
	struct CNaiveNode {
		CNaiveNode() :
			key( 0 ),
			leftChild( 0 ),
			rightChild( 0 )
		{}
		CNaiveNode( int element ) :
			key( element ),
			leftChild( 0 ),
			rightChild( 0 )
		{}
		int key;
		CNaiveNode* leftChild;
		CNaiveNode* rightChild;
	};
public:
	NaiveTree();
	NaiveTree( int key );
	~NaiveTree();
	void Insert( int key );
	int GetDepth( CNaiveNode* node );
	CNaiveNode* GetHead();

private:
	CNaiveNode* head;
};

NaiveTree::NaiveTree() {
	head = new CNaiveNode();
}

NaiveTree::NaiveTree( int key ) {
	head = new CNaiveNode( key );
}

NaiveTree::~NaiveTree() {
	std::queue< CNaiveNode* > queue;
	queue.push( head );
	while( !queue.empty() ) {
		CNaiveNode* node = queue.front();
		queue.pop();
		if( node->leftChild != NULL )
			queue.push( node->leftChild );
		if( node->rightChild != NULL )
			queue.push( node->rightChild );
		delete node;
	}
}

void NaiveTree::Insert( int key ) {
	CNaiveNode* parrentNow = NULL;
	CNaiveNode* headNow = head;
	while( headNow != NULL ) {
		if( headNow->key < key ) {
			parrentNow = headNow;
			headNow = headNow->rightChild;
		}
		else {
			parrentNow = headNow;
			headNow = headNow->leftChild;
		}
	}
	if( parrentNow->key < key )
		parrentNow->rightChild = new CNaiveNode( key );
	else
		parrentNow->leftChild = new CNaiveNode( key );
}

int  NaiveTree::GetDepth( CNaiveNode* node ) {
	if( node == NULL )
		return 0;
	return std::max( GetDepth( node->leftChild ), GetDepth( node->rightChild ) ) + 1;
}

NaiveTree::CNaiveNode* NaiveTree::GetHead() {
	return head;
}

int main() {
	int N;
	std::cin >> N;
	std::pair< int, int >* nodes = new std::pair< int, int >[N];
	std::cin >> nodes[0].first >> nodes[0].second;
	Treap treap( nodes[0] );
	NaiveTree naiveTree( nodes[0].first );
	for( int i = 1; i < N; ++i ) {
		std::cin >> nodes[i].first >> nodes[i].second;
		treap.Insert( nodes[i] );
		naiveTree.Insert( nodes[i].first );
	}
	int treapDepth = treap.GetDepth( treap.GetHead() );
	int naiveDepth = naiveTree.GetDepth( naiveTree.GetHead() );
	int difference = abs( treapDepth - naiveDepth );
	std::cout << difference << std::endl; 
	return 0;
}