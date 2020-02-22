#pragma once
#include <iostream>
#include <windows.h>

class ul {
public:
	ul(CRITICAL_SECTION &Temp);
	~ul();
	void unlock();
private:
	CRITICAL_SECTION * m_ptr;
	bool lockFlag;
};