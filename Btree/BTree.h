#ifndef BTREE.H
#define BTREE.H
#define  M 5
//#define  T (M/2)*2<M?(M/2+1):(M/2)  //最低分叉数
#define T 3
struct btree_nodes;
typedef struct btree_nodes *pbtree_node;
typedef struct btree_nodes {
	int k[M];
	int num;
	pbtree_node p[M+1];
	pbtree_node parent;
}btree_node;


class BTree
{
public:
	BTree(){
		root=0;
		btree_create();
	}
	/**
	* @brief create a btree root
	*
	* @return pointer of btree root
	*/
	pbtree_node btree_create();

	/**
	* @brief allocate a new btree node
	*
	* @return pointer of new node
	*/
	pbtree_node btree_node_new();

	/**
	* @brief insert one key
	*
	*插入规则：只有到达了叶节点才插入，关键字满了溢出则向上分裂
	*
	* @param target: target of value
	*/
	void insert(int target);
	void level_display();
private:
	int btree_node_num;//record the number of btree node
	pbtree_node root;
	void btree_split(pbtree_node node);
	void btree_node_insert(pbtree_node node, int target, pbtree_node left, pbtree_node right);
};

#endif
