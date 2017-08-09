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
	cout << "Insert " << char(target + 64) << endl;
	pbtree_node node = root;
	while (node->p[0] != 0)//��Ҷ�ڵ㣬����Ѱ����һ��Ӧ��Ѱ�ҵĽڵ�
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

	btree_node_insert(node, target, 0, 0);

}

void BTree::btree_split(pbtree_node node)
{
	if (node == root)//�����Ҷ�ڵ��Ǹ��ڵ�
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

		if (2 * T == M)//����ԭ����MΪż��6,  6���ؼ�key 7����  t=3  
		{
			left->p[T - 1] = node->p[T - 1];
			right->p[T - 1] = node->p[M - 1];
			right->k[T - 1] = node->k[2 * T - 1];
			right->p[T] = node->p[M];
			left->num = T - 1;
			right->num = T;
		}
		else{//����ԭ����MΪ����,  5���ؼ�key 6����  t=3  
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
			if(left->p[b]!=NULL)left->p[b]->parent = left;
		for (int b = 0; b <= right->num; b++)
			if(right->p[b]!=NULL)right->p[b]->parent = right;
	}
	else//����ǷǸ��ڵ�
	{
		pbtree_node brother = btree_node_new();
		brother->parent = node->parent;
		for (int i = 0; i < (T - 1); ++i)
		{
			brother->k[i] = node->k[i + T];
			brother->p[i] = node->p[i + T];
			if (brother->p[i] != NULL )
			 brother->p[i]->parent = brother;
			node->k[i + T] = 0;
			node->p[i + T] = NULL;
		}
		node->num = T - 1;
		if (2 * T == M)//����ԭ����MΪż��6,  6���ؼ�key 7����  t=3  
		{
			brother->k[T - 1] = node->k[2 * T - 1];
			brother->p[T - 1] = node->p[2 * T - 1];
			if (brother->p[T-1]!=NULL)
			{
				brother->p[T - 1]->parent = brother;
			}
			
			 
			brother->p[T] = node->p[2 * T];
			if (brother->p[T ] != NULL)
			{
				brother->p[T]->parent = brother;
			}
			node->k[2 * T - 1] = 0;
			node->p[2 * T - 1] = node->p[2 * T] = NULL;
			brother->num = T;

		}
		else //����ԭ����MΪ����5�� 5���ؼ�key 6���� t=3 
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

void BTree::btree_node_insert(pbtree_node node, int target, pbtree_node left, pbtree_node right)
{
	//Ҷ�ڵ������ֱ�Ӳ���
	if (0 == node->num)//��������ʼ�Ŀյĸ��ڵ�
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

	if (node->num == M)//Ҷ�ڵ��������Ϸ���
	{
		btree_split(node);
	}
}

/************  ɾ������   **************
*
*���������������������ֱ�ӷ���false
*������������λ���ؼ��ֵĽڵ��ʱ���ҵ��ڵ㺢�ӵ���ڵ�����ֵ�����ҽڵ����Сֵ�����滻����������ɾ��Ҷ�ڵ㴦���滻�Ĺؼ���
*�жϺ������ж�Ҷ�ڵ���жϣ�����ؼ���С��T-1
*�����ֵܿ����ṩһ���ؼ���֧�֣���ʱ�ֵܹؼ��ִ��ڵ���T������ͨ����ת���Ӹ����ת��һ���ؼ��ֹ���
*�����������ֵܶ��޷��ṩ������ϸ��ڵ��Ӧ�Ĺؼ��ֺϲ�����ʱ��Ӱ�츸�ڵ�ĸ������ݹ��жϸ��ڵ�
*
*ע�����
*�����к�ָֽ��ת�Ƶ�ʱ�򣬻�������ڵ�ĸ��棬��ʱע�����parent����Ϣ
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

			//������һ���ؼ��ֵ�B��
			if (0 == parent->num){
				root->num = left_brother->num;
				for (int i = 0; i < root->num; ++i)
					root->k[i] = left_brother->k[i];
				for (int i = 0; i <= root->num; ++i){
					root->p[i] = left_brother->p[i];
					root->p[i]==NULL?NULL:root->p[i]->parent = root;
				}
					
				delete left_brother;
			}
			else
			btree_judge(parent);
		}

}

bool BTree::Delete(int target)
{
	cout <<"Delete "<< char(target + 64)<<endl;
	pbtree_node node = root;
	int find = -1;
	while (node != NULL)//��Ҷ�ڵ㣬����Ѱ����һ��Ӧ��Ѱ�ҵĽڵ�
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
	//no child
	if (node->p[0] == NULL){
		for (int i = find; i < node->num; ++i)
		{
			node->k[i] = node->k[i + 1];
		}
		node->num--;
		btree_judge(node);
	}
	else//have children
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
			cout << char(node->k[i] + 64) << " ";
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
