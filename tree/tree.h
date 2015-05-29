/************************************************************************/
/* 二叉排序树
	以链式方式存储，保证了在插入和删除时的不用移动节点的特点，

		1、有序插入时一定是在叶子节点处插入
		2、删除时需要考虑 子节点的个数 （0,1,2） 来分为不同的情况
		3、中序遍历是有序 序列

		serach();
		del();//删除叶子节点 只有叶子节点才可以直接 delete 否则会丢失其子节点
		delete_(Node n,int x,Node pre); //删除指定值的节点 
		delete_(Node &n); 析构  //与上面删除指定节点不同的是 该处是引用 为了防止重复析构

		二叉树保证了查找的效率，在查找时走过的路径就是根节点到所要查找的节点的额路径，
			极端的情况1、根几点就是所要查找的值 则查找次数为 1
						2、 查找不到的情况，则最坏情况不会超过二叉树的深度，而二叉树的深度因其插入总是在叶子节点，
								使得二叉树的深度是不确定的。最坏的情况是是二叉树就是 全右树和 全左树  因此必须保证排序二叉树的
								是一种 平衡二叉树  AVL 树 self-balancing binary tree 或 height-balancing binary tree
/************************************************************************/




#ifndef TREE_H__
#define TREE_H__
#define SWAP(a,b){int x = a->x;a->x = b->x;b->x=x;}

#include <iostream>

using namespace std;

/************************************************************************/
/* node 的定义过程完成了两个工作
1、定义了一个node节点， 相当于 struct node {};
2、为node* typedef 为 Node  即 typedef node* Node 
/************************************************************************/
typedef struct node{

	int x;
	node* l;
	node* r;

}* Node;


class Tree_{
public:
	Node r;
	Tree_(){
		r = new node;
		r->l = NULL;
		r->r = NULL;
		r->x = -1;
	}
	Node serach(Node n,int x){
		if(n==NULL){
			return NULL;
		}else if(n->x=x){
			return n;
		}
		if(n->x > x){
			serach(n->l,x);
		}else{
			serach(n->r,x);
		}
		
	}
	void del(Node n){
		delete n;
		n = NULL;
	}
	int delete_(Node n, int x, Node pre){
		if(n==NULL){//没有找到对应 x  的节点
			return -1;
		}
		if(n->x==x){ //删除当前节点 分为下面的几种情况
			if(n->r==NULL||n->l==NULL){ //比较简单的情况  即没有子节点或者只有一个子节点
				Node t = n->r==NULL?n->l:n->r; //找到非NULL的节点
				if(t == NULL){ //没有子节点 即n本身是叶子节点
					del(n);
					return 1;
				}else{  //有一个子节点  直接删除当前n节点， 
					
					if(pre->x>t->x)
						pre->l = t;
					else
						pre->r = t;
					del(n);
					return 1;
				}
			}else{ //       转右 找到左尽头  直接后驱
				   //或者  向左 找到右尽头  直接前驱
				Node t = n->l;
				Node t_ = n;
				while(t->r){
					t_ = t;
					t = t->r;
				}
				SWAP(t,n); //交换两个节点的值 为的是将要删除的节点换到底部 即靠近叶子节点的位置 方便交换
				return delete_(t,x,t_); //删除交换后的节点 
			}
		}else if(n->x > x){
			return delete_(n->l,x,n);
		}else{
			return delete_(n->r,x,n);
		}
	}
	int height(Node n){
		if(n==NULL){
			return 0;
		}
		int lh = height(n->l);
		int rh = height(n->r);

		int max = lh>rh?lh:rh;

		return max + 1;
		
	}
	void delete_(Node& n);
	~Tree_(){
		delete_(this->r);
	}
	void xx(Node n);
	void hx(Node n);
	void zx(Node n);
	void  insert(Node& n, int x);
	int empty(){
		return r->x==-1?1:0;
	}
};

void Tree_::delete_(Node& n){
	if(n==NULL){
		return ;
	}else{
		delete_(n->l);
		delete_(n->r);
		delete n;
		n = NULL;
	}
}
void Tree_::xx(Node n){
	if(n==NULL){
		return;
	}else{
		cout << n->x << endl;
		xx(n->l);
		xx(n->r);
	}
}
void Tree_::zx(Node n){
	if(n==NULL){
		return ;
	}else{
		zx(n->l);
		cout << n->x << endl;
		zx(n->r);
	}
}
void Tree_::insert(Node& n,int x){
	
	if(n!=NULL&&n->x==-1){
		n->x = x;
		return;
	}
	if(n==NULL){
		n = new node;
		n->x = x;
		n->l = NULL;
		n->r = NULL;	
		return ;
	}

	if(n->x > x){
		insert(n->l,x);
	}else{
		insert(n->r,x);
	}
}

#endif