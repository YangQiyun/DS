#include"BTree.h"
#include<iostream>
using namespace std;

pbtree_node BTree::btree_node_new()
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
	pNode->next =pNode->parent = NULL;

	pNode->isleaf = false;

	return pNode;
}

pbtree_node BTree::btree_create()
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

void  BTree::insert(int target)
{
	cout << "Insert " << target  << endl;
	pbtree_node node = root;
	while (node->isleaf==false)//非叶节点，便利寻找下一个应该寻找的节点
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


void BTree::btree_split(pbtree_node node)
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

void BTree::bplustree_split(pbtree_node node)
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
			for (int i = 0; i < T-1; ++i)
			{
				left->k[i] = node->k[i];
				right->k[i] = node->k[i + T-1];
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
				brother->k[i] = node->k[i+T];
				node->k[i + T] = 0;
			}
			brother->num=node->num = T;
		}
		else //该树原来的M为奇数5， 5个关键key 6个叉 t=3 
		{
			for (int i = 0; i < T; ++i)
			{
				brother->k[i] = node->k[i + T-1];
				node->k[i + T-1] = 0;
			}
			brother->num = T;
			node->num = T - 1;

		}
		int target = brother->k[0];

		btree_node_insert(node->parent, target, node, brother);
	}
}

void BTree::btree_node_insert(pbtree_node node, int target, pbtree_node left, pbtree_node right)
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
*遍历搜索，如果不存在则直接返回false
*遍历搜索，定位到关键字的节点的时候，找到节点孩子的左节点的最大值或者右节点的最小值进行替换，接下来是删除叶节点处的替换的关键字
*判断函数进行对叶节点的判断，如果关键字小于T-1
*①其兄弟可以提供一个关键字支持（此时兄弟关键字大于等于T），则通过旋转，从父结点转接一个关键字过来
*②若左右两兄弟都无法提供，则加上父节点对应的关键字合并，此时会影响父节点的个数，递归判断父节点
*
*注意事项：
*当进行孩纸指针转移的时候，会产生父节点的更替，此时注意更新parent的信息
*
*
*删除叶节点 ，更新上一个
*/

void BTree::btree_judge(pbtree_node node)
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

bool BTree::Delete(int target)
{
	cout << "Delete " <<target << endl;
	pbtree_node node = root;
	int find = -1;
	while (!node->isleaf)//非叶节点，便利寻找下一个应该寻找的节点
	{
		bool flag = true;
		for (int i = 0; i < node->num; i++)
		{
			if (target == node->k[i]){
				find = i;
				break;
			}
			if (target < node->k[i]){
				node = node->p[i];
				flag = false;
				break;
			}
		}
		if (find != -1)
			break;
		if (flag){
			node = node->p[node->num];
		}

	}
	if (find == -1)
		return false;
	//leaf node
	if (node->isleaf){
		for (int i = find; i < node->num; ++i)
		{
			node->k[i] = node->k[i + 1];
		}
		node->num--;
		btree_judge(node);
	}
	else//normal node
	{
		pbtree_node temp = node->p[find + 1];
		while (temp->p[0] != NULL)
			temp = temp->p[0];
		node->k[find] = temp->k[0];
		for (int i = 0; i < temp->num; ++i)
			temp->k[i] = temp->k[i + 1];
		temp->num--;
		btree_judge(temp);
	}
}

void BTree::level_display()
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
			cout << node->k[i]  << " ";
		}
		cout << "]";

		for (int i = 0; i <= node->num; i++) {
			if (NULL != node->p[i]) {
				queue[rear++] = node->p[i];
			}
		}
	}
	cout << endl;
}
