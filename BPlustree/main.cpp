#include "BTree.h"
#include<iostream>
using namespace std;

int main()
{
	BTree bt;
	int arr[] = { 1,2,5,45,73,4,8,9,14,23,6,3 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		bt.insert(arr[i]);
	}
	bt.level_display();
	bt.Delete(6);
	bt.level_display();
	bt.Delete(9);
	bt.level_display();
	bt.Delete(2);
	bt.level_display();
	bt.Delete(3);
	bt.level_display();
	bt.Delete(23);
	bt.level_display();
	bt.Delete(8);
	bt.level_display();
	bt.Delete(5);
	bt.level_display();
	while (1){
		int a;
		cin >> a;
		bt.Delete(a);
		bt.level_display();
	}
	system("pause");
	return 0;
}
