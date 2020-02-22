#pragma once
#include <iostream>
#include <Windows.h>
#include <map>
#include <time.h>
#include "Thread.h"

using namespace std;
namespace UtilX {
using std::map;
using std::string;

class Time {
public:
	Time();
	int updateCurrentTime();
	int taskTime2sec(int taskDay, int taskHour, int taskMin, int taskSec);
private:
	struct tm m_tmTime;
	time_t m_tNow;
};

class taskClock:public Time {
	typedef unsigned(_stdcall *LPTaskFun)(void* lpPara);
	typedef struct _TASKELEM {
		LPTaskFun task;//任务函数指针
		int nTimeMark;//任务时间标志
		void* lpTaskPara;//任务函数参数
		_TASKELEM() :task(NULL), nTimeMark(0), lpTaskPara(NULL)  {}
		_TASKELEM(LPTaskFun _task, const int _nTimeMark, void* _lpTaskPara) :task(_task), nTimeMark(_nTimeMark), lpTaskPara(_lpTaskPara) {}
	}TASKELEM, *PTASKELEM;
	typedef map<int, TASKELEM> TaskMap;
public:
	taskClock();
	bool Init();
	bool AddTask(LPTaskFun lpTask, const int nDay, const int nHour, const int nMin, const int nSec, void* lpPara = NULL);
private:
    static unsigned _stdcall threadFun(void * pPara);
	void startATask();
	bool m_bInit;
	TaskMap m_mapTask;
	Thread* m_pThreadFun;
};
}//namespace Utilx