#pragma once

#include <iostream>

template< typename T, typename Comp = std::less< T > >
class AVLtree {
public:
	AVLtree() :
		head( 0 )
	{}
	AVLtree( T element ) {
		head = new  Node( element );
	}
	~AVLtree() {
/*		std::queue< Node* > queue;
		queue.push( head );
		while( !queue.empty() ) {
			Node* top = queue.front();
			queue.pop();
			if( top->left != NULL )
				queue.push( top->left );
			if( top->right != NULL )
				queue.push( top->right );
			delete top;
		}
*/	}

	bool Insert( T key ) {
		Node* node = find( key );
		if ( node != nullptr ) 
			return false;
		head = insert( head, key );
		return true;
	}
	bool Remove( T key ) {
		Node* node = find( key );
		if( node == nullptr )
			return false;
		head = remove( head, key );
		return true;
	}
	bool Find( T key ) {
		Node* node = find( key );
		if( node != nullptr )
			return true;
		return false;
	}

private:
	struct Node {
		Node( const T& element = T() ) :
			key( element ),
			degree( 1 ), 
			left( 0 ),
			right( 0 )
		{}
		
		T key;
		int degree;
		Node* left;
		Node* right;
	};
	Comp comp;
	Node* head;

	Node* insert( Node* node, T key ) {
		if( node == NULL ) 
			return new Node( key );
		if( comp( key, node->key ) )
			node->left =  insert( node->left, key );
		else
			node->right = insert( node->right, key );
		return Balance( node );
	}
	Node* remove( Node* node, T key ) {
		if( node == NULL ) 
			return 0;
		if( comp( key, node->key ) ) {
			node->left = remove( node->left, key );
			return node;
		} else if( comp( node->key, key ) ) {
			node->right = remove( node->right, key );
			return node;
		} else {
			Node* left = node->left;
			Node* right = node->right;
			delete node;
			if( right == NULL )
				return left;
			Node* min = FindMin( right );
			min->right = RemoveMin( right );
			min->left = left;
			return Balance( min );
		}
	}
	Node* find( const T &key ) {
        Node* node = head;
        while ( node != nullptr ) {
            if ( comp( node->key, key ) ) 
				node = node->right;
            else 
				if ( comp( key, node->key ) ) 
					node = node->left;
				else return node;
        }
        return 0;
    }

	Node* Balance( Node* node ) {
		Fix( node );
		if( BalanceFactor( node ) == 2 ) {
			if( BalanceFactor( node->right ) < 0 )
				node->right = RightRotation( node->right );
			return LeftRotation( node );
		}
		if( BalanceFactor( node ) == -2 ) {
			if( BalanceFactor( node->left ) > 0 )
				node->left = LeftRotation( node->left );
			return RightRotation( node );
		}
		return node;
	}

	Node* RightRotation( Node* node ) {
		Node* left = node->left;
		node->left = left->right;
		left->right = node;
		Fix( node );
		Fix( left );
		return left;
	}
	Node* LeftRotation( Node* node ) {
		Node* right = node->right;
		node->right = right->left;
		right->left = node;
		Fix( node );
		Fix( right );
		return right;
	}

	void Fix( Node* node ) {
		int degreeLeft = Degree( node->left );
		int DegreeRight = Degree( node->right );
		node->degree = std::min( degreeLeft, DegreeRight ) + 1;
	}
	int Degree( Node* node ) {
		if( node == NULL )
			return 0;
		return node->degree;
	}
	int BalanceFactor( Node* node ) {
		return Degree( node->right ) - Degree( node->left );
	}

	Node* FindMin( Node* node ) {
		if( node->left == NULL )
			return node;
		return FindMin( node->left );
	}
	Node* RemoveMin( Node* node ) {
		if( node->left == NULL )
			return node->right;
		node->left = RemoveMin( node->left );
		return Balance( node );
	}
};