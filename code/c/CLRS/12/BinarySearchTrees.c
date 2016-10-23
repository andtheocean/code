#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

using namespace std;
typedef struct Node
{
	int key;
	Node* parent;
	Node* leftChild;
	Node* rightChild;
};
typedef struct Tree
{
	Node* root;
};
struct NodeStack
{
	Node** node;//最大容量大于搜索树的高度即可
	int top;
	void push(Node* n);
	Node* pop(void);
};

void NodeStack::push(Node* n)
{
	node[top++] = n;
}

Node* NodeStack::pop(void)
{
	return node[--top];
}

//循环方式实现树结点的插入，中序输出
//输入的tree都可以为NULL

//插入   
void TREE_INSERT(Tree *tree,Node* z)
{
	Node* x = tree->root;
	Node* y = NULL;
	while(x != NULL)
	{
		y = x;
		if(z->key<x->key)
			x = x->leftChild;
		else
			x = x->rightChild;
	}
	if(y == NULL)//树为空树
	{
		tree->root = z;
		z->parent = NULL;
	}
	else if(z->key < y->key)
	{
		y->leftChild = z;
		z->parent = y;
	}
	else
	{
		y->rightChild = z;
		z->parent = y;
	}
}
//用一个栈中序输出二叉树
void printTreeByStack(Node* root)
{
	if(root == NULL)
	{
		cout<<"NULL tree.";
		return ;
	}
	NodeStack* nodeStack = new NodeStack;
	nodeStack->node = new Node*[10];
	nodeStack->top = 0;
	while(nodeStack->top != 0 || root != NULL)//输出根结点的时候，会出现栈为空的情况，所以再加上对root是否为空的判断
	{
		while(root != NULL)
		{
			nodeStack->push(root);
			root = root->leftChild;
		}
		root = nodeStack->pop();
		cout<<root->key<<"  ";
		root = root->rightChild;
	}
}

//不递归  也不用栈中序输出
void print(Node* root)
{
	if(root == NULL)
	{
		cout<<"NULL tree.";
		return ;
	}
	Node* y = NULL;
	while(root != NULL  )
	{
		//if(root->leftChild != NULL && root->parent == y)//root->parent == y表明是在沿着树向下搜索
		//					                // 左子树不为空
		//{
		//	y = root;
		//	root = root->leftChild;
		//}
		//else if(root->rightChild != NULL && root->parent == y)//向下搜索  左子树为空 右子树不为空
		//{
		//	cout<<root->key<<"  ";
		//	y = root;
		//	root = root->rightChild;
		//}
		//else if(root->leftChild == NULL && root->rightChild == NULL )//左右子树都为空 也就说明一定是在向下搜索  
		//{
		//	cout<<root->key<<"  ";
		//	y = root;
		//	root = root->parent;
		//}
		if(root->parent == y)//这是对上面三种情况的一个综合  精简代码
		{
			y = root;
			//如果 左子树不为空取左子树
			//如果左子树为空  右子树不为空  取右子树
			//如果左右子树都为空   取父结点 
			root = root->leftChild?root->leftChild:
				   root->rightChild?root->rightChild:root->parent;
			if(y->leftChild != root)//除了左子树不为空的情况  都需要输出
				cout<<y->key<<"  ";
		}


		else if(root->leftChild == y )//左子树向上回退的情况
		{
			cout<<root->key<<"  ";
			if(root->rightChild != NULL)
			{
				y = root;
				root= root->rightChild;
			}
			else//root->rightChild为空  继续回退
			{
				y = root;
				root = root->parent;
			}
		}
		else  //右子树向上回退  就直接回退
		{
			y = root;
			root = root->parent;
		}
	}
}



//递归实现二叉搜索树的插入，中序输出，输入可以为空
// 插入
void TREE_INSERT_recursive(Node* node,Node* z,Node* p)
{
	if(node == NULL)
	{
		if(z->key<p->key)
		{
			p->leftChild = z;
			z->parent = p;
		}
		else
		{
			p->rightChild = z;
			z->parent = p;
		}
	}
	else
	{
		if(z->key<node->key)
			TREE_INSERT_recursive(node->leftChild,z,node);
		else
			TREE_INSERT_recursive(node->rightChild,z,node);
	}
}
void TREE_INSERT_recursivePrehandle(Tree *tree,Node* z)
{
	if(tree->root == NULL)
	{
		tree->root = z;
		z->parent = NULL;
	}
	else
	{
		TREE_INSERT_recursive(tree->root,z,NULL);
	}
}
//中序输出
void printTreeRecursive(Node* node)
{
	if(node == NULL)
		return;
	printTreeRecursive(node->leftChild);
	cout<<node->key<<"  ";
	printTreeRecursive(node->rightChild);
}




