#ifndef __LEAK_H__
#define __LEAK_H__
#include <string>
#include<stdlib.h>
#include <iostream>
#include <list>
using namespace std;

/**

	�ðɣ�������һ�죬�ܽ�һ��

		���쿴���������ģ���Ҫ��Ԥ����ļ����ؼ��֣�__FUNCTION__ __FILE__ __LINE__
		�����ļ���Ԥ������_DEBUG һ���ģ����Ǳ�����Ԥ�õģ����������Ҳ���Զ��׼���
		
		���ȶ�new �� delete �����أ���new delete�� malloc free
		֮��Ĺ�ϵ����һ������ֱ�۵��˽⣬ ���ص�new ���ÿһ�ε������λ�� ���м�¼��Ȼ����뵽һ��������
		��delete�����أ�ʹ��ÿһ�ε�delete ���ܹ��� ֮ǰ new ��Ӧ�Ľڵ��������ɾ�������ͷŽڵ��Ӧ���ڴ�
		����֮�� delete�����뱣֤�����Ĺ��ܣ����ͷ��������ڴ棬���粻����new �õ��ĵ�ַ���п��ܻ�������֮���
		delete ���ͷ�  
		
		���Ҫ�����Ƿ����ڴ�й¶�����ж�gMemNode �Ƿ�Ϊ�� 

		������� �Զ����η�����ʵ��
		ʹ��#define ��ʵ�ֵ�
		#define new new(__FUNCTION__,__LINE__) ���� ������������ new ֮�� ��ɣ�������Ҳ��� new��...)�Ķ���
		��Ӧ�Ĳ������delete �����ڲ�����
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
    if(NULL == pMemNode) {  //û���ҵ���Ӧ�ĵ�ַ ��ʾ��Ҫ�ͷŵ�ָ�벻��ͨ��  �Զ����new  �Ĺ�������õ���
        return;   //��ǰ�����ٴ˴��ͷ�address���ڴ棬ֱ�ӷ��ػ�ֱ���ͷ��ڴ�
    }  
  
    if(pMemNode == gMemNode){  //��ǰֻʣ��һ���ڵ� Ҳ��ɾ�� ����gMemNode ��ֵΪ��ʼֵ NULL �������Ƿ���й©���ж�
        gMemNode = gMemNode->next;  
    }else{  
        pHead->next = pMemNode->next;  
    }  
    free(pMemNode);  //ɾ���ڴ�ڵ�
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

#ifdef __NEEDP_ //�������ļ�ͷ����
	cout << "new --" << name << "--" << line << endl;
#endif	


	void *pData = malloc(size);  //����ָ���Ŀռ�
	memset(pData,0,size);  /*����Ҳ��malloc �� new ֮���һ������
								malloc ����������ڴ�󣬲������г�ʼ���Ĳ���������ֱ�ӷ��ظ��û� 
	   						    ���� new����Ȼ����malloc() ������ӵ��������һ����С�Ŀռ䣬ͬʱ�ڵõ��ڴ����һ�� _callnewh �Ĺ���
								��Ȼδ���õ�Դ�룬������ע�� report no memory �����ƶϳ��������ԭ���ڴ��е�����

								if (_callnewh(size) == 0)
								{       // report no memory
									_THROW_NCEE(_XSTD bad_alloc, );
								}

								������malloc �õ��ڴ棬��������գ�����ʹ��
								*/
	//throw int(3);
	MemoryNode* node = (MemoryNode*)malloc(sizeof(MemoryNode));  //����ڵ�ռ�
	memset(node,0,sizeof(MemoryNode));
	node->address = pData;
	node->function_name = name;
	node->line = line;  //���õ�ǰ�ڵ�Ĳ���
	add_memory_node(node);

	return pData;
}

//#define new new(__FUNCTION__, __LINE__)
#endif