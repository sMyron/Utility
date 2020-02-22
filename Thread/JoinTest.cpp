//#include <thread>
#include <iostream>
#include <string>
#include <windows.h>

#if defined _THREAD_

typedef std::thread Thread;
#else
#include "Thread.h"
#endif
typedef struct _Userdate
{
	std::string strdate;
	void * pUser;
	bool bIsOk;
	_Userdate() :strdate(""), pUser(NULL), bIsOk(false){}
}Userdate, *PUserdate;
unsigned _stdcall threadfun(void * pUserdate);
class testclass
{
public:
	void test()
	{
		pgUserdate = new Userdate();
		pgUserdate->strdate = "�߳�����hello";
		pgUserdate->pUser = this;
		Thread thread(threadfun, (void *)pgUserdate);
		std::cout << "���߳��ڵȴ��������У�" << std::endl;
		thread.join();
	}
	void  m_threadfun(void * pUserdate)
	{
		PUserdate puserdate = (PUserdate)pUserdate;
		std::cout << puserdate->strdate << std::endl;
		for (int i = 0; i < 5; i++)
		{
			Sleep(1000);
			std::cout << "�߳����棬��û����" << std::endl;
		}
		std::cout << "�߳̽���" << std::endl;
		puserdate->bIsOk = true;
	}
	static PUserdate pgUserdate;
};
PUserdate testclass::pgUserdate = NULL;
unsigned _stdcall threadfun(void * pUserdate)
{
	PUserdate puserdate = (PUserdate)pUserdate;
	testclass * puser = (testclass *)(puserdate->pUser);
	puser->m_threadfun(pUserdate);
	return 1;
}

int main()
{
	testclass test;
	test.test();
	if (testclass::pgUserdate->bIsOk != true)
	{
		std::cout << "����ʧ��, join�㼯ʧ��" << std::endl;
		getchar();
		return 0;
	}
	std::cout << "���Գɹ�" << std::endl;
	delete testclass::pgUserdate;
	testclass::pgUserdate = NULL;
	getchar();
	return 0;
}