//替换节点  输入：两个节点 u v ,让u的父节点直接指向v，并设v的父节为点u的父节点
void TreeNode_replace(Tree* tree, Node* u, Node* v)
{
	if(u->parent == NULL)//要被替换的是根结点
	{
		tree->root = v;
	}
	else
	{
		if(u == u->parent->leftChild)
			u->parent->leftChild = v;
		else
			u->parent->rightChild = v;
	}
	if(v != NULL)
		v->parent = u->parent;
}

//删除元素  
void Tree_delete(Tree* tree, Node* z)
{
	// if(z->leftChild == NULL && z->rightChild == NULL)
	// {
	// 	if(z==z->parent->leftChild)
	// 		z->parent->leftChild = NULL;
	// 	else
	// 		z->parent->rightChild = NULL;	
	// }
	// else if(z->leftChild == NULL)
	// {
	// 	if(z==z->parent->leftChild)
	// 	{
	// 		z->parent->leftChild = z->rightChild;
	// 		z->rightChild->parent = z->parent;
	// 	}
	// 	else
	// 	{
	// 		z->parent->rightChild = z->rightChild;
	// 		z->rightChild->parent = z->parent;	
	// 	}
	// }
	// else if(z->rightChild == NULL)
	// {
	// 	if(z==z->parent->leftChild)
	// 	{
	// 		z->parent->leftChild = z->leftChild;
	// 		z->leftChild->parent = z->parent;
	// 	}
	// 	else
	// 	{
	// 		z->parent->rightChild = z->leftChild;
	// 		z->leftChild->parent = z->parent;	
	// 	}
	// }
	//下面两种情况是对上面三种情况的合并与精简
	if(z->leftChild == NULL)
	{
		TreeNode_replace(tree,z,z->rightChild);
	}
	else if(z->rightChild == NULL)
	{
		TreeNode_replace(tree,z,z->leftChild);
	}



	else//左右子树都不为空
	{
		Node* y = z->rightChild;
		while(y->leftChild!=NULL)//获得z的后继结点
			y = y->leftChild;
		if(y != z->rightChild)
		{
			TreeNode_replace(tree,y,y->rightChild);
			y->rightChild = z->rightChild;
			y->rightChild->parent = y;
		}
		TreeNode_replace(tree,z,y);
		y->leftChild = z->leftChild;
		z->leftChild->parent = y;
	}
}

int main()
{
	int a[13] = {5,3,2,1,4,6,7,9,8,13,12,10,11};
	//非递归
	Tree* testTree = new Tree;
	testTree->root = NULL;
	for(int i=0;i<13;i++)
	{
		Node* node = new Node;
		node->key = a[i];
		node->parent = NULL;
		node->leftChild = NULL;
		node->rightChild = NULL;
		TREE_INSERT(testTree,node);
	}
	cout<<"用循环的方式插入元素建树："<<endl<<"Build succeed!"<<endl;
	cout<<"用栈输出："<<endl;
	printTreeByStack(testTree->root);
	cout<<endl<<"既不用递归，也不用栈输出:"<<endl;
	print(testTree->root);
	cout<<endl<<endl;


	cout<<"用递归的方式插入元素建树："<<endl<<"Build succeed!"<<endl;
	Tree* RecursiveTestTree = new Tree;
	RecursiveTestTree->root = NULL;
	for(int i=0;i<13;i++)
	{
		Node* node = new Node;
		node->key = a[i];
		node->parent = NULL;
		node->leftChild = NULL;
		node->rightChild = NULL;
		TREE_INSERT_recursivePrehandle(RecursiveTestTree,node);
	}
	cout<<"用递归的方式输出："<<endl;	
	printTreeRecursive(RecursiveTestTree->root);
	//删除节点
	Node* deleteNode = RecursiveTestTree->root;
	int key = 9;
	while(deleteNode->key!=key  && deleteNode != NULL)
	{
		if(key < deleteNode->key)
			deleteNode = deleteNode->leftChild;
		else
			deleteNode = deleteNode->rightChild;
	}
	Tree_delete(RecursiveTestTree,deleteNode);
	cout<<endl<<"删除节点"<<key<<"后："<<endl;
	printTreeRecursive(RecursiveTestTree->root);
	cout<<endl;
	return 0;
}yy