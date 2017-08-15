#include"BPlusTree.h"
#include<iostream>
using namespace std;

pbtree_node BPlusTree::btree_node_new()
{
	pbtree_node pNode = new btree_node;
	if (NULL == pNode)
		return NULL;

	for (int i = 0; i < M; i++)
	{
		pNode->k[i] = 0;
	}

	for (int i = 0; i < M + 1; i++)
	{
		pNode->p[i] = NULL;
	}

	pNode->num = 0;
	pNode->next = pNode->parent = NULL;

	pNode->isleaf = false;

	return pNode;
}

pbtree_node BPlusTree::btree_create()
{
	if (NULL == this->root){
		root = btree_node_new();
		root->isleaf = true;
		root->parent = root;
		head = root;
		root->next = NULL;
	}
	return root;
}

void  BPlusTree::insert(int target)
{
	cout << "Insert " << target << endl;
	pbtree_node node = root;
	while (node->isleaf == false)//非叶节点，便利寻找下一个应该寻找的节点
	{
		bool flag = true;
		for (int i = 0; i < node->num; i++)
		{
			if (target <= node->k[i]){
				node = node->p[i];
				flag = false;
				break;
			}
		}
		if (flag){
			node = node->p[node->num];
		}
	}

	btree_node_insert(node, target, 0, 0);

}


/************  分裂分析   **************
*
*叶节点分裂和非叶节点分裂不同
*非叶节点的分裂可以直接调用BTree的分裂方式
*/


void BPlusTree::btree_split(pbtree_node node)
{
	if (node == root)//如果该叶节点是根节点
	{
		pbtree_node left = btree_node_new();
		pbtree_node right = btree_node_new();
		left->parent = right->parent = node;
		for (int i = 0; i < T - 1; i++)
		{
			left->k[i] = node->k[i];
			left->p[i] = node->p[i];
			right->k[i] = node->k[i + T];
			right->p[i] = node->p[i + T];
		}

		if (2 * T == M)//该树原来的M为偶数6,  6个关键key 7个叉  t=3  
		{
			left->p[T - 1] = node->p[T - 1];
			right->p[T - 1] = node->p[M - 1];
			right->k[T - 1] = node->k[2 * T - 1];
			right->p[T] = node->p[M];
			left->num = T - 1;
			right->num = T;
		}
		else{//该树原来的M为奇数,  5个关键key 6个叉  t=3  
			left->p[T - 1] = node->p[T - 1];
			right->p[T - 1] = node->p[M];
			left->num = right->num = T - 1;
		}
		node->k[0] = node->k[T - 1];
		node->p[0] = left;
		for (int i = 1; i < M; ++i)
		{
			node->k[i] = 0;
			node->p[i] = NULL;
		}
		node->p[node->num] = NULL;
		node->num = 1;
		node->p[1] = right;
		for (int b = 0; b <= left->num; b++)
			if (left->p[b] != NULL)left->p[b]->parent = left;
		for (int b = 0; b <= right->num; b++)
			if (right->p[b] != NULL)right->p[b]->parent = right;
	}
	else//如果是非跟节点
	{
		pbtree_node brother = btree_node_new();
		brother->parent = node->parent;
		for (int i = 0; i < (T - 1); ++i)
		{
			brother->k[i] = node->k[i + T];
			brother->p[i] = node->p[i + T];
			if (brother->p[i] != NULL)
				brother->p[i]->parent = brother;
			node->k[i + T] = 0;
			node->p[i + T] = NULL;
		}
		node->num = T - 1;
		if (2 * T == M)//该树原来的M为偶数6,  6个关键key 7个叉  t=3  
		{
			brother->k[T - 1] = node->k[2 * T - 1];
			brother->p[T - 1] = node->p[2 * T - 1];
			if (brother->p[T - 1] != NULL)
			{
				brother->p[T - 1]->parent = brother;
			}


			brother->p[T] = node->p[2 * T];
			if (brother->p[T] != NULL)
			{
				brother->p[T]->parent = brother;
			}
			node->k[2 * T - 1] = 0;
			node->p[2 * T - 1] = node->p[2 * T] = NULL;
			brother->num = T;

		}
		else //该树原来的M为奇数5， 5个关键key 6个叉 t=3 
		{
			brother->num = T - 1;
			brother->p[T - 1] = node->p[2 * T - 1];
			if (brother->p[T - 1] != NULL)
			{
				brother->p[T - 1]->parent = brother;
			}
			node->p[2 * T - 1] = 0;

		}
		int target = node->k[T - 1];
		node->k[T - 1] = 0;

		btree_node_insert(node->parent, target, node, brother);
	}
}

