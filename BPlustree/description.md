# Data-Structure-BPlustree

参考[B+树动态演示](http://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)



- 节点结构为

		int k[M];
		int num;
		pbtree_node p[M + 1];
		pbtree_node parent;
		bool isleaf;
		pbtree_node next;




- 创建叶节点统一使用btree_node_new();
- 插入函数	void insert(int target);
	1. 找到叶节点插入
	2. 如果叶节点满，则向上分裂，可能导致树增高
	3. 分裂分为两种，一种是叶节点分裂，另一种普通节点分裂（直接用btree的分裂函数）
- 删除函数  bool Delete(int target);


插入用例结果图
![插入树状图片](http://i.imgur.com/zTdCbZg.png)
![插入测试代码](http://i.imgur.com/a7C4NBz.png)