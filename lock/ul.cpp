#include "ul.h"
using namespace std;

ul::ul(CRITICAL_SECTION &Temp) {
	m_ptr = &Temp;
	EnterCriticalSection(m_ptr);
	lockFlag = TRUE;
}

void ul::unlock() {
	if (lockFlag = TRUE) {
		LeaveCriticalSection(m_ptr);
		lockFlag = FALSE;
	}
	else {
		cout << "���̴߳�ǰδ����";
	}
}

ul::~ul() {
	if (lockFlag = TRUE) {
		LeaveCriticalSection(m_ptr);
	}
	else { NULL; }
}
