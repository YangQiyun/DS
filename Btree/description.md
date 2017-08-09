# Data-Structure-Btree

参考[B树和B+树的实现代码](https://github.com/orange1438/BTree-and-BPlusTree-Realize)，对于删除的做法还有
插入用例来自
http://taop.marchtea.com/03.02.html
!



- 节点结构为

		typedef struct btree_nodes
		{int k[M]；
		int num;
		pbtree_node p[M + 1];
		pbtree_node parent;
		}btree_node;




- 创建叶节点统一使用btree_node_new();
- 插入函数	void insert(int target);
	1. 找到合适的叶节点插入
	2. 如果叶节点满，则向上分裂，可能导致树增高
- 删除函数  bool Delete(int target);
	1. 遍历搜索，如果不存在则直接返回false
	2. 遍历搜索，定位到关键字的节点的时候，找到节点孩子的左节点的最大值或者右节点的最小值进行替换，接下来是删除叶节点处的替换的关键字
	3.	判断函数进行对叶节点的判断，如果关键字小于T-1
		- ①其兄弟可以提供一个关键字支持（此时兄弟关键字大于等于T），则通过旋转，从父结点转接一个关键字过来
		- ②若左右两兄弟都无法提供，则加上父节点对应的关键字合并，此时会影响父节点的个数，递归判断父节点
	4. 注意事项：
	当进行孩纸指针转移的时候，会产生父节点的更替，此时注意更新parent的信息


用例结果图
![](http://i.imgur.com/oiNP9QF.png)