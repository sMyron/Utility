#pragma once
#include <iostream>
//#include <thread>
#include <process.h>
#include <windows.h>

class lg {
public:
	lg(CRITICAL_SECTION &Temp);//����Ϊ�ٽ�������
	~lg();
private://˽�л���ֹ����
	lg(const lg&);//���ƹ��캯��
	lg& operator= (const lg&);//���Ƹ�ֵ�����
private:
	CRITICAL_SECTION* m_ptr;
};