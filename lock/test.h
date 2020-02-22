#pragma once
// 取消以下两个开始测试标准C++11库
//#include <mutex>
//#include <thread>
//#include <condition_variable>

#include <iostream>
#include <string>
#include <windows.h>
#if defined(_MUTEX_)
typedef std::lock_guard<std::mutex> lg;
typedef std::unique_lock<std::mutex> ul;
typedef std::mutex MTX, *PMTX;
#define InitMtx(pMtx) 
#else
#include "lg.h"
#include "ul.h"
typedef CRITICAL_SECTION MTX, *PMTX;
#define InitMtx(Mtx)  ::InitializeCriticalSection(&Mtx)
#endif
#if defined(_THREAD_)
typedef std::thread Thread;
#else
#include "Thread.h"
#endif
#if defined(_CONDITION_VARIABLE_)
typedef std::condition_variable cv;
#else
#include "cv.h"
#endif

using std::cout;
using std::endl;
using std::string;
typedef struct _THREADPARA
{
	void * pUser;
	string  strDate;
	_THREADPARA() :pUser(NULL), strDate("") {}
}THREADPARA, *PTHREADPARA;
typedef struct _ASYDATE
{
	int na;
	int nb;
	bool signal;
	_ASYDATE() :na(0), nb(0), signal(false){}
}ASYDATE, *PASYDATE;
class testclass// singletion
{
	MTX Mtx;
	Thread * pthread1;
	Thread * pthread2;
	
	cv m_cv;
	ASYDATE m_date;
	static testclass * g_ptestclass;
	static string strCheck;
	testclass();
	static unsigned _stdcall threadFun(void *);
	static unsigned _stdcall threadFunWait(void *);
	static unsigned _stdcall threadFunSignal(void *);
	static unsigned _stdcall threadFunTestul(void *);

public:
	static testclass * getTest();
	long startTest();
	long startTestUl();
	long startTestCV();
};

class beforeRet// RAII
{
public:
	~beforeRet()
	{
		cout << m_msg << "测试结束, 按下任意键结束程序" << endl;
		getchar();
	}
	long operator()(const string & msg){ m_msg = msg; return 0; }
private:
	string m_msg;
};