#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <cmath>

const int inf = 1e+6;

class SparseTable {
public:
	SparseTable( std::vector< int > &keys );
	~SparseTable() {}

	void GetStat( int left, int right );
private:
	// храним пару индексов 1 и 2 статистик
	std::vector< std::vector< std::pair< int, int > > > table;
	std::vector< int > arr;
	std::vector< int > logs;
};
// заполнение тальицы
SparseTable::SparseTable( std::vector< int > &keys ) {
	logs.assign( keys.size() + 1, 0 );
	for( int i = 1; i <= keys.size(); ++i ) {
		logs[i] = log ( i ) / log( 2 );
		arr.push_back( keys[i - 1] );
	}
	std::vector< std::pair< int, int > > tmp;
	tmp.assign( logs[keys.size()] + 1, std::make_pair(0, 0) );
	table.assign( keys.size() + 2, tmp );

	for( int i = 0; i < keys.size(); ++i )
		table[i][0] = std::make_pair( i, i );
	for( int j = 1; j <= logs[keys.size()]; ++j ) {
		for( int i = 0; i + pow( 2, j ) <= keys.size(); ++i ) {
			// у нас есть 4 индекса - сорируем их по элементам, на которые они указывают 
			std::vector< int > stats;
			stats.push_back( table[i][j - 1].first );
			stats.push_back( table[i][j - 1].second );
			stats.push_back( table[i + pow( 2, j - 1 )][j - 1].first );
			stats.push_back( table[i + pow( 2, j - 1 )][j - 1].second );
			if( arr[stats[0]] > arr[stats[1]] )
				std::swap( stats[0], stats[1] );

			if( arr[stats[1]] > arr[stats[2]] )
				std::swap( stats[1], stats[2] );
			if( arr[stats[0]] > arr[stats[1]] )
				std::swap( stats[0], stats[1] );

			if( arr[stats[2]] > arr[stats[3]] )
				std::swap( stats[2], stats[3] );
			if( arr[stats[1]] > arr[stats[2]] )
				std::swap( stats[1], stats[2] );
			if( arr[stats[0]] > arr[stats[1]] )
				std::swap( stats[0], stats[1] );
			// берем первый из не равных первому индекс
			int min1 = stats[0];
			int min2 = stats[1];
			if ( min1 == min2 )
				min2 = stats[2];
			if ( min1 == min2 )
				min2 = stats[3];
			table[i][j] = std::make_pair( min1, min2 );
		}
	}
}
// поиск 2 статистики
void SparseTable::GetStat( int left, int right ) {
	// аналогично заполнению
	int k = logs[right - left + 1];
	std::vector< int > stats;
	stats.push_back( table[left][k].first );
	stats.push_back( table[left][k].second );
	stats.push_back( table[right - pow( 2, k ) + 1][k].first );
	stats.push_back( table[right - pow( 2, k ) + 1][k].second );
	if( arr[stats[0]] > arr[stats[1]] )
		std::swap( stats[0], stats[1] );

	if( arr[stats[1]] > arr[stats[2]] )
		std::swap( stats[1], stats[2] );
	if( arr[stats[0]] > arr[stats[1]] )
		std::swap( stats[0], stats[1] );

	if( arr[stats[2]] > arr[stats[3]] )
		std::swap( stats[2], stats[3] );
	if( arr[stats[1]] > arr[stats[2]] )
		std::swap( stats[1], stats[2] );
	if( arr[stats[0]] > arr[stats[1]] )
		std::swap( stats[0], stats[1] );
	int min1 = stats[0];
	int min2 = stats[1];
	if ( min1 == min2 )
		min2 = stats[2];
	if ( min1 == min2 )
		min2 = stats[3];
	std::cout << arr[ min2 ] << std::endl;
}

int main() {
	int N = 0;
	int M = 0;
	std::cin >> N >> M;
	std::vector< int > arr;
	for( int i = 0; i < N; ++i ) {
		int element;
		std::cin >> element;
		arr.push_back( element );
	}
	SparseTable sparseTable( arr );
	int left = 0;
	int right = 0;
	for( int i = 0; i < M; ++i ) {
		std::cin >> left >> right;
		if( left == right )
			std::cout << arr[left] << std::endl;
		else
			sparseTable.GetStat( left - 1, right - 1 );
	}
	system( "pause" );
	return 0;
}