void BPlusTree::bplustree_split(pbtree_node node)
{
	if (node == root)//如果该叶节点是根节点
	{
		pbtree_node left = btree_node_new();
		pbtree_node right = btree_node_new();
		left->parent = right->parent = node;
		left->isleaf = right->isleaf = true;
		head = left;
		left->next = right;

		if (2 * T == M)//该树原来的M为偶数6,  6个关键key 7个叉  t=3  
		{
			for (int i = 0; i < T; ++i)
			{
				left->k[i] = node->k[i];
				right->k[i] = node->k[i + T];
			}
			left->num = right->num = T;
			node->k[0] = node->k[T];
		}
		else{//该树原来的M为奇数,  5个关键key 6个叉  t=3  
			for (int i = 0; i < T - 1; ++i)
			{
				left->k[i] = node->k[i];
				right->k[i] = node->k[i + T - 1];
			}
			right->k[T - 1] = node->k[2 * T - 2];
			right->num = T;
			left->num = T - 1;
			node->k[0] = node->k[T - 1];
		}
		node->p[0] = left;
		for (int i = 1; i < M; ++i)
		{
			node->k[i] = 0;
			node->p[i] = NULL;
		}
		node->p[node->num] = NULL;
		node->num = 1;
		node->p[1] = right;
		node->isleaf = false;
	}
	else//如果是非跟节点
	{
		pbtree_node brother = btree_node_new();
		brother->isleaf = true;
		brother->parent = node->parent;
		brother->next = node->next;
		node->next = brother;
		if (2 * T == M)//该树原来的M为偶数6,  6个关键key 7个叉  t=3  
		{
			for (int i = 0; i < T; ++i)
			{
				brother->k[i] = node->k[i + T];
				node->k[i + T] = 0;
			}
			brother->num = node->num = T;
		}
		else //该树原来的M为奇数5， 5个关键key 6个叉 t=3 
		{
			for (int i = 0; i < T; ++i)
			{
				brother->k[i] = node->k[i + T - 1];
				node->k[i + T - 1] = 0;
			}
			brother->num = T;
			node->num = T - 1;

		}
		int target = brother->k[0];

		btree_node_insert(node->parent, target, node, brother);
	}
}

void BPlusTree::btree_node_insert(pbtree_node node, int target, pbtree_node left, pbtree_node right)
{
	//叶节点非满，直接插入
	if (0 == node->num)//如果是最初始的空的跟节点
	{
		node->num = 1;
		node->k[0] = target;
		return;
	}
	int	i = node->num - 1;

	while (i >= 0 && target <= node->k[i])
	{
		node->k[i + 1] = node->k[i];
		--i;
	}
	if (-1 == i)
		node->k[0] = target;
	else
		node->k[i + 1] = target;
	node->num++;

	if (left != right)
	{

		if (-1 == i)
		{
			int temp = M;
			while (temp != 0){
				node->p[temp] = node->p[temp - 1];
				--temp;
			}
			node->p[0] = left;
			node->p[1] = right;
		}
		else
		{
			node->p[i + 1] = left;
			int temp = M;
			while (temp != i + 1)
			{
				node->p[temp] = node->p[temp - 1];
				--temp;
			}
			node->p[i + 2] = right;
		}
	}

	if (node->num == M)//叶节点满，向上分裂
	{
		if (node->isleaf)
			bplustree_split(node);
		else
			btree_split(node);
	}
}

/************  删除分析   **************
*
*首先定位到相关的叶节点，删除信息
*①如果当前的叶节点关键数满足大于T个，直接删除后，若是处于叶节点的最小值或者最大值，则向上更新搜索节点处的信息，进行替换
*②如果当前的叶节点删除后关键数小于T-1个，如果兄弟节点关键字数大于T个，则从兄弟结点处获得一个关键字，向上更新搜索节点处信息，
*如果兄弟节点关键字数为T-1个，这两兄弟合并为一个叶节点，向上更新搜索节点信息（此时具体为删除搜索结点的某一个key值，可以直接调用原来btree的judge函数）
*/

