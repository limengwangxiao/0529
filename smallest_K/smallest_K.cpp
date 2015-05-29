
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define SWAP(a,b){int tmp=a;a=b;b=tmp;}
#define K 0


/************************************************************************/
/*  题目描述：查找最小的k个元素
		题目：输入n个整数，输出其中最小的k个。
		例如输入1，2，3，4，5，6，7和8这8个数字，则最小的4个数字为1，2，3和4。
		
		1、对原序列进行排序，输出前k个数 根据排序的时间复杂度 为 O（n^2） 或 O（nlogN） 
		2、无需对整个序列进行排序，只需在原来无序的数组中选出 k个最小的即可，每次在无序中查找最小的 需遍历 n次 共需进行k次查找
					则O（n*k）
		3、维护一个k个元素的最小堆,初始将任意K个元素建堆，并认为他们是最小的k个数，再依次比较剩下的元素，
					更新堆或者不更新，最后堆中的元素就是结果。（？）
		4、类似快速排序中的划分过程，上述2、3 两个过程实际上最后输出的K个元素都是有序的，这在某种程度上也是一种浪费，
				因此，可以对比快排的划分过程， 若返回的mid 值 正好==K 则前K 个数正好是需要的结果，另外两种情况，递归继续进行。
				此过程的效率受到 划分中枢纽元素

		同理将最小的K 个数转化为最大的K个数 同理
		此外寻找第K大的数, 其实上面的问题就是由TOP K 转化过来的，在找到TOP K 之后再在原序列中线性的寻找K个数即可 

		5、在STL 也对 top K 问题给出了一个解法，同样是利用划分的过程， 比较重要的部分也是在划分过程中枢纽点的选取
			在SGI STL 中 选取的是 当前 第K 个和 首尾  三个数中最小的点做为枢纽点  _algo.c 83 行
		6、既然确定枢纽点的选取是影响时间复杂度的关键因素，则还有另外的一种选择枢纽点的方法  BFPRT 
		BFPRT  可以称为 “五分化中项的中项”，或“中位数的中位数” 或者 median-of-medians （ median 中位数）
			BFPRT 解决的正好是在无序的数组中寻找第K 小的数 可以分成两个大的步骤
			1、 一种特殊的寻找枢纽元素的方法
			2、 根据找到的枢纽元素对序列进行划分

				

				getMedian();

		1、将arr中的n个元素划分成n/5组，每组5个元素，如果最后的组不够5个元素，那么最后剩下的元素为一组(n%5个元素)
		2、对每个组进行插入排序(只是每个组最多5个元素之间的组内排序，组与组之间并不排序)，排序后找到每个组的中位数，如果组的元素个数			为偶数，统一找到下中位数。
		3、步骤2中一共会找到n/5个中位数，让这些中位数组成一个新的数组，记为medianArr。递归调用getMedian
(medianArr,medianArr.length/2)，意义是找到medianArr这个数组中的中位数(median中的第(medianArr.length/2)小的数)。


4、getMedian中得到的枢纽 划分
			
																	*/
/************************************************************************/


int getTopK(int *l,int *r,int x){ //找到每一个个数为5 的序列中第3小的数 作为当前序列的中位数

//#ifdef _DEBUG
//	for(int *i=l;i!=r;i++){
//		cout << *i << "--" << endl;
//	}
//	cout << endl;
//#endif
	int count = 0;
	int max;
	int maxIndex;
	int *i=l;
	while(count < x){
		for(;i!=r;i++){
			if(i==l+count){
				max = *i;
				maxIndex = i-l;
			}else if(max < *i){
				max = *i;
				maxIndex = i-l;
			}
		}
		//找打当前序列中的最大值 交换到最前面
		SWAP(*(l+maxIndex),*(l+count));
		count ++;
		i=l+count;
	}

	return maxIndex;
}

