#pragma once
// интерфейс содержит виртуальные объявления методов и пустую релизацию деструктора
// Т.к. метод Мeld() должен принимать объект типа Heap, в реальзации каждой из куч,
// перед вызовом этого метода кучи будут преобразовываться к типу Heap,
// а в начале реализации Мeld() - обратно (все преобразования с помощью dynamic_cast )
class Heap {
public:
	virtual ~Heap() {}
	virtual void Insert( int key ) = 0;
	virtual int ExtractMin() = 0;
	virtual void Meld( Heap* heapForMerge ) = 0;
};