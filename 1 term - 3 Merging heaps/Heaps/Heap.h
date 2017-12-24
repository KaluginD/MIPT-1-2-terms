#pragma once
// ��������� �������� ����������� ���������� ������� � ������ ��������� �����������
// �.�. ����� �eld() ������ ��������� ������ ���� Heap, � ���������� ������ �� ���,
// ����� ������� ����� ������ ���� ����� ����������������� � ���� Heap,
// � � ������ ���������� �eld() - ������� (��� �������������� � ������� dynamic_cast )
class Heap {
public:
	virtual ~Heap() {}
	virtual void Insert( int key ) = 0;
	virtual int ExtractMin() = 0;
	virtual void Meld( Heap* heapForMerge ) = 0;
};