#include "StdAfx.h"
#include <iostream>  
using namespace std;  
  
#define BLACK 0  
#define RED 1  
typedef struct Node
{
	int key;
	Node* parent;
	Node* left;
	Node* right;
	bool color;

	//扩展属性
	int v;
	int p;
	int m;
	int o;
	Node(Node*init,int key)
		:key(key),left(init),right(init),parent(init),color(RED),v(0),m(0),o(key){}
												//初始颜色设为红色 因为新插入的结点颜色为红色 
												//所以说nil结点需要再手动将颜色设置为黑色
};

typedef struct Red_Black_Tree
{
	Node* root;
	Node* nil;
	Red_Black_Tree()
	{
		nil = new Node(NULL,-1);
		nil->color = BLACK;//nil结点颜色为黑色
		root = nil;
	}
};
int max(int a,int b,int c)
{
	a = a > b?a:b;
	return a > c?a:c;
}
//最大重叠点的维护
void maintain_maxOverlap_toRoot(Red_Black_Tree* T,Node*z)
{
	while(z != T->nil)
	{
		z->v = z->left->v + z->p + z->right->v;
		z->m = max(z->left->m,
			       z->left->v+z->p,
			       z->left->v+z->p+z->right->m);
		if(z->m == z->left->m)
			z->o = z->left->o;
		else if(z->m == z->left->v+z->p)
			z->o = z->key;
		else
			z->o = z->right->o;
		z = z->parent;
	}
}
//对于旋转来说  只有两个节点需要重新维护  
void maintain_maxOverlap_oneNode(Red_Black_Tree* T,Node*z)
{
		z->v = z->left->v + z->p + z->right->v;
		z->m = max(z->left->m,
			       z->left->v+z->p,
			       z->left->v+z->p+z->right->m);
		if(z->m == z->left->m)
			z->o = z->left->o;
		else if(z->m == z->left->v+z->p)
			z->o = z->key;
		else
			z->o = z->right->o;
		z = z->parent;
}
//左旋  完全参照教材算法导论中文版第三版p177
void left_rotate(Red_Black_Tree* T,Node* x)
{
	Node* y = x->right;
	x->right = y->left;
	if(y->left != T->nil)
		y->left->parent = x;
	y->parent = x->parent;
	if(x->parent == T->nil)
		T->root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	maintain_maxOverlap_oneNode(T,x);
	maintain_maxOverlap_oneNode(T,y);
}
void right_rotate(Red_Black_Tree* T,Node* x)
{
	Node* y = x->left;
	x->left = y->right;
	if(y->right != T->nil)
		y->right->parent = x;
	y->parent = x->parent;
	if(x->parent == T->nil)
		T->root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
	maintain_maxOverlap_oneNode(T,x);
	maintain_maxOverlap_oneNode(T,y);
}
void rb_insert_fixup(Red_Black_Tree* T,Node* z)
{
	while(z->parent->color == RED)
	{
		if(z->parent == z->parent->parent->left)
		{
			Node* y = z->parent->parent->right;
			//case1
			if(y->color == RED)
			{
				z->parent->color = BLACK;
				y->parent->color = BLACK;
				y->parent->parent->color = RED;
				z = y->parent->parent; 
			}
			else
			{
				//case2
				if(z == z->parent->right)
				{
					z = z->parent;
					left_rotate(T,z);
				}
				//case3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				right_rotate(T,z);
				z = T->root;
			}
		}
		else//z->parent == z->parent->parent->right
		{
			Node* y = z->parent->parent->left;
			//case1
			if(y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent; 
			}
			else
			{
				//case2
				if(z == z->parent->left)
				{
					z = z->parent;
					right_rotate(T,z);
				}
				//case3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				left_rotate(T,z);
			}
		}
	}
	T->root->color = BLACK;
}
void rb_insert(Red_Black_Tree* T,Node* z)
{
	Node* y = T->nil;
	Node* x = T->root;
	while(x != T->nil)
	{
		y = x;
		if(z->key < x->key)
			x = x->left;
		else 
			x = x->right;
	}
	if(y == T->nil)
		T->root = z;
	else if(z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->parent = y;
	maintain_maxOverlap_toRoot(T,z);//通过实验与思考发现 由于对于旋转操作来说 先调整颜色 或者先维护信息都可以(后面删除的情况也一样）
									// 但是我觉得这有一定碰巧的因素在里面  先维护信息(使整颗树的信息正确),然后fixup（插入和删除）在变换过程中也维护这种
									//信息不变  在逻辑上更严密 也更容易理解 
	rb_insert_fixup(T,z);
	//maintain_maxOverlap_toRoot(T,z);
}

//返回以z为根结点的子树中的最小元素 
Node* tree_min(Red_Black_Tree* T, Node* z)
{
	while(z->left != T->nil)
		z = z->left;
	return z;
}

// //返回结点的后继
// Node* tree_sucessor(Red_Black_Tree* T,Node* z)
// {
// 	if(z->right != T->nil)
// 		return tree_min(T,z->right);
// 	else
// 	{
// 		while(z == z->parent->right)
// 			z = z->parent;
// 		return z;
// 	}
// }

//让v结点替代u结点与u结点的父节点互相连接 
void tree_node_replace(Red_Black_Tree*T, Node* u,Node* v)
{
	v->parent = u->parent;
	if(u->parent == T->nil)
		T->root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
}
void rb_delete_fixup(Red_Black_Tree* T,Node* x)
{
	while(x != T->root && x->color == BLACK)
	{
		if(x == x->parent->left)
		{

			Node* w = x->parent->right;
			//case1
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(T,x->parent);
			}
			//case2
			else if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				//case3
				if(w->left->color == RED)
				{
					w->color = RED;
					w->left->color = BLACK;
					right_rotate(T,w);
					w = x->parent->right;
				}
				//case4
				w->right->color = BLACK;
				w->color = x->parent->color;
				x->parent->color = BLACK;
				left_rotate(T,x->parent);
				x = T->root;
			}

		}
		else//x == x->parent->right
		{
			Node* w = x->parent->left;
			//case1
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				right_rotate(T,x->parent);
			}
			//case2
			else if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				//case3
				if(w->right->color == RED)
				{
					w->color = RED;
					w->right->color = BLACK;
					left_rotate(T,w);
					w = x->parent->left;
				}
				//case4
				w->left->color = BLACK;
				w->color = x->parent->color;
				x->parent->color = BLACK;
				right_rotate(T,x->parent);
				x = T->root;
			}
		}
	}
	x->color = BLACK;
}

