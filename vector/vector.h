#pragma once
#include <iostream>// ȫ��ͷ�ļ�include��������Ԥ����ѡ��ȫ������.h�У�����#include "vector.h"
using namespace std;

class vector
{
public:
	vector(const int input_size);// ����Ϊconst��������Ĳ���
	~vector();
	int size();
	void push_back(const int value);// ����Ϊconst��������Ĳ���
	void clear();
	int & operator[](const int & i) const;// ��������Ϊconst�����������������ΪӦ�����Ч�ʣ���ΪΪ������Ա��������Ϊconst������Ա����
private:
	size_t input_size;// ��С�ǷǸ���һ����size_t��ʾ��ע�����ͼ��
	size_t m_size;// ��С�ǷǸ���һ����size_t��ʾ��ע�����ͼ��
	int* m_Array;
	int* dilateTemp;
};

