#include <iostream>
#include "vector.h"
using namespace std;

void fails(const string & msg)
{
	cout << msg.c_str() << "²âÊÔÊ§°Ü" << endl;
}

int main()
{
	vector vec(10);
	for (int i = 0; i < 10; i++)
	{
		vec[i] = i;
		if ((vec[i] = i) != i)
		{
			fails("²âÊÔÊ§°Ü");
		}
	}
	cout << "È«²¿²âÊÔsuccess\n";
	getchar();
	return 0;
}