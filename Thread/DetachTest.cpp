//#include <thread>
#include <iostream>
#include <string>
#include <windows.h>

#if defined _THREAD_
typedef std::thread Thread;
typedef std::exception MyException;
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
		gUserdate.strdate = "线程数据hello";
		gUserdate.pUser = this;
		Thread thread(threadfun, (void *)&gUserdate);
		thread.detach();
		std::cout << "线程分离" << std::endl;
		try
		{
			thread.join();
		}
		catch (MyException & e)
		{
			std::cout << e.what() << std::endl;
		}
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
	static Userdate gUserdate;
};
Userdate testclass::gUserdate;
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
	if (testclass::gUserdate.bIsOk == true)
	{
		std::cout << "线程分离失败" << std::endl;
		getchar();
		return 0;
	}
	std::cout << "线程分离成功, 测试成功" << std::endl;
	getchar();
	return 0;
}
