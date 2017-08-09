#include "BTree.h"
#include<iostream>
using namespace std;

int main()
{
	BTree bt;
	int arr[] = { 1, 3, 7, 14, 8, 5, 11, 17, 13, 6, 23, 12, 20, 26, 4, 16, 18, 24, 25 ,19};
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		bt.insert(arr[i]);
	}
	bt.level_display();
	bt.Delete(int('H')-64);
	bt.level_display();
	bt.Delete(int('T')-64);
	bt.level_display();	
	bt.Delete(int('R')-64);
	bt.level_display();
	bt.Delete(int('E') - 64);
	bt.level_display();
	bt.Delete(int('Z') - 64);
	bt.level_display();
	bt.Delete(int('X') - 64);
	bt.level_display();
	bt.Delete(int('Y') - 64);
	bt.level_display();
	bt.Delete(int('A') - 64);
	bt.level_display();
	bt.Delete(int('K') - 64);
	bt.level_display();
	bt.Delete(int('N') - 64);
	bt.level_display();
	bt.Delete(int('C') - 64);
	bt.level_display();
	bt.Delete(int('L') - 64);
	bt.level_display();
	bt.Delete(int('M') - 64);
	bt.level_display();
	bt.Delete(int('P') - 64);
	bt.level_display();
	bt.Delete(int('F') - 64);
	bt.level_display();
	bt.Delete(int('G') - 64);
	bt.level_display();
	bt.Delete(int('S') - 64);
	bt.level_display();
	bt.Delete(int('W') - 64);
	bt.level_display();
	bt.insert(25);
	bt.level_display();
	bt.insert(12);
	bt.level_display();
	bt.insert(15);
	bt.level_display();
	system("pause");
	return 0;
}
