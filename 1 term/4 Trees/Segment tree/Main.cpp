#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

const int inf = 1e+6;

class SegmentTree {
public:
	SegmentTree( std::vector< int > &arr );
	void Update( int node, int left, int right, int pos, int sum );
	int FindMin( int node, int leftThis, int rightThis, int left, int right );
private:
	std::vector< int > tree;

	void Build( std::vector< int > &arr, int node, int left, int right );
};

SegmentTree::SegmentTree( std::vector< int > &arr ) {
	int k = 0;
	for( k = 1; k < 2 * arr.size(); k *= 2 ); 
	for( int i = 0; i < k; ++i )
		tree.push_back( inf );
	Build( arr, 0, 0, arr.size() - 1 );
}
// стрим дерево рекурсивно - сверху вниз
void SegmentTree::Build( std::vector< int > &arr, int node, int left, int  right ) {
	if( left == right ) {
		tree[ node ] = arr[left];
		return;
	}
	int middle = ( left + right ) / 2;
	Build( arr, node * 2 + 1, left, middle );
	Build( arr, node * 2 + 2, middle + 1, right );
	tree[node] = std::min( tree[node * 2 + 1], tree[node * 2 + 2] );
}
// обновление происходит поэлементно
void SegmentTree::Update( int node, int left, int right, int stat, int sum ) {
	if( left == right ) {
		tree[node] = sum;
		return;
	}
	int middle = ( left + right ) / 2;
	if( stat <= middle )
		Update( node * 2 + 1, left, middle, stat, sum );
	else 
		Update( node * 2 + 2, middle + 1, right, stat, sum );
	tree[node] = std::min( tree[node * 2 + 1], tree[node * 2 + 2] );
}
// поиск минимума в дереве отрезков
int SegmentTree::FindMin( int node, int leftThis, int rightThis, int left, int right ) {
	if( left > right ) 
		return inf;
	if( left == leftThis && right == rightThis )
		return tree[node];
	int middle = ( leftThis + rightThis ) / 2;
	return std::min( FindMin( node * 2 + 1, leftThis, middle, left, std::min( right, middle ) ),
			 		 FindMin( node * 2 + 2, middle + 1, rightThis, std::max( left, middle + 1), right ) );
}

int main() {
	int N = 0;
	std::cin >> N;
	std::vector< int > arr;
	int R = 0;
	int G = 0;
	int B = 0;
	for( int i = 0; i < N; ++i ) {
		std::cin >> R >> G >> B;
		arr.push_back( R + G + B );
	}
	SegmentTree tree( arr );
	int K;
	std::cin >> K;
	int C = 0;
	int D = 0;
	int E = 0;
	int F = 0;
	for( int i = 0; i < K; ++i ) {
		std::cin >> C >> D >> R >> G >> B >> E >> F;
		for( int j = C; j <= D; ++j )
			tree.Update( 0, 0, arr.size() - 1, j, R + G + B );
		std::cout << tree.FindMin( 0, 0, arr.size() - 1, E, F ) << std::endl;
	}
	return 0;
}