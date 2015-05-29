#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 10000
#define SWAP1(a,b){a+=b;b=a-b;a-=b;}
#define SWAP(a,b){int tmp = a;a=b;b=tmp;}

using namespace std;

void bundle(int *a){
	for(int i=0;i<10;i++){
		for(int j=i+1;j<10;j++){
			if(a[i]<a[j]){
				SWAP1(a[i],a[j]);
			}
		}
	}
}
void merge(int *a,int l,int r, int m){

	vector<int> L;// m - l + 1;
	vector<int> R;// r - m;

	for(int i=0;i<m-l+1;i++){
		L.push_back(a[l+i]);
	}
	L.push_back(MAX);

	for(int i=0;i<r-m;i++){
		R.push_back(a[m+i+1]);
	}
	R.push_back(MAX);

	int i,j;
	i = j = 0;
	for(int k=l;k<=r;k++){
		if(L[i]<R[j]){
			a[k] = L[i];
			i ++;
		}else{
			a[k] = R[j];
			j ++;
		}
	}
}

void merge_sort(int *a, int l,int r){

	if(l<r){

		int m = (l + r) / 2;
		merge_sort(a,l,m);
		merge_sort(a,m+1,r);
		merge(a,l,r,m);
	}
}





void insert(int *a){
	int i,j;
	int n = 10;
	int temp;
	for (i=1;i<n;i++)
	{
		temp = a[i];
		j=i-1;
		while (j>-1 &&temp<a[j])//Ϊ�˲����ķ��� ��Ӻ���ǰѰ�ҵ�ǰ i λ���ϵ�����Ҫ����ĺ��ʵ�λ�� ��tmp ��¼����i λ���ϵ���
						//iλ�� �ճ�λ�ã� һ������iǰ������� tmp �� ��ֱ������ƶ�����
		{
			a[j+1]=a[j];
			j--;
		}
		//����while�����ֿ��� 1��j=-1  2���ҵ�jʹ��a[j]<temp ��a[j+1+1]>temp
			//�����������¶��ǽ�temp ��ֵ�ŵ� j+1��λ����
		a[j+1]=temp;
	}
}

void select (int *a){
	int temp;
	int index;
	for(int i=0;i<10;i++){//Ϊ��i��λ��ѡ��һ����

		for(int j=i;j<10;j++){
			
			if(j==i){
				temp = a[j];//��ʼ����Сֵ
				index = j;
			}else{
				if(a[j]<temp){
					temp =  a[j];
					index = j;
				}
			}
		}

		SWAP(a[index],a[i]); //������Сֵ�͵�ǰλ���ϵ�ֵ
	}
}

int p(int *a, int l, int r){


	int x = a[r];

	while(l<r){
		while(l<r&&a[l]<x){
			l ++;
		}
		a[r] = a[l];
		while(l<r&&a[r]>x){
			r --;
		}
		a[l] = a[r];
	}

	a[l] = x;  
	return l;  
}

int partation(int *a, int low, int high){

	int temp = a[low];   //ѡ������ �м�ֵ  �ú�����Ŀ����Ϊ�˽����������б��м�ֵС�� �������е���� 
							//���б��м�ֵ��ķ����м�ֵ���ұ� �����շ����м�ֵ��index
	while(low < high){    //�ⲿ��ѭ����Ϊ�˽����е� ����Ҫ���ֵ �Ƶ��ʵ���λ��
		while((low < high)&&(a[high] > temp)){  //�ڲ�������ѭ��ֻ��Ϊ���ҵ�һ�� ���м�ֵ����߱��м�ֵС�� ֵ ���ƶ�
			high--;  
		} 
		a[low] = a[high];  
		while((low < high)&&(a[low] < temp)){  
			low++;  
		} 
		a[high] = a[low];  
	}  
	a[low] = temp;  
	return low;  
}

void quick(int *a,int l, int r){
	if(l<r){ // ��Ϊ�ݹ����ֹ����
		int x = p(a,l,r);	//�������ֻ��ֵķ�ʽ
		quick(a,l,x-1);
		quick(a,x+1,r);
	}
}
//#include "utils.h"
#include <ctime>
#include <cstdlib>

int random(int start, int end){

	return start +rand() % (end - start);
}
double random(){
	
	float tmp = 0.1;
	float d = 0;
	float f[6];
	for(int i=0;i<6;i++){
		f[i] = 0 + rand() % (10);
		d = d + f[i] * tmp;
		tmp *= 0.1;
	}
	return d;
}

template <class T>
int compare(T a, T b){
	if(a>b){  //�Զ��� �Ƚϴ�С�ķ���
		return 1;
	}else{
		return 0;
	}
}

int cmp ( const void *a , const void *b )
{ return *(int *)a - *(int *)b; }

int main(){

	int r[10] ={1,9,8,7,688,5,4,3,2,10};
	int a,b;
	a = 1,b=2;
	SWAP(a,a);
	cout << a << "--" <<b<<endl;
//	quick(r,0,9);
//	merge_sort(r,0,9);
//	insert(r);
//	select(r);
//  bundle(r);

	//������Щ��������֮�⣬����һЩ���ṩ��һЩ����ķ���
	//1����׼�����ṩ��sort����
		//#include <algorithm>
	//	sort(r,r+10);
		//����Ҳ����ָ���Ƚϴ�С�ķ���
	//	sort(r,r+10,compare<int>);
	//2��ʹ��qsort
	//	qsort(r,10,sizeof(int),cmp);  �����cmp �Ƚϴ�С���ж��Ǹ��ݷ���ֵ���������жϵ�
	// ��STL�е�sortһ�� qsort ������Ը������͵����ݽ�������
		//��Ҫ�ر�ע�����double ���͵�����
	for(int i=0;i<10;i++){
		cout << r[i] << endl;
	}
}