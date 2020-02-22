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
		pgUserdate->strdate = "线程数据hello";
		pgUserdate->pUser = this;
		Thread thread(threadfun, (void *)pgUserdate);
		std::cout << "主线程在等待（阻塞中）" << std::endl;
		thread.join();
	}
	void  m_threadfun(void * pUserdate)
	{
		PUserdate puserdate = (PUserdate)pUserdate;
		std::cout << puserdate->strdate << std::endl;
		for (int i = 0; i < 5; i++)
		{
			Sleep(1000);
			std::cout << "线程在玩，还没结束" << std::endl;
		}
		std::cout << "线程结束" << std::endl;
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
		std::cout << "测试失败, join汇集失败" << std::endl;
		getchar();
		return 0;
	}
	std::cout << "测试成功" << std::endl;
	delete testclass::pgUserdate;
	testclass::pgUserdate = NULL;
	getchar();
	return 0;
}
