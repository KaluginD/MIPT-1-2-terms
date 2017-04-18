#include <iostream>
#include <queue>

class AVLtree {
public:
	struct Node {
		Node( int element ) {
			key = element;
			left = NULL;
			right = NULL;
			degree = 1;
			childNumber = 1;
		}
		
		int key;
		int degree;
		int childNumber;
		Node* left;
		Node* right;
	};
	Node* head;

	AVLtree() {}
	AVLtree( int key ) {
		head = new Node( key );
	}
	~AVLtree() {
		std::queue< Node* > queue;
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
	}

	Node* Insert( Node* node, int key ) {
		if( node == NULL ) 
			return new Node( key );
		if( key < node->key )
			node->left =  Insert( node->left, key );
		else
			node->right = Insert( node->right, key );
		return Balance( node );
	}
	Node* Remove( Node* node, int key ) {
		if( node == NULL ) 
			return 0;
		if( key < node->key ) {
			node->left = Remove( node->left, key );
			return node;
		}
		else if( node->key < key ) {
			node->right = Remove( node->right, key );
			return node;
		}
		else {
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
	void FindStat( Node* node, int number ) {
		if( node == NULL )
			return;
		int stat = 1;
		if( node->left != NULL )
			stat += node->left->childNumber;
		if( stat == number ) {
			std::cout << node->key << std::endl;
			return;
		}
		if( number < stat ) {
			FindStat( node->left, number );
			return;
		}
		FindStat( node->right, number - stat );
	}

private:
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
		int childrenLeft = Children( node->left );
		int childrenRight = Children( node->right );
		node->childNumber = childrenLeft + childrenRight + 1;
	}
	int Degree( Node* node ) {
		if( node == NULL )
			return 0;
		return node->degree;
	}
	int Children( Node* node ) {
		if( node == NULL )
			return 0;
		return node->childNumber;
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

int main() {
	int N = 0;
	std::cin >> N;
	int key = 0;
	int stat = 0;
	std::cin >> key >> stat;
	AVLtree tree( key );
	tree.FindStat( tree.head, stat + 1 );
	while( --N > 0 ) {
		std::cin >> key >> stat;
		if( key > 0 ) {
			tree.head = tree.Insert( tree.head, key );
		}
		else {
			tree.head = tree.Remove( tree.head, -key );
		}
		tree.FindStat( tree.head, stat + 1 );
	}
	return 0;
}