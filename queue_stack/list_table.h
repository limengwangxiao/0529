
/************************************************************************/
/* // list_table standard header            
//��������

���� resort
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
//��ģ��Ľṹ�岻��ֱ��typedef

template <class T>
class list_table{
typedef node <T> * Node;
public:
	node<T>* head;
	node<T>* low;
public:
	Node nth_element(int n){  //�ҳ�������n��Ԫ��
		assert(n<=size());
		Node p_one = head;
		Node p_two = head;  //��������ָ�룬�Ƚ�һ��ָ���Ƶ�����n��λ���ϣ���ͬ���ƶ�����ָ��

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
		while(t->next!=NULL){//�ҵ� ��һ���ǿյ� ��node
			t = t->next;
		}
		node<T> *cur = new node<T>;
		cur->data = x;
		cur->next = 0;
		t->next = cur;
	}
	void print(){
		node<T> *t = head->next;//head �в���ֵ
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
	if(flag==1){  //remove first  ɾ������head->next
		head->next = p;  //���迼��t�Ƿ���NULL����� ��Ҫɾ����һ��Ԫ�� ʹ�����豣֤��Ԫ�صĴ���
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


	if(t==NULL){//�ҵ������ĩβ ����ǰҪ�����ֵ �����������������
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
	if(_f==1){//ǰ��
		p->next = cur;
		cur->next = t;
	}else{//���
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
