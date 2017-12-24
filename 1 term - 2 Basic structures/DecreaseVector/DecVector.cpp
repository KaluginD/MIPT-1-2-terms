#include "DecVector.h"
#include <assert.h>
#include <algorithm>
#include <stdio.h>

const int InitialSize = 16;

CVector::CVector() :
	bufferSize( InitialSize ),
	buffer( new int[bufferSize] ),
	vectorSize( 0 )
{
}

CVector::CVector( int size ) :
	bufferSize( size ),
	buffer( new int[bufferSize] ),
	vectorSize( 0 )
{
}

CVector::CVector( int size, int defValue ) :
	bufferSize( size ),
	buffer( new int[bufferSize] ),
	vectorSize( size )
{
	for(int i = 0; i < vectorSize; ++i ) {
		buffer[i] = defValue;
	}
}

CVector::~CVector()
{
	delete[] buffer;
}

void CVector::push_back( int element )
{
	if( bufferSize == vectorSize ){		// проверяем, не заполнен ли буффер
		grow();							// если заполнен, увеличиваем вектор
	}
	buffer[vectorSize] = element;
	++vectorSize;
}

int CVector::pop_back()
{
	assert( size() != 0 );				// проверяем, чтобы вектор был не пустой
	int element = buffer[--vectorSize];	
	// если вектор заполнен меньше, чем на четверть
	// и при уменьшении в два раза он будет больше InitialSize, уменьшаем раземер
	if( 4 * vectorSize <= bufferSize && 2 * InitialSize <= bufferSize ) {	
		decrease();
	}
	return element;
}

int& CVector::operator [] ( const int index )
{
	assert( vectorSize > index && index >= 0 );		//проверяем, чтобы идекс был в в диапазоне индексов
	return buffer[index]; 
}

const int& CVector::operator [] ( const int index ) const  
{
	assert( vectorSize > index && index >= 0 );		//проверяем, чтобы идекс был в в диапазоне индексов
	return buffer[index]; 
}

// увеличение вектора в 2 раза
void CVector::grow()
{
	int newBufferSize = std::max( 2 * bufferSize, InitialSize );
	int* newBuffer = new int[newBufferSize];
	if( bufferSize != 0 ){
		::memcpy( newBuffer, buffer, bufferSize * sizeof(int) );
	}
	delete buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}

// уменьшение вектора в 2 раза
void CVector::decrease()
{
	int newBufferSize = std::max( bufferSize / 2, InitialSize );
	int* newBuffer = new int[newBufferSize];
	for( int i = 0; i < vectorSize; i++ ) {
		newBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newBuffer;
	bufferSize = newBufferSize;
}