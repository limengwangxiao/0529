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
		while (j>-1 &&temp<a[j])//为了操作的方便 需从后向前寻找当前 i 位置上的数需要插入的合适的位置 因tmp 记录下了i 位置上的数
						//i位置 空出位置， 一旦发现i前面的数比 tmp 大 则直接向后移动即可
		{
			a[j+1]=a[j];
			j--;
		}
		//跳出while有两种可能 1、j=-1  2、找到j使得a[j]<temp 且a[j+1+1]>temp
			//因此两种情况下都是讲temp 的值放到 j+1的位置上
		a[j+1]=temp;
	}
}

void select (int *a){
	int temp;
	int index;
	for(int i=0;i<10;i++){//为第i个位置选择一个数

		for(int j=i;j<10;j++){
			
			if(j==i){
				temp = a[j];//初始化最小值
				index = j;
			}else{
				if(a[j]<temp){
					temp =  a[j];
					index = j;
				}
			}
		}

		SWAP(a[index],a[i]); //交换最小值和当前位置上的值
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

	int temp = a[low];   //选出来的 中间值  该函数的目的是为了将序列中所有比中间值小的 放在序列的左边 
							//所有比中间值大的放在中间值的右边 并最终返回中间值的index
	while(low < high){    //外部的循环是为了将所有的 满足要求的值 移到适当的位置
		while((low < high)&&(a[high] > temp)){  //内部的两个循环只是为了找到一个 比中间值大或者比中间值小的 值 并移动
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
	if(l<r){ // 作为递归的终止条件
		int x = p(a,l,r);	//上面两种划分的方式
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
	if(a>b){  //自定义 比较大小的方法
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

	//除了这些常见排序之外，还有一些库提供的一些排序的方法
	//1、标准库中提供的sort函数
		//#include <algorithm>
	//	sort(r,r+10);
		//另外也可以指定比较大小的方法
	//	sort(r,r+10,compare<int>);
	//2、使用qsort
	//	qsort(r,10,sizeof(int),cmp);  这里的cmp 比较大小的判断是根据返回值的正负来判断的
	// 与STL中的sort一样 qsort 可以针对各种类型的数据进行排序
		//需要特别注意的是double 类型的数据
	for(int i=0;i<10;i++){
		cout << r[i] << endl;
	}
}