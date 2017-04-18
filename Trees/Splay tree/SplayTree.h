#pragma once
#include <utility>

 
#include <iostream>
#include <vector>
#include <assert.h>
 
template< typename T, typename Comp = std::less< T > >
class SplayTree {
public:
    SplayTree() : 
		head( 0 )
	{}
// вставляем, как в наивное и вызвыаем сплей
    bool Insert( const T &key ) {
        Node* node = find( key );
        if ( node )
            return false;
 
        Node* newPlase = head; 
        Node* newParent = NULL; 
 
        while ( newPlase != NULL ) {
            newParent = newPlase;
            if ( comp( newPlase->key, key ) ) 
				newPlase = newPlase->right;
            else newPlase = newPlase->left;
        }
 
        newPlase = new Node(key);
        newPlase->parent = newParent;
 
        if ( newParent == NULL ) 
			head = newPlase;
        else if ( comp( newParent->key, newPlase->key ) )
            newParent->right = newPlase;
        else newParent->left = newPlase;
 
        Splay( newPlase ); 
        return true;
    }
// удаление как из обычного дерева поиска
    bool Remove( const T &key ) {
        Node* newPlase = find( key );
        if ( newPlase == NULL ) return false; 
 
        Splay( newPlase ); 
 
        if ( !newPlase->left ) 
			Replase( newPlase, newPlase->right );
        else if ( !newPlase->right ) 
			Replase( newPlase, newPlase->left );
        else {
            Node* min = findMin( newPlase->right );
            if ( min->parent != newPlase ) {
                Replase( min, min->right );
                min->right = newPlase->right;
                min->right->parent = min;
            }
            Replase( newPlase, min );
            min->left = newPlase->left;
            min->left->parent = min;
        }
 
        delete newPlase;
        return true;
    }
// обычный поиск по двоичному дереву поика
    bool Find( T key ) {
		Node* node = find( key );
        if ( node == 0 ) 
			return false;
//        Splay( node );
		return true;
    }
 
private:
	struct Node {
		Node( const T& element = T() ) : 
			left( 0 ),
            right( 0 ),
            parent( 0 ),
            key( element )
		{}
        Node* left;
		Node* right;
        Node* parent;
        T key;
    };
    Comp comp;
	Node* head;
 
    void LeftRotation( Node* node ) {
        Node* right = node->right;
 
        if ( right != NULL ) {
            node->right = right->left;
            if ( right->left )
                right->left->parent = node;
            right->parent = node->parent;
        }
 
        if ( node->parent == NULL )
            head = right;
        else if ( node == node->parent->left ) node->parent->left = right;
        else node->parent->right = right;
        if ( right != NULL )
            right->left = node;
        node->parent = right;
    }
 
    void RightRotation( Node* node ) {
        Node* left = node->left;
        if ( left != NULL ) {
            node->left = left->right;
            if ( left->right )
                left->right->parent = node;
            left->parent = node->parent;
        }
        if ( node->parent == NULL )
            head = left;
        else if ( node == node->parent->left )
            node->parent->left = left;
        else
            node->parent->right = left;
        if ( left != NULL )
            left->right = node;
        node->parent = left;
    }
 
    void Splay( Node* node ) {
        while ( node->parent != NULL ) {
            // Zig
            if ( node->parent->parent == NULL ) {
                if ( node->parent->left == node )
                    RightRotation( node->parent );
                else LeftRotation( node->parent );
            }
            // Zig-Zig left
            else if ( node->parent->left == node && node->parent->parent->left == node->parent ) {
                RightRotation( node->parent->parent );
                RightRotation( node->parent );
            }
            // Zig-Zig right
            else if ( node->parent->right == node && node->parent->parent->right == node->parent ) {
                LeftRotation( node->parent->parent );
                LeftRotation( node->parent );
            }
            // Zig-Zag
            else if ( node->parent->left == node && node->parent->parent->right == node->parent ) {
                RightRotation( node->parent );
                LeftRotation( node->parent );
            }
            else {
                LeftRotation( node->parent );
                RightRotation( node->parent );
            }
        }
    }
 
