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
		// ������ ����, ��������, ������� ����, ������ ����� � �������
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
	// ���������� �����
	void Add( int key );
	// ������� ���
	void Merge( BinomialHeap* heapForMerge );
	// �������� �������
	int Minimum();
	// ������� �������
	int ExtractMin();
	// ������ ��������� �� ������ ������, ������� ��������� �� ������ ������
	Node* head;
};