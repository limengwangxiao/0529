#include <iostream>
#include <algorithm>
using namespace std;
#include<string>

void f2(int *a){
	for(int i=0;i<1000;i++){
		cout << i <<"--" << a[i] <<endl;
	}
}

int f1(int *a, int low, int high, int key){
	if(low>high){
		return -1;
	}
	int mid = low +  (key - a[low]) / (a[high] - a[low]) * (high - low);
	if(a[mid]==key){
		return mid;
	}else if(a[mid]>key){
		return f1(a,low,mid-1,key);
	}else{
		return f1(a,mid+1,high,key);
	}

	

	return -1;

}

int chazh_find(int *a, int low, int high, int key){
	while(low <= high)  
	{  
		int mid = low +  (key - a[low]) / (a[high] - a[low]) * (high - low) ; //此处于二分查找不同,套用插值公式  
		if(a[mid] > key)         //如果key比插值小,把高位调整为插值下标的下一位            
			high = mid - 1;                           
		else if(a[mid] < key)  
			low = mid + 1;  
		else  
			return mid;  
	}  
	return -1;  
}

int cmp( const void *a , const void *b ) 
{ 
	return *(char *)a - *(char *)b; 
} 

int bj(char a, char b){
	if(a<b){
		return 1;
	}else{
		return 0;
	}
}
int main(){



	//int a[10] = {1,3,4,5,6,7,8,9,10,15};
	//f1(a,0,0,0);
//	cout <<f1(a,0,9,15) << endl;
//	f2(a);

	return 0;
}