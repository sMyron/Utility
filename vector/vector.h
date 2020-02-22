#pragma once
#include <iostream>// 全部头文件include，声明，预编译选项全部放在.h中，除了#include "vector.h"
using namespace std;

class vector
{
public:
	vector(const int input_size);// 声明为const保护传入的参数
	~vector();
	int size();
	void push_back(const int value);// 声明为const保护传入的参数
	void clear();
	int & operator[](const int & i) const;// 参数声明为const保护传入参数，声明为应用提高效率，因为为读，成员函数声明为const保护成员变量
private:
	size_t input_size;// 大小是非负，一般用size_t表示，注意类型检查
	size_t m_size;// 大小是非负，一般用size_t表示，注意类型检查
	int* m_Array;
	int* dilateTemp;
};

