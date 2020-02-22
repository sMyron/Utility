#pragma once
#include <iostream>
//#include <thread>
#include <process.h>
#include <Windows.h>
using namespace std;

typedef unsigned(_stdcall* ThreadFunPtr)(void*);
class Thread {
public:
	Thread(ThreadFunPtr PFunc, void * PPram);
	void join();
	void detach();
    
private:
	void* m_hThread;
};

class MyException {
public:
	const char * m_pmsg;//���峣�����վ����쳣����char
	MyException(const char * msg) {
		m_pmsg = NULL;
		m_pmsg = msg;
	}
	const char * what()const noexcept {
		return  m_pmsg;
	};
};