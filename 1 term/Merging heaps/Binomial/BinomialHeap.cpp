#include "BinomialHeap.h"
#include <queue>

BinomialHeap::BinomialHeap() {
	head = new Node();
}

BinomialHeap::BinomialHeap( int element ) {
	head = new Node();
	head->sibling = new Node( element );
}
// деструктор работает по принципу BFS 
BinomialHeap::~BinomialHeap() {
	std::queue< Node* > queue;
	queue.push( head );
	while( !queue.empty() ) {
		Node* top = queue.front();
		queue.pop();
		if( top != nullptr ) {
			if( top->child != nullptr )
				queue.push( top->child  );
			if( top->sibling != nullptr )
				queue.push( top->sibling );
			delete top;
		}
	}
}
// добавление клча - слияние с кучей с 1 ключем 
void BinomialHeap::Add( int key ) {
	BinomialHeap* heapForMerge = new BinomialHeap( key );
	Merge( heapForMerge );	 
}
// слияние двух куч. Сперва сливаем все деревья в одну кучу в порядке возрастания глубины
// потом проходим по полученой куче, если встречаем деревья одинаковой глубины, сливаем их в одно
void BinomialHeap::Merge( BinomialHeap* heap1 ) {
	// heap1 и heap2 - кучи, которые сливаются в текущую
	BinomialHeap* heap2 = new BinomialHeap();
	std::swap( head, heap2->head );
	// указатели на наше текущее положение в каждой из куч
	Node* headNow1 = heap1->head->sibling;
	Node* headNow2 = heap2->head->sibling;
	Node* headNow = head;
	// проверка на пустоту одной из куч
	if( headNow1 == nullptr ) {
		headNow->sibling = headNow2;
		return;
	}
	if( headNow2 == nullptr ) {
		headNow->sibling = headNow1;
		return;
	}
	// сливаем деревья из обеих куч в одну
	// 1 приоритет - глубина дерева (сперва меньшие), 2 приоритет - ключи (спева меньшие)
	while( headNow1 != nullptr && headNow2 != nullptr ) {
		if( headNow1->degree < headNow2->degree || 
		  ( headNow1->degree == headNow2->degree &&  headNow1->key < headNow2->key ) ) {
			headNow->sibling = headNow1;
			headNow1 = headNow1->sibling;
		}
		else
		if( headNow2->degree < headNow1->degree || 
		  ( headNow2->degree == headNow1->degree && headNow2->key < headNow1->key ) ) {
			headNow->sibling = headNow2;
			headNow2 = headNow2->sibling;
		}
		headNow = headNow->sibling;
	}
	// т.к. одна из куч зкончится раньше, досливаем другую
	while( headNow1 != nullptr ) {
		headNow->sibling = headNow1;
		headNow = headNow->sibling;
		headNow1 = headNow1->sibling;
	}
	while( headNow2 != nullptr ) {
		headNow->sibling = headNow2;
		headNow = headNow->sibling;
		headNow2 = headNow2->sibling; 
	}
	// проходимся по полученой куче и сливаем деревья равного размера 
	headNow = head->sibling;
	while( headNow != nullptr && headNow->sibling != nullptr ) {
		// если нашли деревья одинаковой глубины
		if( headNow->degree == headNow->sibling->degree ) {
			// справа должно быть дерево с меньшим корнем
			if( headNow->key > headNow->sibling->key ) {
				Node* sibling = headNow->sibling;
				std::swap( headNow->sibling, headNow->sibling->sibling );
				std::swap( *headNow, *sibling );
			}
			// подвешиваем второе дерево в сыновья первого и переопределяем брата первого дерева
			Node* next = headNow->sibling->sibling;

			headNow->sibling->sibling = headNow->child;
			headNow->sibling->parent = headNow;
			++headNow->degree;
			headNow->child = headNow->sibling;

			headNow->sibling = next;
		}
		headNow = headNow->sibling;
	}

}
// для поиска минимума пробегаемся по корням деревьев
int BinomialHeap::Minimum() {
	Node* headNow = head->sibling;
	int min = headNow->key;
	while( headNow->sibling != nullptr ) {
		if( headNow->key < min ){
			min = headNow->key;
		}
		headNow = headNow->sibling;
	}
	return min;
}
// извлечение минимума. Находим  минимум, извлекаем его и сливаем оставшуюся кучу с кучей из детей извлеченного дерева
int BinomialHeap::ExtractMin() {
	// сперва находим дерево, предшествующее дереву  с минимумом(для переопределения его брата)
	int min = head->sibling->key;
	Node* headNow = head;
	Node* nodeWithMin = headNow; 
	while( headNow->sibling != nullptr ) {
		if( headNow->sibling->key < min ){
			min = headNow->sibling->key;
			nodeWithMin = headNow;
		}
		headNow = headNow->sibling;
	}
	// создаем кучу детей дерева с минимумом, которую сольем с оставшейся кучей
	BinomialHeap* heapForMerge = new BinomialHeap();
	Node* nodeForMegre = nodeWithMin->sibling->child;
	// теперь у сына этой вершины нет родителя
	if( nodeWithMin->sibling->child != nullptr )
		nodeWithMin->sibling->child->parent = nullptr;
	nodeWithMin->sibling = nodeWithMin->sibling->sibling;
	headNow = heapForMerge->head;
	// записываем в кучу всех детей дерева с минимумом
	while( nodeForMegre != nullptr ) {
		headNow->sibling = nodeForMegre;
		headNow = headNow->sibling;
		nodeForMegre = nodeForMegre->sibling;
	}
	Merge( heapForMerge );
	return min;
}
