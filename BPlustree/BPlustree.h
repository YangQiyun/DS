#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#define  M 3
//#define  T (M/2)*2<M?(M/2+1):(M/2)  //最低分叉数
#define T 2
struct btree_nodes;
typedef struct btree_nodes *pbtree_node;
typedef struct btree_nodes {
	int k[M];
	int num;
	pbtree_node p[M + 1];
	pbtree_node parent;
	bool isleaf;
	pbtree_node next;
}btree_node;


class BPlusTree
{
public:
	BPlusTree(){
		root = 0;
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

	/**
	* @brief delete one key
	*
	*删除规则于cpp
	*
	* @param target: target of value
	* @return if success to delete is ture ,other is false
	*/
	bool Delete(int target);

	/**
	* @brief show by level order
	*
	*/
	void level_display();
	/**
	* @brief show by leaf node
	*
	*/
	void bplus_display();
private:
	int btree_node_num;//record the number of btree node
	pbtree_node root;
	pbtree_node head;
	/**
	* @brief when one btree_node key is more than what we limit,this function slove this problem splite the node
	*
	* @param node:btree node pointer
	*/
	void btree_split(pbtree_node node);	
	void bplustree_split(pbtree_node node);
	/**
	* @brief insert the node which need add two children
	*
	* @param node: btree node pointer
	* @param target: the value that need to insert to the node with tis two child
	* @param left:left child of value
	* @param right:right child of value
	*/
	void btree_node_insert(pbtree_node node, int target, pbtree_node left, pbtree_node right);
	/**
	* @brief judge the tree node's num is legal (num more than or equal T-1)
	*
	* @param node: btree node pointer
	*/
	void btree_judge(pbtree_node node);
	/**
	* @brief 向上循环替换掉已经被删除的关键字
	*
	* @param node: btree node pointer
	* @param pfind: the index of parent'p to the node, for the reason of the same value that may replace a wrong value
	* @param find:the value which need to be replaced
	* @param replace:the value to the new one
	*
	*/
	void bplustree_replace(pbtree_node node, int pfind, int find, int replace);
};

#endif
