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
		//�빹�������һ�����ǣ�new��delete Ҫ�����һ�£�
			//��ĳ��new�Ĺ���ʹ�õ�new���������ڹ����е�ĳ��ʱ�̳����쳣����ֹ������̵Ļ�������Զ�ɾ�������Ѿ���ɵĹ��죬�������������ľ�����new������Ӧ����ͬ��delete���ء������ɹ�����ɹ��죬��˺�Ĺ��̶������õ����Ӳ�����delete���� ����Ҳ�ǱȽϺ����ģ���Ϊ����û����ɣ�ֻ������new �ķ�����delete ȥ���
				//����������� ��people����Ӧ�������������������ĺ͵��������ģ���4�������������ˣ��ڲ��Ե�ʱ�򣬴���һ�� �жϹ������� ������ ���캯�����׳��쳣��ʹ������ֹ�����ʱ��ȥ���ö�Ӧ������delete  

		//���� Ŀǰ�����������delete ���أ�ֻ���������ĳ���ʹ�õ����������ڲ��������Լ������ء���������ط�����һ��Ҫ������ڲ�����new �������������Ϊ ����һ�����ȼ������⣬���û� �� main ��ʹ�õ��ؼ���new��ʱ�򣬻������ڵ�ǰ�� ����ڲ�Ѱ�ң���ȥ��ȫ�ֵġ���������̶Գ����쳣ʱ ��Ҫ���õ�delete ��û�й�ϵ�ģ�ֻ�Ǽ򵥵ĸ��ݲ���ȥƥ��  ��ǰ Ҳ֤����
		//���� ȫ�ֵ�delete �����ص�ʱ��Ҳ����ȥ�������Ķ�����汾��
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