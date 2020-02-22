#include "lg.h"

lg::lg(CRITICAL_SECTION &Temp) {//引用Temp接收传入的CRITICAL_SECTION类型的参数
	m_ptr = &Temp;//取Temp的首地址赋值给成员指针m_ptr
	EnterCriticalSection(m_ptr);//指针作为函数输入
}

lg::~lg() {
	LeaveCriticalSection(m_ptr);//指针作为函数输入
}