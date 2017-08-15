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
	1. 首先定位到相关的叶节点，删除信息
	2. 如果当前的叶节点关键数满足大于T个，直接删除后，若是处于叶节点的最小值或者最大值，则向上更新搜索节点处的信息，进行替换
	3. 如果当前的叶节点删除后关键数小于T-1个，如果兄弟节点关键字数大于T个，则从兄弟结点处获得一个关键字，向上更新搜索节点处信息，
	4. 如果兄弟节点关键字数为T-1个，这两兄弟合并为一个叶节点，向上更新搜索节点信息（此时具体为删除搜索结点的某一个key值，可以直接调用原来btree的judge函数）
- 其他
	- 编写的时候一开始没有关注到相同的关键字怎么处理，后来稍微修改后基本满足，但是还是存在着一个bug，如图，判断6的位置会默认为3，同时可能存在一些未发现的问题。

![bug](http://i.imgur.com/UqCBbpL.png)



# 插入用例结果图 #

![插入树状图片](http://i.imgur.com/zTdCbZg.png)
![插入测试代码](http://i.imgur.com/a7C4NBz.png)


# 删除用例结果图 #
![删除测试代码](http://i.imgur.com/vzfsjhV.png)
![](http://i.imgur.com/CtA72Hb.png)
![](http://i.imgur.com/BjCmEBb.png)
![](http://i.imgur.com/sWhojJv.png)
![](http://i.imgur.com/vbFjiFE.png)
![](http://i.imgur.com/jMd5ckt.png)

![](http://i.imgur.com/x4HOOoI.png)