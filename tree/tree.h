/************************************************************************/
/* ����������
	����ʽ��ʽ�洢����֤���ڲ����ɾ��ʱ�Ĳ����ƶ��ڵ���ص㣬

		1���������ʱһ������Ҷ�ӽڵ㴦����
		2��ɾ��ʱ��Ҫ���� �ӽڵ�ĸ��� ��0,1,2�� ����Ϊ��ͬ�����
		3��������������� ����

		serach();
		del();//ɾ��Ҷ�ӽڵ� ֻ��Ҷ�ӽڵ�ſ���ֱ�� delete ����ᶪʧ���ӽڵ�
		delete_(Node n,int x,Node pre); //ɾ��ָ��ֵ�Ľڵ� 
		delete_(Node &n); ����  //������ɾ��ָ���ڵ㲻ͬ���� �ô������� Ϊ�˷�ֹ�ظ�����

		��������֤�˲��ҵ�Ч�ʣ��ڲ���ʱ�߹���·�����Ǹ��ڵ㵽��Ҫ���ҵĽڵ�Ķ�·����
			���˵����1�������������Ҫ���ҵ�ֵ ����Ҵ���Ϊ 1
						2�� ���Ҳ�������������������ᳬ������������ȣ���������������������������Ҷ�ӽڵ㣬
								ʹ�ö�����������ǲ�ȷ���ġ����������Ƕ��������� ȫ������ ȫ����  ��˱��뱣֤�����������
								��һ�� ƽ�������  AVL �� self-balancing binary tree �� height-balancing binary tree
/************************************************************************/




#ifndef TREE_H__
#define TREE_H__
#define SWAP(a,b){int x = a->x;a->x = b->x;b->x=x;}

#include <iostream>

using namespace std;

/************************************************************************/
/* node �Ķ�������������������
1��������һ��node�ڵ㣬 �൱�� struct node {};
2��Ϊnode* typedef Ϊ Node  �� typedef node* Node 
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
		if(n==NULL){//û���ҵ���Ӧ x  �Ľڵ�
			return -1;
		}
		if(n->x==x){ //ɾ����ǰ�ڵ� ��Ϊ����ļ������
			if(n->r==NULL||n->l==NULL){ //�Ƚϼ򵥵����  ��û���ӽڵ����ֻ��һ���ӽڵ�
				Node t = n->r==NULL?n->l:n->r; //�ҵ���NULL�Ľڵ�
				if(t == NULL){ //û���ӽڵ� ��n������Ҷ�ӽڵ�
					del(n);
					return 1;
				}else{  //��һ���ӽڵ�  ֱ��ɾ����ǰn�ڵ㣬 
					
					if(pre->x>t->x)
						pre->l = t;
					else
						pre->r = t;
					del(n);
					return 1;
				}
			}else{ //       ת�� �ҵ���ͷ  ֱ�Ӻ���
				   //����  ���� �ҵ��Ҿ�ͷ  ֱ��ǰ��
				Node t = n->l;
				Node t_ = n;
				while(t->r){
					t_ = t;
					t = t->r;
				}
				SWAP(t,n); //���������ڵ��ֵ Ϊ���ǽ�Ҫɾ���Ľڵ㻻���ײ� ������Ҷ�ӽڵ��λ�� ���㽻��
				return delete_(t,x,t_); //ɾ��������Ľڵ� 
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