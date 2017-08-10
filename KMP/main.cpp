#include "BTree.h"
#include "KMP.h"
#include<iostream>
using namespace std;

int main()
{

	string str = "bbcabcdababcdabcdabde";
	string key = "abcdabd";

	cout << KMP(str, key);
	system("pause");
	return 0;
}
