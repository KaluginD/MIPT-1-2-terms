#include <utility>
#include <iostream>
#include <string>
#include <assert.h>

template< typename T, typename Comp = std::less< T > >
class SplayTree {
public:
	SplayTree() :
		head( 0 )
	{}
	SplayTree( T element ) {
		head = new  Node( element );
	}
	~SplayTree() {
	}

	bool Insert( T key ) {
		Node* node = find( key );
		if( node != NULL )
			return false;
		node = head;
		Node* parent = NULL;
		while( node != NULL ) {
			parent = node;
			if( comp( node->key, key ) )
				node = node->right;
			else
				node = node->left;
		}
		node = new Node( key );
		node->parent = parent;
		if( parent == NULL )
			head = node;
		else 
			if( comp( parent->key, node->key ) )
				parent->right = node;
			else 
				parent->left = node;
		Splay( node );
		return true;
	}
	bool Remove( T key ) {
		Node* newPlase = find(key);
        if (newPlase == NULL)
			return false; 
 
        Splay(newPlase); 
 
        if (!newPlase->left) { 
			Replase(newPlase, newPlase->right);
			return true;
		}
        if (!newPlase->right) {
			Replase(newPlase, newPlase->left);
			return true;
		}
   		Node* min = minimum(newPlase->right);
        if (min->parent != newPlase) {
			Replase(min, min->right);
		    min->right = newPlase->right;
	        min->right->parent = min;
		}
		Replase(newPlase, min);
		min->left = newPlase->left;
		min->left->parent = min;
        delete newPlase;
        return true;
	}
	bool Find( T key ) {
		if( find( key ) != NULL )
			return true;
		return false;
	}
private:
	struct Node {
		Node( const T& element = T() ) :
			key( element ),
			left( 0 ),
			right( 0 ),
			parent( 0 )
		{}

		T key;
		Node* left;
		Node* right;
		Node* parent;
	};
	Node* head;
	Comp comp;

	void Merge( Node* tree1, Node* tree2 ) {
		if( tree1 == NULL ) {
			head = tree2;
			return;
		}
		Node* node = tree1;
		while( node->right != NULL )
			node = node->right;
			Splay( node );
			tree1 = node;
			tree1->right = tree2;
			head = tree1;
	}
	void Splay( Node* node ) {
		while( node->parent != NULL ) {
			// Zig
			if( node->parent->parent == NULL ) {
				if( node->parent->left == node )
					rotationRight( node->parent );
				else
					rotationLeft( node->parent );
				continue;
			}
			// Zig-Zig left
			if( node->parent->left == node && node->parent->parent->left == node->parent ) {
				rotationRight( node->parent->parent );
				rotationRight( node->parent );
				continue;
			}
			// Zig-Zig right
			if( node->parent->right == node && node->parent->parent->right == node->parent ) {
				rotationLeft( node->parent->parent );
				rotationLeft( node->parent );
				continue;
			}
			// Zig-Zag
			if( node->parent->left == node && node->parent->parent->right == node->parent ) {
				rotationRight( node->parent );
				rotationLeft( node->parent );
				continue;
			}
			else {
				rotationLeft( node->parent );
				rotationRight( node->parent );
			}
		}
	}

	void Replase( Node* first, Node* second ) {
		if( first->parent == NULL )  {
			head = second;
			return;
		}
		if( first == first->parent->left )
			first->parent->left = second;
		else
			first->parent->right = second;
		if( second != NULL )
			second->parent = first->parent;

	}
	Node* minimum( Node* node ) {
		if( node->left == NULL )
			return node;
		return minimum( node->left );
	}

	void rotationLeft( Node* node ) {
		Node*  right = node->right;
		if( right != NULL ) {
			node->right = right->left;
			if( right->left != NULL )
				right->left->parent = node;
			right->parent = node->parent;
		}
		if( node->parent == NULL )
			head = right;
		else
			if( node == node->parent->left )
				node->parent->left = right;
			else
				node->parent->right = right;
		if( right != NULL )
			right->left = node;		
		node->parent = right;
	}
	void rotationRight( Node* node ) {
		Node* left = node->left;
		if( left != NULL ) {
			node->left = left->right;
			if( left->right != NULL )
				left->right->parent = node;
			left->parent = node->parent;
		}
		if( node->parent == NULL )
			head = left;
		else
			if( node == node->parent->left)
				node->parent->left = left;
			else 
				node->parent->right = left;
		if( left != NULL )
			left->right = node;
		node->parent = left;
	}
    Node* find( const T &key ) {
        Node* node = head;
        while ( node != NULL ) {
            if ( comp( node->key, key ) ) 
				node = node->right;
            else if ( comp( key, node->key ) ) 
				node = node->left;
			else return node;
        }
        return 0;
    }
};


int main() {
	SplayTree< std::string > tree;
	while( true ) {
		char command;
		std::cin >> command;
		if( std::cin.eof() ){
			return 0;
		}
		std::string key;
		std::cin >> key;
		switch( command ) {
		case '?':
			std::cout << ( tree.Find( key ) ? "OK" : "FAIL" ) << std::endl;
			break;
		case '+':
			std::cout << ( tree.Insert(key) ? "OK" : "FAIL" ) << std::endl;
			break;
		case '-':
			std::cout << ( tree.Remove(key) ? "OK" : "FAIL" ) << std::endl;
			break;
		default:
			assert( false );
		}
	}
	system( "pause" );
	return 0;
}