int medianOfmedian(int *a, int l,int r,int k){

	vector<int> tmp;
	int i;
	for(i=l;i<=r-5;i+=5){ //最后会剩下一组小于5个的序列
		getTopK(a+i,a+i+5,3);
		int x = a[i+2];
		tmp.push_back(x);
	}


	if(r-i==4){  //最后剩下的元素的个数仍为5个
		getTopK(a+i,a+i+5,3);
		int x = a[i+2];
		tmp.push_back(x);
	}else {
		int index = ((float)(r-i+1))/2+0.5-1;
		//     Kth   index
		//    1---1    0
		//	  2---2    0
		//	  3---2    1
		//	  4---3    1
		int Kth = r-i+1-index;
		getTopK(a+i,a+r+1,Kth);
		tmp.push_back(a[i+index]);

	}

	if(tmp.size()==1){
		return tmp[0];
	}else{
		medianOfmedian(&(tmp[0]),0,tmp.size()-1,k);
	}

	return 0;
}

int q_select_1(int *a,int l, int r){
	//另一种选取枢纽元素的方法是 在原序列中随机选取一个元素作为枢纽
	int x = K;
	cout << x << endl;
	while(l<r){
		while(a[r]>=x){
			r --;
		}
		while(a[l]<x){
			l++;
		}
		if(l<r){
			SWAP(a[l],a[r]);
		}
	}

	cout<<l <<endl;

	return l;
}


void print(int k,int *a){
	for(int i=0;i<k;i++){
		cout << a[i] << "--";
	}
	cout << endl;
}

int q_select(int *a,int l, int r,int k){ 

	int low = l;
	int high = r;

	int x = a[l];//枢纽元素  与快速排序一致的是 觉得算法效率的因素就是枢纽的选取
				// 此处直接选取 第一个元素作为枢纽  然而有多种选取枢纽的方法
	while(l<r){
		while(l<r&&a[r]>=x){
			r --;
		}
		a[l] = a[r];
		while(l<r&&a[l]<x){
			l ++;
		}
		a[r] = a[l];
	}
	a[l] = x;
	cout << low <<"--" <<high <<"--" <<l << endl;
	print(k,a);

#ifdef _DEBUG  //目前的理解就是 无论是#if 还是#ifdef _DEBUG的效果都是一样的，且无论调试与否，只要生成是在Debug条件下生成的
				//则在编译阶段会将这段代码编译出来，（最后执行的代码 预处理阶段已经去除） 
				//而在Release 条件下生成的则不会编译这段代码
	cout << "DEBUG" << endl;
#endif // _DEBUG

	int mid = l;
	if(mid==k){  //正好 a[mid] + 前 mid-1（k-1） 个数
		print(k,a);
		return mid;
	}else if(mid==k+1){ //正好 mid 前 k 个数
		print(k,a);
		return mid;
	}else if(mid > k){
		return q_select(a,low,mid-1,k);
	}else if(mid < k){
		return q_select(a,mid+1,high,k);
	}
	return l;
}
#include <algorithm>
int main(){

	string s = "1865273496123";
	cout << s << endl;
	
	int *a = new int[s.length()];

	for(int i=0;i<s.length();i++){
		a[i] = s[i] - '0';
	}

	int k = 5;

	medianOfmedian(a,0,s.length()-1,k);

/*
	int mid = q_select(a,0,s.length()-1,k);

	for(int i=0;i<s.length();i++){
		cout << i % 10 <<"--";
	}
	cout<< endl;
	for(int i=0;i<s.length();i++){
		cout << a[i] <<"--";
	}

	sort(a,a+s.length());
	cout<< endl;*/


	nth_element<int*>(a,a+k,a+s.length());
	cout << endl;

	for(int i=0;i<k;i++){
		cout << a[i] <<"--";
	}
	
	cout << endl;
	for(int i=0;i<s.length();i++){
		cout << a[i] <<"--";
	}

	delete []a;
	return 1;
}	