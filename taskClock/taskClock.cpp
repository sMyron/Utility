#include "taskClock.h"
UtilX::Time::Time() {
	m_tNow = 0;
}
int UtilX::Time::updateCurrentTime() {
	time(&m_tNow);
	localtime_s(&m_tmTime, &m_tNow);
	return  m_tmTime.tm_mday * 24 * 3600 + m_tmTime.tm_hour * 3600 + m_tmTime.tm_min * 60 + m_tmTime.tm_sec;
}
int UtilX::Time::taskTime2sec(int taskDay, int taskHour, int taskMin, int taskSec) {
	return taskDay * 24 * 60 * 60 + taskHour * 60 * 60 + taskMin * 60 + taskSec;
}

UtilX::taskClock::taskClock() {
	m_bInit = false;
	m_pThreadFun = NULL;
}
bool UtilX::taskClock::Init() {
	if (m_bInit) {
		return true;
	}
	if (!m_pThreadFun) {
		m_pThreadFun = new Thread(threadFun, this);
	}
	m_bInit = true;
	return true;
}
unsigned _stdcall UtilX::taskClock::threadFun(void * pPara) {
	taskClock* _pthis = (taskClock*)pPara;//强转类型
	_pthis->startATask();
	return 0;
}
void UtilX::taskClock::startATask() {
	while (!m_mapTask.empty()) {
		for (TaskMap::iterator it = m_mapTask.begin(); it != m_mapTask.end(); ++it) {
			if (updateCurrentTime() - it->first == 0) {
				m_pThreadFun = new Thread(it->second.task, this);
			}
			Sleep(200);
		}
	}
}

bool UtilX::taskClock::AddTask(LPTaskFun lpTask, const int nDay, const int nHour, const int nMin, const int nSec, void* lpPara) {
	if (!lpTask) {
		return false;
	}
	m_mapTask.insert(pair<int, TASKELEM>(taskTime2sec(nDay, nHour, nMin, nSec), TASKELEM(lpTask, taskTime2sec(nDay, nHour, nMin, nSec), lpPara)));//默认Key从小到大排序
}
