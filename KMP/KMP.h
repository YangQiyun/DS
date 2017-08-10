#ifndef KMP_H
#define KMP_H
#include <string>
using namespace std;



static int*  getfail(string key)
{
	int length=key.length();
	int *fail = new int[length]();

	int k = -1;
	int j = 0;
	fail[0] = -1;

	while (j<length-1)
	{
		if (k == -1 || key[j] == key[k])
		{
			if (key[j + 1] == key[k + 1])
				fail[++j] = fail[++k];
			else
			fail[++j] = ++k;
		}
		else
			k = fail[k];
	}

	return fail;
}

int KMP(string str,string key)
{
	int *fail = getfail(key);

	int i = 0, j = 0;
	while (i<int(str.size()) && j< int(key.size()))
	{
		if (j==-1||str[i] == key[j])
		{
			++i;
			++j;
		}
		else
		{
			j = fail[j];
		}
	}

	if (i == str.length() - 1 && j != key.length())
		return false;
	else
		return i - j;
}

#endif