    void Replase(Node* first, Node* second) {
        if (!first->parent)
            head = second;
        else if (first == first->parent->left)
            first->parent->left = second;
        else
            first->parent->right = second;
        if (second)
            second->parent = first->parent;
    }
 
    Node* findMin( Node* node ) {
        while ( node->left ) node = node->left;
        return node;
    }

    Node* find( const T &key ) {
        Node* newPlase = head;
        while ( newPlase ) {
            if ( comp( newPlase->key, key ) ) newPlase = newPlase->right;
            else if ( comp( key, newPlase->key ) ) newPlase = newPlase->left;
            else return newPlase;
        }
        return 0;
    }
 
};

/*
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
		Node* Node = find( key );
		if( Node != nullptr )
			return false;
		Node = head;
		Node* parent = nullptr;
		while( Node != nullptr ) {
			parent = Node;
			if( comp( Node->key, key ) )
				Node = Node->right;
			else
				Node = Node->left;
		}
		Node = new Node( key );
		Node->parent = parent;
		if( parent == nullptr )
			head = Node;
		else 
			if( comp( parent->key, Node->key ) )
				parent->right = Node;
			else 
				parent->left = Node;
		Splay( Node );
		return true;
	}
	bool Remove( T key ) {
		Node* Node = find( key );
		if( Node == nullptr || comp( Node->key, key ) || comp( key, Node->key ) )
			return false;
		Splay( Node );
		Merge( Node->left, Node->right );
		return true;
	}
	bool Find( T key ) {
		if( find( key ) != nullptr )
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
		if( tree1 == nullptr ) {
			head = tree2;
			return;
		}
		Node* Node = tree1;
		while( Node->right != nullptr )
			Node = Node->right;
			Splay( Node );
			tree1 = Node;
			tree1->right = tree2;
			head = tree1;
	}
	void Splay( Node* Node ) {
		while( Node->parent != nullptr ) {
			// Zig
			if( Node->parent->parent == nullptr ) {
				if( Node->parent->left == Node )
					rotationRight( Node->parent );
				else
					rotationLeft( Node->parent );
				continue;
			}
			// Zig-Zig left
			if( Node->parent->left == Node && Node->parent->parent->left == Node->parent ) {
				rotationRight( Node->parent->parent );
				rotationRight( Node->parent );
				continue;
			}
			// Zig-Zig right
			if( Node->parent->right == Node && Node->parent->parent->right == Node->parent ) {
				rotationLeft( Node->parent->parent );
				rotationLeft( Node->parent );
				continue;
			}
			// Zig-Zag
			if( Node->parent->left == Node && Node->parent->parent->right == Node->parent ) {
				rotationRight( Node->parent );
				rotationLeft( Node->parent );
				continue;
			}
			else {
				rotationLeft( Node->parent );
				rotationRight( Node->parent );
			}
		}
	}

	void rotationLeft( Node* Node ) {
		Node*  right = Node->right;
		if( right != nullptr ) {
			Node->right = right->left;
			if( right->left != nullptr )
				right->left->parent = Node;
			right->parent = Node->parent;
		}
		if( Node->parent == nullptr )
			head = right;
		else
			if( Node == Node->parent->left )
				Node->parent->left = right;
			else
				Node->parent->right = right;
		if( right != nullptr )
			right->left = Node;		
		Node->parent = right;
	}
	void rotationRight( Node* Node ) {
		Node* left = Node->left;
		if( left != nullptr ) {
			Node->left = left->right;
			if( left->right != nullptr )
				left->right->parent = Node;
			left->parent = Node->parent;
		}
		if( Node->parent == nullptr )
			head = left;
		else
			if( Node == Node->parent->left)
				Node->parent->left = left;
			else 
				Node->parent->right = left;
		if( left != nullptr )
			left->right = Node;
		Node->parent = left;
	}
    Node* find(const T &key) {
        Node *z = head;
        while (z) {
            if (comp(z->key, key)) z = z->right;
            else if (comp(key, z->key)) z = z->left;
            else return z;
        }
        return 0;
    }
};
*/