void BPlusTree::btree_judge(pbtree_node node)
{
	if (node->num >= T - 1 || node == root)
		return;
	//find its brothers ,if one of them could save it
	pbtree_node parent = node->parent;
	pbtree_node left_brother = NULL, right_brother = NULL;

	int i = 0;
	for (; i <= parent->num; ++i)
	{
		if (parent->p[i] == node)
		{
			if (i != 0)
				left_brother = parent->p[i - 1];
			if (i != parent->num)
				right_brother = parent->p[i + 1];
			break;
		}
	}
	if (left_brother != NULL&&left_brother->num >= T)
	{
		node->p[node->num + 1] = node->p[node->num];
		for (int q = node->num - 1; q >= 0; --q)
		{
			node->k[q + 1] = node->k[q];
			node->p[q + 1] = node->p[q];
		}
		node->k[0] = parent->k[i - 1];
		node->p[0] = left_brother->p[left_brother->num];
		parent->k[i - 1] = left_brother->k[left_brother->num - 1];
		left_brother->k[left_brother->num - 1] = 0;
		left_brother->p[left_brother->num] = NULL;
		--left_brother->num;
		++node->num;
	}
	else
		if (right_brother != NULL&&right_brother->num >= T)
		{
		node->p[node->num + 1] = right_brother->p[0];
		node->k[node->num] = parent->k[i];
		++node->num;
		parent->k[i] = right_brother->k[0];
		for (int q = 0; q < right_brother->num - 1; ++q)
		{
			right_brother->k[q] = right_brother->k[q + 1];
			right_brother->p[q] = right_brother->p[q + 1];
		}
		right_brother->p[right_brother->num - 1] = right_brother->p[right_brother->num];
		right_brother->k[right_brother->num - 1] = 0;
		right_brother->p[right_brother->num] = NULL;
		--right_brother->num;
		}
		else
		{
			if (left_brother == NULL){
				left_brother = node;
				node = right_brother;
				left_brother->k[left_brother->num] = parent->k[i];
			}
			else{
				left_brother->k[left_brother->num] = parent->k[--i];

			}

			for (int q = left_brother->num + 1; q < node->num + left_brother->num + 1; ++q)
			{
				left_brother->k[q] = node->k[q - left_brother->num - 1];
				left_brother->p[q] = node->p[q - left_brother->num - 1];
				left_brother->p[q] == NULL ? NULL : left_brother->p[q]->parent = left_brother;
			}
			left_brother->p[node->num + left_brother->num + 1] = node->p[node->num];
			left_brother->p[node->num + left_brother->num + 1] == NULL ? NULL : left_brother->p[node->num + left_brother->num + 1]->parent = left_brother;
			left_brother->num = node->num + left_brother->num + 1;

			for (int q = i; q < parent->num; q++){
				parent->k[q] = parent->k[q + 1];
				parent->p[q] = parent->p[q + 1];
			}
			parent->p[parent->num] = NULL;
			parent->k[parent->num - 1] = 0;
			parent->p[i] = left_brother;
			parent->num--;
			delete node;

			//不考虑一个关键字的B树
			if (0 == parent->num){
				root->num = left_brother->num;
				for (int i = 0; i < root->num; ++i)
					root->k[i] = left_brother->k[i];
				for (int i = 0; i <= root->num; ++i){
					root->p[i] = left_brother->p[i];
					root->p[i] == NULL ? NULL : root->p[i]->parent = root;
				}

				delete left_brother;
			}
			else
				btree_judge(parent);
		}

}

