#include "lg.h"

lg::lg(CRITICAL_SECTION &Temp) {//����Temp���մ����CRITICAL_SECTION���͵Ĳ���
	m_ptr = &Temp;//ȡTemp���׵�ַ��ֵ����Աָ��m_ptr
	EnterCriticalSection(m_ptr);//ָ����Ϊ��������
}

lg::~lg() {
	LeaveCriticalSection(m_ptr);//ָ����Ϊ��������
}