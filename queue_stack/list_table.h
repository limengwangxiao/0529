
/************************************************************************/
/* // list_table standard header            
//单向链表

逆序 resort
push_back
_delete	
add_pre 
add_aft

sort_insert
//
/************************************************************************/


#ifndef LIST_TABLE_H__
#define LIST_TABLE_H__
#include <iostream>
#include <assert.h>
using namespace std;
#ifndef NULL
#define NULL 0
#endif

template <class T>
struct node{
	T data;
	node* next;
};
//带模板的结构体不能直接typedef

template <class T>
class list_table{
typedef node <T> * Node;
public:
	node<T>* head;
	node<T>* low;
public:
	Node nth_element(int n){  //找出倒数第n个元素
		assert(n<=size());
		Node p_one = head;
		Node p_two = head;  //设置两个指针，先将一个指针移到正数n的位置上，再同步移动两个指针

		int k = 0;

		while(k<n){
			p_two = p_two->next;
			k ++;
		}

		while(p_two!=NULL){
			p_two = p_two->next;
			p_one = p_one->next;
		}

		return p_one;
	}
	int size(){
		int _size=0;
		Node t = head->next;
		while(t!=NULL){
			t=t->next;
			_size++;
		}
		return _size;
	}
	T __delete(int flag);
	void sort_insert(T x);
	void resort();
	void _delete(T x);
	void add(T x,T flag,int _f);
	void add(T x){
		node<T> *t = head;
		while(t->next!=NULL){//找到 下一个非空的 的node
			t = t->next;
		}
		node<T> *cur = new node<T>;
		cur->data = x;
		cur->next = 0;
		t->next = cur;
	}
	void print(){
		node<T> *t = head->next;//head 中不存值
		while(t!=0){
			cout<< t->data << endl;
			t=t->next;
		}
	}
	list_table(){
		head = new node<T>();
		head ->next = NULL;
	}
	~list_table();
};

template<class T>
T list_table<T>::__delete(int flag){
	T toD=-1;
	Node t = head->next;
	Node p = t->next;
	if(flag==1){  //remove first  删掉的是head->next
		head->next = p;  //无需考虑t是否是NULL的情况 因要删除第一个元素 使用者需保证该元素的存在
		toD = t->data;
		delete t;
	}else{//remove last
		t = head->next;
		p = head;
		while(t->next!=NULL){
			p = t;
			t = t->next;
		}
		p->next = NULL;
		toD = t->data;
		delete t;
	}

	return toD;
}
template<class T>
list_table<T>::~list_table(){

	node<T> *t = head;
	while(t->next!=NULL){
		node<T> *p = t;
		t = t->next;
		delete p;
		p = NULL;
	}
}


template<class T>
void list_table<T>::sort_insert(T x){
	node <T> *cur = new node<T>;
	cur->data = x;
	cur->next = NULL;
	node<T> *t = head->next;
	node <T> *p = head;
	while(t!=NULL&&t->data<x){
		p = t;
		t = t->next;
	}


	if(t==NULL){//找到链表的末尾 即当前要插入的值 在整个的链表中最大
		p->next = cur;
		cur->next = NULL;
	}else{
		cur->next = t;
		p->next = cur;
	}






}


template<class T>
void list_table<T>::add(T x, T flag,int _f){

	node <T> *cur = new node<T>;
	cur->data = x;
	cur->next = NULL;
	node<T> *t = head->next;
	node <T> *p = head;
	while(t!=NULL&&t->data!=flag){
		p = t;
		t = t->next;
	}
	if(_f==1){//前插
		p->next = cur;
		cur->next = t;
	}else{//后插
		cur->next = t->next;
		t->next = cur;
	}
}
template<class T>
void list_table<T>::resort(){
	node<T> *t = head->next;
	node<T> *q = NULL;
	node<T> *p;
	while(t!=NULL){
		p = t->next;
		t->next = q;
		q = t;
		t = p;
	}
	head->next = q;
}
template<class T>
void list_table<T>::_delete(T x){
	node<T> *t = head->next;
	node <T> *p = head;
	while(t!=NULL&&t->data!=x){
		p = t;
		t = t->next;
	}
	p->next = t->next;
	delete t;
}
#endif
