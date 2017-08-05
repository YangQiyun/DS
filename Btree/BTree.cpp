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

	for (int i = 0; i < M+1; i++)
	{
		pNode->p[i] = NULL;
	}

	pNode->num = 0;
	pNode->parent = NULL;

	return pNode;
}

pbtree_node BTree::btree_create()
{
	if (NULL == this->root){
		root = btree_node_new();
		root->parent = root;
	}
	return root;
}

void  BTree::insert(int target)
{
	pbtree_node node = root;
	while (node->p[0] != 0)//非叶节点，便利寻找下一个应该寻找的节点
	{
		bool flag = true;
		for (int i = 0; i < node->num; i++)
		{
			if (target < node->k[i]){
				node = node->p[i];
				flag = false;
				break;
			}
		}
		if (flag){
			node = node->p[node->num];
		}
	}

	btree_node_insert(node, target,0,0);

}

void BTree::btree_split(pbtree_node node)
{
	if (node == root)//如果该叶节点是根节点
	{
		pbtree_node left = btree_node_new();
		pbtree_node right = btree_node_new();
		left->parent = right->parent = node;
		for (int i = 0; i < T-1 ; i++)
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
			left->num=T-1;
			right->num=T;
		}
		else{//该树原来的M为奇数,  5个关键key 6个叉  t=3  
			left->p[T - 1] = node->p[T - 1];
			right->p[T - 1] = node->p[M];
			left->num=right->num=T-1;
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
	}
	else//如果是非跟节点
	{
		pbtree_node brother = btree_node_new();
		brother->parent = node->parent;
		for (int i = 0; i < (T - 1); ++i)
		{
			brother->k[i] = node->k[i + T];
			brother->p[i] = node->p[i + T];
			node->k[i + T] = 0;
			node->p[i + T] = NULL;
		}
		node->num=T-1;
		if (2 * T == M)//该树原来的M为偶数6,  6个关键key 7个叉  t=3  
		{
			brother->k[T - 1] = node->k[2 * T - 1];
			brother->p[T - 1] = node->p[2 * T - 1];
			brother->p[T] = node->p[2 * T];
			node->k[2 * T - 1] = 0;
			node->p[2 * T - 1] = node->p[2 * T] = NULL;
			brother->num=T;
			
		}
		else //该树原来的M为奇数5， 5个关键key 6个叉 t=3 
		{
			brother->num=T-1;
			brother->p[T-1]=node->p[2*T-1];
			node->p[2*T-1]=0;
			
		}
		int target = node->k[T - 1];
			node->k[T - 1] = 0;
			
			btree_node_insert(node->parent, target, node, brother);
	}
}

void BTree::btree_node_insert(pbtree_node node,int target,pbtree_node left,pbtree_node right)
{
	//叶节点非满，直接插入
	if (0 == node->num)//如果是最初始的空的跟节点
	{
		node->num = 1;
		node->k[0] = target;
		return;
	}
	int	i = node->num - 1;

	while (i >= 0 && target < node->k[i])
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
			int temp=M;
			while(temp!=0){
				node->p[temp]=node->p[temp-1];
				--temp;
			}
			node->p[0] = left;
			node->p[1] = right;
		}
		else
		{
			node->p[i+1] = left;
			int temp = M;
			while (temp!=i+1)
			{
				node->p[temp] = node->p[temp - 1];
				--temp;
			}
			node->p[i + 2] = right;
		}
	}

	if (node->num == M)//叶节点满，向上分裂
	{
		btree_split(node);
	}
}

void BTree::level_display()
{
	// just for simplicty, can't exceed 200 nodes in the tree
	btree_node *queue[200] = {NULL};
	int front = 0;
	int rear = 0;

	queue[rear++] = root;

	while(front < rear) {
		btree_node *node = queue[front++];

		cout<<"[";
		for(int i = 0; i < node->num; i++) {
			cout<<node->k[i]<<" ";
		}
		cout<<"]";

		for(int i = 0; i <= node->num; i++) {
			if(NULL != node->p[i]) {
				queue[rear++] = node->p[i];               
			}
		}
	}
	cout<<endl;
}
