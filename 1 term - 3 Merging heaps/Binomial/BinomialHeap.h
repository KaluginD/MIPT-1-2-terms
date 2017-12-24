class BinomialHeap {
private:
	struct Node {
		Node() {
			key = 0;
			parent = nullptr;
			child = nullptr;
			sibling = nullptr;
			degree  = 0;
		}
		explicit Node( int element ) {
			key = element;
			parent = nullptr;
			child = nullptr;
			sibling = nullptr;
			degree = 0;
		}
		// храним ключ, родителя, правого сына, левого брата и уровень
		int key;
		Node* parent;
		Node* child;
		Node* sibling;
		int degree;
	};
private:
	BinomialHeap();
	explicit BinomialHeap( int element);
	~BinomialHeap();
	// добавление ключа
	void Add( int key );
	// слияние куч
	void Merge( BinomialHeap* heapForMerge );
	// получить минимум
	int Minimum();
	// извлечь минимум
	int ExtractMin();
	// храним указатель на пустой корень, который ссылается на первое дерево
	Node* head;
};