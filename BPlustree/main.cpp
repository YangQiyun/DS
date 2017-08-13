#include "BTree.h"
#include<iostream>
using namespace std;

int main()
{
	BTree bt;
	int arr[] = { 2,3,4,5,6,1,5,3 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		bt.insert(arr[i]);
	}
	bt.level_display();
	while (1){
		int a;
		cin >> a;
		bt.insert(a);
		bt.level_display();
	}
	system("pause");
	return 0;
}
