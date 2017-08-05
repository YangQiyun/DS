#include "BTree.h"
#include<iostream>
using namespace std;

int main()
{
	BTree bt;
	int arr[] = {1,3,7,14,8,5,11,17,13,6,23,12,20,26,4,16,18,24,25,19};
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        bt.insert(arr[i]);
    }
    bt.level_display();
    system("pause");
    return 0;
}