bool BPlusTree::Delete(int target)
{
	cout << "Delete " << target << endl;
	pbtree_node node = root;
	int pfind = -1;
	while (!node->isleaf)//非叶节点，便利寻找下一个应该寻找的节点
	{
		bool flag = true;
		for (int i = 0; i < node->num; i++)
		{
			if (target < node->k[i]){
				node = node->p[i];
				pfind = i;
				flag = false;
				break;
			}
		}
		if (flag){
			pfind = node->num;
			node = node->p[node->num];
		}
	}


	pbtree_node parent = node->parent, brother;
	//除了该叶节点在p[0]处，其他的叶节点兄弟设定为它的左兄弟
	if (pfind == 0) brother = parent->p[1];
	else
		brother = parent->p[pfind - 1];
	int kfind = -1;
	//先对node里面target值进行删除
	bool exist = false;
	for (int i = 0; i < node->num; ++i)
	{
		if (node->k[i] == target){
			kfind = i;
			exist = true;
		}
		if (kfind != -1)
			node->k[i] = node->k[i + 1];
	}
	if (!exist)
		return false;
	//此时只需更换搜索结点的信息
	if (node->num >= T || brother->num >= T){
		if (node->num >= T){//不需要从兄弟结点找节点
			--node->num;
			if (kfind != 0)
				return true;
			else
				bplustree_replace(parent, pfind-1,target, node->k[0]);
		}
		else
		{//node->num < T && brother->num >= T
			if (pfind == 0){
				node->k[node->num - 1] = brother->k[0];
				for (int i = 0; i < brother->num; ++i)
					brother->k[i] = brother->k[i + 1];
				--brother->num;
				if (0 == kfind)
					bplustree_replace(parent, pfind, target, node->k[0]);
				bplustree_replace(parent, pfind - 1, node->k[node->num - 1], brother->k[0]);
			}
			else{
				for (int i = node->num - 1; i >= 0; --i)
					node->k[i + 1] = node->k[i];
				node->k[0] = brother->k[brother->num - 1];
				brother->k[brother->num - 1] = 0;
				--brother->num;
				if (0 == kfind)
					bplustree_replace(parent, pfind-1 , target, node->k[0]);
				else
					bplustree_replace(parent, pfind - 1, node->k[1], node->k[0]);
			}
		}
	}
	else//需要删除搜索结点的信息
	{
		if (pfind == 0){
			for (int i = 0; i < brother->num; ++i)
				node->k[i + node->num - 1] = brother->k[i];
			node->num += (brother->num - 1);
			node->next = brother->next;
			for (int i = 0; i < parent->num; ++i)
			{
				parent->k[i] = parent->k[i + 1];
				parent->p[i] = parent->p[i + 1];
			}
			parent->p[parent->num] = NULL;
			parent->p[0] = node;
			--parent->num;
			delete brother;
			if (0 == kfind)
				bplustree_replace(parent, pfind, target, node->k[0]);
			if (parent == root&&root->num == 0){
				node->isleaf = true;
				delete root;
				root = head = node;
			}
			else
				btree_judge(parent);
		}
		else
		{
			for (int i = brother->num; i < brother->num + node->num - 1; ++i)
				brother->k[i] = node->k[i - brother->num];
			brother->num += (node->num - 1);
			brother->next = node->next;
			for (int i = pfind - 1; i < parent->num; ++i)
			{
				parent->k[i] = parent->k[i + 1];
				parent->p[i + 1] = parent->p[i + 2];
			}
			--parent->num;
			delete node;
			if (parent == root&&root->num == 0){
				brother->isleaf = true;
				delete root;
				root = head = brother;
			}
			else
				btree_judge(parent);
		}
	}
	return true;
}


void BPlusTree::bplustree_replace(pbtree_node node, int pfind, int find, int replace)
{
	for (int i = pfind; i < node->num; ++i)
	{
		if (node->k[i] == find){
			node->k[i] = replace;
			return;
		}
	}
	if (node == root)
		return;
	bplustree_replace(node->parent,0, find, replace);
}
void BPlusTree::level_display()
{
	// just for simplicty, can't exceed 200 nodes in the tree
	btree_node *queue[200] = { NULL };
	int front = 0;
	int rear = 0;

	queue[rear++] = root;

	while (front < rear) {
		btree_node *node = queue[front++];

		cout << "[";
		for (int i = 0; i < node->num; i++) {
			cout << node->k[i] << " ";
		}
		cout << "]";

		for (int i = 0; i <= node->num; i++) {
			if (NULL != node->p[i]) {
				queue[rear++] = node->p[i];
			}
		}
	}
	cout << endl;
	bplus_display();
}

void BPlusTree::bplus_display()
{
	pbtree_node node = head;
	while (node)
	{
		cout << "[";
		for (int i = 0; i < node->num; i++) {
			cout << node->k[i] << " ";
		}
		cout << "]";
		node = node->next;
	}
	cout << endl;
}
