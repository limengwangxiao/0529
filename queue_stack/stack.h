#ifndef STACK_H__
#define STACK_H__
#include "list_table.h"

template<class T>
class stack{
public:
	list_table<T> l;
	void push(T x);
	T pop();
	bool empty();
	stack(){}
	~stack(){}
};
template<class T>
bool stack<T>::empty(){
	if(l.size()==0){
		return 1;
	}else{return 0;}
}
template<class T>
void stack<T>::push(T x){
	l.add(x);
}
template<class T>
T stack<T>::pop(){
	if(l.size()==0){// 只有一个head  list 中并没有值存储
		return -1;
	}
	T t = l.__delete(0);
	return t;
}

#endif