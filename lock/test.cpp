#include "test.h"
testclass * testclass::g_ptestclass = NULL;
string testclass::strCheck = "";
testclass * testclass::getTest()
{
	return g_ptestclass == NULL ? g_ptestclass = new testclass() : g_ptestclass;
}
static bool chect(std::string & str)
{
	return str.substr(0, str.find("2")) == "1111" && str.rfind("1") > 4;
}
testclass::testclass() : pthread1(NULL), pthread2(NULL)
{
	InitMtx(Mtx);
}
long testclass::startTest()
{
	beforeRet RET;
	if (!g_ptestclass)
	{
		return -1;
	}
	THREADPARA thread1para;
	thread1para.strDate = "1";
	thread1para.pUser = g_ptestclass;
	THREADPARA thread2para;
	thread2para.strDate = "2";
	thread2para.pUser = g_ptestclass;

	pthread1 = new Thread(testclass::g_ptestclass->threadFun, &thread1para);
	Sleep(1000);
	pthread2 = new Thread(testclass::g_ptestclass->threadFun, &thread2para);
	pthread1->join();
	pthread2->join();
	if (strCheck.compare("1111122222")!=0)
	{
		return RET("测试失败....");
	}
	return RET("测试成功！");
}
long testclass::startTestUl()
{
	beforeRet RET;
	if (!g_ptestclass)
	{
		return -1;
	}
	THREADPARA thread1para;
	thread1para.strDate = "1";
	thread1para.pUser = g_ptestclass;
	THREADPARA thread2para;
	thread2para.strDate = "2";
	thread2para.pUser = g_ptestclass;

	pthread1 = new Thread(testclass::g_ptestclass->threadFunTestul, &thread1para);
	Sleep(100);
	pthread2 = new Thread(testclass::g_ptestclass->threadFunTestul, &thread2para);
	pthread1->join();
	pthread2->join();
	if (!chect(strCheck))
	{
		return RET("测试失败....");
	}
	return RET("测试成功！");

}

long testclass::startTestCV()
{
	if (!g_ptestclass)
	{
		return -1;
	}
	THREADPARA thread1para;
	thread1para.strDate = "1";
	thread1para.pUser = g_ptestclass;
	THREADPARA thread2para;
	thread2para.strDate = "2";
	thread2para.pUser = g_ptestclass;
	pthread1 = new Thread(testclass::g_ptestclass->threadFunSignal, &thread1para);
	pthread2 = new Thread(testclass::g_ptestclass->threadFunWait, &thread2para);
	pthread1->join();
	pthread2->join();
	return 0;
}
unsigned  testclass::threadFun(void * para)
{
	PTHREADPARA p = (PTHREADPARA)para;
	testclass* pUser = (testclass*)p->pUser;
	if (!pUser)
	{
		return false;
	}
	lg lock(pUser->Mtx);
	for (int i = 0; i < 5; i++)
	{
		cout << p->strDate << endl;
		strCheck.append(p->strDate);
	}
	return 0;
}
unsigned  testclass::threadFunTestul(void * para)
{
	PTHREADPARA p = (PTHREADPARA)para;
	testclass* pUser = (testclass*)p->pUser;
	if (!pUser)
	{
		return false;
	}
	ul lock(pUser->Mtx);
	for (int i = 0; i < 4; i++)
	{
		cout << p->strDate << endl;
		strCheck.append(p->strDate);
	}
	lock.unlock();
	Sleep(100);
	cout << p->strDate << endl;
	strCheck.append(p->strDate);
	return 0;
}
unsigned  testclass::threadFunSignal(void * para)
{
	PTHREADPARA p = (PTHREADPARA)para;
	testclass* pUser = (testclass*)p->pUser;
	Sleep(4000);
	cout << "线程" << p->strDate << "发出信号，运算信息就位" << endl;
	ul lock(pUser->Mtx);
	pUser->m_date.signal = true;
	pUser->m_date.na = 2;
	pUser->m_date.nb = 3;
	pUser->m_cv.notify_one();
	return 0;
}

unsigned  testclass::threadFunWait(void * para)
{
	beforeRet RET;
	PTHREADPARA p = (PTHREADPARA)para;
	testclass* pUser = (testclass*)p->pUser;
	ul lock(pUser->Mtx);
	while (!pUser->m_date.signal)
	{
		cout << "线程" << p->strDate << "挂起，焦急等待运算信息" << endl;
		pUser->m_cv.wait(lock);
	}
	int result = 0;
	if ((result = pUser->m_date.na + pUser->m_date.nb) == 0 )
	{
		return RET("测试失败");
	}
	cout << "线程" << p->strDate << "被唤醒，计算结果:" << result << endl;
	Sleep(1000);
	
	return RET("测试成功");
}
