#pragma once
#include <iostream>
//#include <thread>
#include <process.h>
#include <windows.h>

class lg {
public:
	lg(CRITICAL_SECTION &Temp);//参数为临界区对象
	~lg();
private://私有化禁止拷贝
	lg(const lg&);//复制构造函数
	lg& operator= (const lg&);//复制赋值运算符
private:
	CRITICAL_SECTION* m_ptr;
};