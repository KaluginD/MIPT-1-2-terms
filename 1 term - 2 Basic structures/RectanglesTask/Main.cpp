#include <iostream>
#include <assert.h>

// структура пр€моугольник
struct Rect {
	int width;			// ширина
	int height;		// высота
	int beginX;		// начальна€ координата по ’

	Rect() {};
	Rect( int w, int h ) :  width( w ), height( h ) {};
};

// стек пр€моугольников
class RectStack {
public:
	// конструктор
	RectStack( int size ) {
		buffer = new Rect[ size ];
		top = 0;
		maxSize = 0;
	}	 
	
	~RectStack() {
		delete[] buffer;
	}

	void addRect( Rect r ) {
		if ( top == 0 ) {		// если стек пуст, то добавл€ем первый пр€моугольник
			r.beginX = 0;
			maxSize = r.width * r.height;
			buffer[ top++ ] = r;
			return;
		}
		r.beginX = buffer[ top - 1 ].beginX + buffer[ top - 1 ].width;
		buffer[ top++ ] = r;
		if( r.height < buffer[ top - 2].height )	// если пр€моугольник ниже предыдущего, 
			// найдем пр€моугольник максимальной площади, не превосход€щий по высоте данный
			combineToMaxRect();
	}

	void combineToMaxRect ( ) {
		Rect r = buffer[ --top ];	// достаем последний пр€моугольник, который ниже предыдущего
		int endX = r.beginX + r.width;	// координата его правого конца по  ’  
		Rect prevRect = buffer[ --top ];	// последний пр€моугольник	
		int lastEndX = prevRect.beginX + prevRect.width;
		int lastRectSize = prevRect.width * prevRect.height;	// площадь пр€моугольника, высоты последнего 
		if( maxSize < lastRectSize )	// если больше текущей - перезаписываем
			maxSize = lastRectSize;
		while( top > 0 && buffer[ top - 1 ].height > r.height ) {	// проходим по пр€моугольникам, которые невыше последнего добавленого
			prevRect = buffer[ --top ];	
			lastRectSize = ( lastEndX - prevRect.beginX ) * prevRect.height;	// находим площадь соответсвующего пр€моугольника
			if( maxSize < lastRectSize )	// если больше текущего - обновл€ем
				maxSize = lastRectSize;
		}
		// добавл€ем в стек пр€моугольник, высоты последнего добавленого 
		int newRectBeginX = buffer[ top ].beginX;	
		Rect newRect( endX - newRectBeginX, r.height );
		newRect.beginX = newRectBeginX;
		buffer[ top++ ] = newRect;
	}

	int getMax() {
		// чтобы не пропустить возможные последние пр€моугольники, добавл€ем пр€моугольник высоты 0
		addRect( Rect( 1, 0 ) );
		return maxSize;
	}

private:
	Rect* buffer;	// массив пр€моугольников
	int top;		// номер последнего элемента
	int maxSize;	// площадь наибольшего пр€моугольника
};


int main() {
	int n;
	std::cin >> n;
	RectStack stack(n);		// создаем стек на n пр€моугольников
	for (int i = 0; i < n; ++i ) {
		int width = 0;
		int height = 0;
		std::cin >> width >> height;	
		stack.addRect( Rect( width, height ) );		// добавл€ем пр€моугольники в стек
	}
	int answer = stack.getMax();	// поулчаем  ответ
	std::cout << answer;
	return 0;
}