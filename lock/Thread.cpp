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
		WaitForSingleObject(m_hThread, INFINITE);//m_hThreadΪ�߳̾����INFINITE���޵ȴ�
	}
	else {
		throw MyException("<�׳��쳣>���Ϊ��");//�׳��쳣������Ϊclass MyException
	}
}

void Thread::detach() {
	if (m_hThread != NULL) {
		m_hThread = NULL;
	}
}