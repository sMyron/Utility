#include "cv.h"

void cv::wait(ul &objLock){
	objLock.unlock();
	m_hHandle = CreateEvent(NULL, false, false, NULL);
	WaitForSingleObject(m_hHandle,INFINITE);

}

void cv::notify_one() {
	SetEvent(m_hHandle);//����һ��boolֵ
}