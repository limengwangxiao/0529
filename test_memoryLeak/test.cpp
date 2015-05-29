#include "leak.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

class people{

public:
	people(){
		throw int(3);
	}
	~people(){
		cout << "~" << endl;
	}
	/*void* operator new(size_t size){  
		//与构造和析构一样的是，new和delete 要求参数一致，
			//即某次new的过程使用的new函数，若在构造中的某个时刻出现异常而终止构造过程的话，则会自动删除上面已经完成的构造，而完成这项任务的就是与new参数对应的相同的delete重载。而若成功的完成构造，则此后的过程都不会用到复杂参数的delete重载 ，这也是比较好理解的，因为构造没有完成，只能是用new 的反过程delete 去完成
				//关于这个问题 在people将对应的两种情况，即多参数的和单个参数的，共4个函数都给出了，在测试的时候，创造一种 中断构造的情况 就是在 构造函数中抛出异常，使程序终止，则此时回去调用对应参数的delete  

		//而且 目前来看多参数的delete 重载，只会在这样的场合使用到，即在类内部定义类自己的重载。但是这个地方并不一定要在类的内部重载new 的两种情况，因为 这是一个优先级的问题，当用户 即 main 中使用到关键字new的时候，会首先在当前即 类的内部寻找，再去找全局的。而这个过程对出现异常时 需要调用的delete 是没有关系的，只是简单的根据参数去匹配  当前 也证明了
		//所以 全局的delete 在重载的时候也不会去重载他的多参数版本。
		return malloc(size);
	}*/
	void operator delete(void* p,string name,int line){
		cout << name << "--" << line << endl;
		cout << "duo can delete " << endl;
		free(p);
	}

	/*void* operator new(size_t size,string name,int line){
		return malloc(size);
	}*/
	void operator delete(void *p){
		cout<<"dele----" << endl;
		free(p);
	}
};

#define new new(__FUNCTION__,__LINE__)
int main(){
	//MemoryNode *node = new MemoryNode;
	/*int *a = new int[10];
	vector<int> *v = new vector<int>;

	double *b = new double;
	*/

	int *xx = (int*)malloc(sizeof(int));

	*xx = 10;
	int *a = new int;
	int *b = new int;
	int *c = new int;

	
	delete c;
	delete a;
	delete b;

	
//	delete xx;
	free(xx);
	try{
		people *p;
		p = new people;
		delete p;
	}catch(...){
		cout << "catch" << endl;
	}

//	try{
//		int *a = new int;
//		int *b = new int;
//		int *c = new int;
//		//throw int(3);
////	delete a;
//		delete b;
//		delete a;
//		delete c;
//	}catch(...){
//		cout << "c" << endl;
//	}
//
//	if(gMemNode!=NULL){
//		cout << "..." << endl;
//	}

//	Node n = new MemoryNode;
//	delete n;
//	double *d = new double;
//	delete d;
//
//	cout << MemoryList.size() << endl;
}