#ifndef __LEAK_H__
#define __LEAK_H__
#include <string>
#include<stdlib.h>
#include <iostream>
#include <list>
using namespace std;

/**

	好吧，折腾了一天，总结一下

		昨天看起来不懂的，主要是预处理的几个关键字，__FUNCTION__ __FILE__ __LINE__
		这样的几个预处理与_DEBUG 一样的，都是编译器预置的，具体的作用也是显而易见，
		
		首先对new 和 delete 的重载，对new delete和 malloc free
		之间的关系有了一个更加直观的了解， 重载的new 会对每一次的申请的位置 进行记录，然后加入到一个序列中
		对delete的重载，使得每一次的delete 都能够将 之前 new 对应的节点从序列中删除，并释放节点对应的内存
		除此之外 delete还必须保证基本的功能，即释放其他的内存，比如不是由new 得到的地址，有可能会由重载之后的
		delete 来释放  
		
		最后要想检查是否有内存泄露，需判断gMemNode 是否为空 

		此外对于 自动传参方法的实现
		使用#define 来实现的
		#define new new(__FUNCTION__,__LINE__) 但是 必须是在重载 new 之后 完成，否则会找不到 new（...)的定义
		对应的并不会对delete 函数内部传参
**/

typedef struct MemoryNode{
	string function_name;
	int line;
	void *address;
	MemoryNode * next;
}*Node;
static Node gMemNode = NULL;  
void add_memory_node(Node pMemNode)  
{  
    Node pNode = gMemNode;  
    if(NULL == pMemNode) return;  
    if(NULL == gMemNode){  
        gMemNode = pMemNode;  
        return;  
    }  
  
    while(NULL != pNode->next){  
        pNode = pNode->next;  
    }  
    pNode->next = pMemNode;  
    return;  
} 
void delete_memory_node(void* pAddress)  
{  
    Node pHead = gMemNode;  
    Node pMemNode = gMemNode;  
    while(NULL != pMemNode){  
        if(pAddress == pMemNode->address)  
            break;  
		pHead = pMemNode;
        pMemNode = pMemNode->next;  
    }  
    if(NULL == pMemNode) {  //没有找到相应的地址 表示所要释放的指针不是通过  自定义的new  的过程申请得到的
        return;   //则当前无需再此处释放address的内存，直接返回会直接释放内存
    }  
  
    if(pMemNode == gMemNode){  //当前只剩下一个节点 也被删除 则置gMemNode 的值为初始值 NULL 方便做是否有泄漏的判断
        gMemNode = gMemNode->next;  
    }else{  
        pHead->next = pMemNode->next;  
    }  
    free(pMemNode);  //删除内存节点
    return;  
}  

void operator delete(void *pUserData){
		cout << "normaml del" << endl;
		delete_memory_node(pUserData);  
		free(pUserData);
		pUserData = NULL;
}

void operator delete(void* p,string name,int line){
	cout << "duo can del" << endl;
}

void* operator new(size_t size,string name,int line){

#ifdef __NEEDP_ //可以在文件头设置
	cout << "new --" << name << "--" << line << endl;
#endif	


	void *pData = malloc(size);  //分配指定的空间
	memset(pData,0,size);  /*这里也是malloc 与 new 之间的一个区别，
								malloc 向堆中申请内存后，并不进行初始化的操作，而是直接返回给用户 
	   						    反观 new，虽然是由malloc() 函数间接的向堆申请一定大小的空间，同时在得到内存后，有一个 _callnewh 的过程
								虽然未能拿到源码，但根据注释 report no memory 可以推断出是在清除原来内存中的内容

								if (_callnewh(size) == 0)
								{       // report no memory
									_THROW_NCEE(_XSTD bad_alloc, );
								}

								所以由malloc 拿到内存，必须先清空，才能使用
								*/
	//throw int(3);
	MemoryNode* node = (MemoryNode*)malloc(sizeof(MemoryNode));  //分配节点空间
	memset(node,0,sizeof(MemoryNode));
	node->address = pData;
	node->function_name = name;
	node->line = line;  //设置当前节点的参数
	add_memory_node(node);

	return pData;
}

//#define new new(__FUNCTION__, __LINE__)
#endif