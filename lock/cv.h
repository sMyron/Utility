#pragma once
#include <iostream>
#include <windows.h>
#include "ul.h"

class cv {
public:
	void wait(ul &objLock);
	void notify_one();
private:
	void* m_hHandle;
	bool m_bSignal;
};