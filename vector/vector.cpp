
#include "vector.h"// ����Include�൱�ڽ�ȫ��vector�Ķ������������ˣ���������Include���Ƕ������


vector::vector(const int input_size)
{
	m_Array = NULL;
	dilateTemp = NULL;// ָ���Ա��Ҫ�ڹ��캯����ָ����ʼֵ�������ڳ�ʼ���б���г�ʼ�����죨�����ѣ���ʼ���б���г�ʼ����
	m_size = input_size;
	m_Array = new int[m_size];
	for (size_t i = 0; i < m_size; i++) {
		*(m_Array + i) = i + 1;
	}
}

vector::~vector()
{
	delete m_Array;
	m_Array = NULL;
}

int vector::size() {
	cout << "the size of Vector is " << m_size << endl;
	return m_size;
}

void vector::push_back(const int value) {
	if (m_size < input_size) {
		*(m_Array + m_size - 1) = value;
	}
	else {
		dilateTemp = new int[1];
		*(dilateTemp) = value;
		*(m_Array + m_size - 1) = *(dilateTemp);
	}
}

void vector::clear() {
	for (size_t i = 0; i < m_size; i++) {
		*(m_Array + i) = NULL;
	}
	m_size = 0;
}

int & vector::operator[](const int & i) const {
	return *(m_Array + i);
}