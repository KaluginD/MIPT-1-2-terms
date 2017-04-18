#include <iostream>
#include <assert.h>

// ��������� �������������
struct Rect {
	int width;			// ������
	int height;		// ������
	int beginX;		// ��������� ���������� �� �

	Rect() {};
	Rect( int w, int h ) :  width( w ), height( h ) {};
};

// ���� ���������������
class RectStack {
public:
	// �����������
	RectStack( int size ) {
		buffer = new Rect[ size ];
		top = 0;
		maxSize = 0;
	}	 
	
	~RectStack() {
		delete[] buffer;
	}

	void addRect( Rect r ) {
		if ( top == 0 ) {		// ���� ���� ����, �� ��������� ������ �������������
			r.beginX = 0;
			maxSize = r.width * r.height;
			buffer[ top++ ] = r;
			return;
		}
		r.beginX = buffer[ top - 1 ].beginX + buffer[ top - 1 ].width;
		buffer[ top++ ] = r;
		if( r.height < buffer[ top - 2].height )	// ���� ������������� ���� �����������, 
			// ������ ������������� ������������ �������, �� ������������� �� ������ ������
			combineToMaxRect();
	}

	void combineToMaxRect ( ) {
		Rect r = buffer[ --top ];	// ������� ��������� �������������, ������� ���� �����������
		int endX = r.beginX + r.width;	// ���������� ��� ������� ����� ��  �  
		Rect prevRect = buffer[ --top ];	// ��������� �������������	
		int lastEndX = prevRect.beginX + prevRect.width;
		int lastRectSize = prevRect.width * prevRect.height;	// ������� ��������������, ������ ���������� 
		if( maxSize < lastRectSize )	// ���� ������ ������� - ��������������
			maxSize = lastRectSize;
		while( top > 0 && buffer[ top - 1 ].height > r.height ) {	// �������� �� ���������������, ������� ������ ���������� �����������
			prevRect = buffer[ --top ];	
			lastRectSize = ( lastEndX - prevRect.beginX ) * prevRect.height;	// ������� ������� ��������������� ��������������
			if( maxSize < lastRectSize )	// ���� ������ �������� - ���������
				maxSize = lastRectSize;
		}
		// ��������� � ���� �������������, ������ ���������� ����������� 
		int newRectBeginX = buffer[ top ].beginX;	
		Rect newRect( endX - newRectBeginX, r.height );
		newRect.beginX = newRectBeginX;
		buffer[ top++ ] = newRect;
	}

	int getMax() {
		// ����� �� ���������� ��������� ��������� ��������������, ��������� ������������� ������ 0
		addRect( Rect( 1, 0 ) );
		return maxSize;
	}

private:
	Rect* buffer;	// ������ ���������������
	int top;		// ����� ���������� ��������
	int maxSize;	// ������� ����������� ��������������
};


int main() {
	int n;
	std::cin >> n;
	RectStack stack(n);		// ������� ���� �� n ���������������
	for (int i = 0; i < n; ++i ) {
		int width = 0;
		int height = 0;
		std::cin >> width >> height;	
		stack.addRect( Rect( width, height ) );		// ��������� �������������� � ����
	}
	int answer = stack.getMax();	// ��������  �����
	std::cout << answer;
	return 0;
}