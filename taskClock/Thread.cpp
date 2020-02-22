#include "Thread.h"


Thread::Thread(ThreadFunPtr PFunc, void * PPram) {
	//m_hThread = NULL;
	if (PFunc)
	{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, PFunc, PPram, 0, NULL);
	}
}

void Thread::join() {
	if (m_hThread != NULL) {
		WaitForSingleObject(m_hThread, INFINITE);//m_hThread为线程句柄，INFINITE无限等待
	}
	else {
		throw MyException("<抛出异常>句柄为空");//抛出异常，类型为class MyException
	}
}

void Thread::detach() {
	if (m_hThread != NULL) {
		m_hThread = NULL;
	}
}