void rb_delete(Red_Black_Tree* T,Node*z)
{
	bool original_color = z->color;//用来记录被删除的节点的颜色
	Node* x;//用来记录可能引起红黑树性质被破坏的点
	if(z->left == T->nil)
	{
		tree_node_replace(T,z,z->right);
		x = z->right;
	}
	else if(z->right == T->nil)
	{
		tree_node_replace(T,z,z->left);		
		x = z->left;
	}
	else
	{	
		Node* y = tree_min(T,z->right);
		if(y != z->right)
		{
			original_color = y->color;
			tree_node_replace(T,y,y->right);//y->left 一定为nil
			x = y->right;
			y->right = z->right;
			z->right->parent = y;
		}
		tree_node_replace(T,z,y);
		y->color = z->color;
		y->left = z->left;//因为有了nil这个哨兵 所以无需再进行判断
		z->left->parent = y;
	}
	maintain_maxOverlap_toRoot(T,x->parent);
	if(original_color == BLACK)
		rb_delete_fixup(T,x);
	//maintain_maxOverlap_toRoot(T,x->parent);
}

//求最大覆盖点  
int find_pom(Red_Black_Tree *T)  
{  
	return T->root->o;  
}  

Node* tree_search(Red_Black_Tree* T,int key)
{
	Node* z = T->root;
	while(z != T->nil)
	{
		if(z->key == key)
			return z;
		else if(key <  z->key)
			z = z->left;
		else
			z = z->right;
	}
	return T->nil;
}
//插入的区间为[1,2]  [3,5],[4,6],[5,7],[8,9]
//观察可知5为最大重叠点  与程序所求吻合
int main()
{
	int a[][2] = {{1,1},{2,-1},{3,1},{4,1},{5,1},{5,-1},{6,-1},{7,-1},{8,1},{9,-1}};
	Red_Black_Tree* Tree = new Red_Black_Tree;
	for(int i=0;i<10;i++)
	{
		Node* node = new Node(Tree->nil,a[i][0]);
		node->p = a[i][1];
		rb_insert(Tree,node);
	}
	cout<<"最大重叠点："<<find_pom(Tree)<<endl;
	cout<<"重叠次数："<<Tree->root->m<<endl;

	//删除[4,6]区间
	Node* node = tree_search(Tree,4);
	rb_delete(Tree,node);
	node = tree_search(Tree,6);
	rb_delete(Tree,node);

	cout<<"最大重叠点："<<find_pom(Tree)<<endl;
	cout<<"重叠次数："<<Tree->root->m<<endl;
	return 0;
}
