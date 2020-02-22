#include "taskClock.h"
using namespace std;
using namespace UtilX;

void taskFun() {
	time_t Now = 0;
	struct tm x;
	time(&Now);
	localtime_s(&x, &Now);
	cout << "任务执行时间：" << x.tm_mday << "日" << x.tm_hour << ":" << x.tm_min << ":" << x.tm_sec << endl;
}
unsigned _stdcall threadTaskFun(void* lpPara) {
	taskFun();
	return 0;
}
int main() {
	taskClock taskclockmap;
	if (!taskclockmap.Init()) {
		return 0;
	}
	taskclockmap.AddTask(threadTaskFun, 22, 14, 43, 10);//函数指针，日，时，分，秒，
	taskclockmap.AddTask(threadTaskFun, 29, 2, 31, 40);
	taskclockmap.AddTask(threadTaskFun, 29, 2, 31, 41);
	taskclockmap.AddTask(threadTaskFun, 29, 2, 31, 42);
	taskclockmap.AddTask(threadTaskFun, 29, 2, 31, 43);
	getchar();
	return 0;
}
