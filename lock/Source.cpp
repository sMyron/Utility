#include "test.h"
int main()
{
	testclass * ptest = testclass::getTest();
	return ptest->startTestUl();//startTest()����lg��startTestUl()����ul�� startTestCV����cv��
}