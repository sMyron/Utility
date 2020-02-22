#include "Thread.h"
//#include <thread>
#include <iostream>
#include <string>
#include <windows.h>

#if defined _THREAD_
typedef std::thread Thread;
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
		pgUserdate->strdate = "线程数据hello";
		pgUserdate->pUser = this;
		Thread thread(threadfun, (void *)pgUserdate);
#if defined _THREAD_
		thread.detach();
#endif
	}
	void  m_threadfun(void * pUserdate)
	{
		PUserdate puserdate = (PUserdate)pUserdate;
		std::cout << puserdate->strdate << std::endl;
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
	while (1)
	{
		if (testclass::pgUserdate->bIsOk == true)
		{
			std::cout << "测试成功" << std::endl;
			break;
		}
		Sleep(1000);
	}
	delete testclass::pgUserdate;
	testclass::pgUserdate = NULL;
	getchar();
	return 0;
}
