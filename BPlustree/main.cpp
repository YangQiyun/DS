#include "BPlusTree.h"
#include<iostream>
using namespace std;

int main()
{
	BPlusTree bt;
	int arr[] = { 6,2,7 ,45, 73,9, 14, 23, 1, 3 };
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
	bt.Delete(7);
	bt.level_display();
	bt.Delete(14);
	bt.level_display();
	bt.Delete(73);
	bt.level_display();
	bt.Delete(1);
	bt.level_display();
	system("pause");
	return 0;
}
