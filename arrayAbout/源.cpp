#include <iostream>
#include <vector>
#define SWAP(a,b) {int c=a;a=b;b=c;}
using namespace std;


//其他人写的 不是很明白
 int _find(vector<int> &num, int left, int right) //返回的是下标
    {
        if(left + 1 == right)
        {
            //cout<<"left = "<<left<<" right="<<right<<endl;
            return num[left]<num[right]?left:right;
        }
        
        int mid;
        while(left + 1 < right)
        {
            mid = (left + right)/2;
            
            if(num[mid] > num[left]) //转折点到右侧
                left = mid;
            else if (num[mid] < num[left]) //转折点在左侧
                right = mid;
            else //转折点不确定
            {
                int m1 = _find(num, left, mid);
                int m2 = _find(num, mid, right);
                return num[m1]<num[m2]?m1:m2;
            }
        }
        //cout<<"left = "<<left<<" right="<<right<<endl;
        return num[left]<num[right]?left:right;
    }

    int findMin(vector<int> &num)
    {
        int left, right;
        left = 0, right = (int)num.size()-1;
        int min = _find(num ,left, right);
        if(num[min] > num[0])
            min = 0;
        return num[min];
    }


	//对比局部极小值  设a[0] 与a[n] = MAX  则    a[mid] < a[mid+1]  前面一部分
											 //a[mid] > a[mid+1]  后面一部分
int findMin_(vector<int>& nums) {  
	int length = nums.size();
	int len = length;
	int l=0;
	if(nums[length-1]>nums[0]){  //直接顺序的情况
		return nums[0];
	}
	if(length==0){ //为空
		return 1000000;
	}
	if(length==1){ //就一个元素
		return nums[0];
	}
	if(length==2){ //两个元素
		return nums[0]>nums[1]?nums[1]:nums[0];
	}
 	while(1){   //二分
		int mid = (l+len)/2;
		if(nums[mid]>=nums[(mid-1+length)%length]&&nums[mid]>nums[(mid+1)%length]){  //<=x<  结束条件的判断是关键点 两个<=
			return nums[(mid+1)%length];
		}
		if(nums[mid]<nums[(mid-1+length)%length]&&nums[mid]<=nums[(mid+1)%length]){   //<x<=
			return nums[mid];
		}
		if(nums[mid]>nums[l]){  //mid>l  则 mid--l之间是有序的，要找无序的 则需到后面
			l = mid+1;
		}else if(nums[mid]<nums[l]){
			len = mid-1;
		}else{
			vector<int> xx(nums.begin()+l,nums.begin()+mid);
			int min_1 = findMin_(xx);
			vector<int> xxx(nums.begin()+mid,nums.begin()+len);
			int min_2 = findMin_(xxx);
			return min_1>min_2?min_2:min_1;
		}
	}
}


int findX(vector<int> & nums,int x){  //循环有序数组中查找指定元素
	int length = nums.size();
	int len = length-1;
	int l = 0;

	while(1){
		int mid = (l+len) / 2;
		if(nums[mid]==x){
			return mid;
		}
		if(nums[mid]>nums[l]&&x<=nums[mid]&&x>=nums[l]){  // a[l] < x << a[mid]
			 //直接二分
			return findX(vector<int>(nums.begin(),nums.begin()+mid),x);
		}else {  //在另一侧递归
			return findX(vector<int>(nums.begin()+mid,nums.end()),x);
		}
			
		if(nums[mid]<nums[len]&&x>=nums[mid]&&x<=nums[len]){  //a[mid] < x << a[len]
			return findX(vector<int>(nums.begin()+mid,nums.end()),x);
		}else{ 
			return findX(vector<int>(nums.begin(),nums.begin()+mid),x);
		}
	}
}

int findX_aX(vector<int> & nums){  //一个严格单增的序列中找到 x==a[x]的位置  严格单增的意思就是 不存在重复的元素 可以把 x 和 a[x] 看成两个指针， 其中x的速度恒定为1，但a[x]的速度不恒定 且速度比较 a[x] >= x
	int l=0;
	int r=nums.size()-1;
	while(1){
		int mid = (l+r)/2;
		if(mid==nums[mid]){
			return mid;
		}
		if(mid>nums[mid]){  //         mid
							// a[mid]  若此时再向前找 因a[mid] 的速度较快，故不可能在前面找到a[mid] == mid
			l = mid;        //故应向后寻找
		}else{  //mid < nums[mid]  向前寻找 
			r = mid;
		}
	}

}


//在一个数组中第一个缺失的正整数 
/* 1、 这个数肯定会是在1-n 之间的数,因假设对数组进行排序，不考虑负数，且不缺失的情况下 为a[i] = i+1; 因此缺失的只可能是 1-n 之间的数
2、理想的情况是a[i]==i+1; 则需要做的就是从第0个位置上开始，看 数组中是否存在 i+1, 直到找到第一个不存在的位置为止，这样的解法，分析一下时间复杂度为 O（n^2）
3、利用数组的交换。
				首先若一个数组的A[0--i]的位置上都满足 a[i] = i+1, a[j--n] 的位置上是未知的，需要从j开始做下面的判断：
	在数组中出现的  负数 和 >n 的数都是没用的，所以可以考虑去掉。另外重复的元素，只需保留一个就可以 不影响最后的结果，重复的情况 会出现在 i 的前面 和 后面， 所以上面的三种情况，可以考虑移除
*/
int firstMissingPositive(vector<int>& nums){ 
	int n = nums.size();
	for(int i=0;i<n;){
		if(nums[i]==i+1){
			i ++;
		}
		else if(nums[i]>n||  // >n 
				nums[i]<=i||  //重复出现的元素 且在前面  包括 负数
					nums[nums[i]-1]==nums[i] //重复出现的元素 且在后面
			){  //   移除该元素
			nums[i] = nums[n-1]; //把最后一个元素 换到前面 ，因i未改变，故当前还是待处理的状态
			n--;//元素个数 --  这样的移除元素的方法 不需要 逐步的位置变化，但会导致 数组的原来的顺序发生改变
		}else{  // 需要把当前的这个数a[i] 换到他应该在的位置上  即 i--；
			int xa=i;
			int xb=nums[i]-1;
			SWAP(nums[xa],nums[xb]);  //下一次的循环会判断 是否满足 a[i]=i+1的条件
		}
	}
	return n+1;
}

/*
	众数问题 (注意不是出现次数最多的数)
	众数的个数 > 所有其他非众数的个数和
	扔掉两个不同的数，众数不变
		扔掉两个非众数
		扔掉一个众数和一个非众数
*/
int zhongshu(vector<int> &nums){
	int count=0,x;
	for(int i=0;i<nums.size();i++){
		if(count==0){
			x=nums[i];
			count ++;
		}else if(nums[i]==x){  //模拟扔掉两个不同的数
			count ++;
		}else{
			count --;
		}
	}

	return x;
}

int main(){
	int a[] ={3,2,3,4,3,4,4,3,3}; 
	SWAP(a[0],a[1]);
	vector<int> x(a,a+9);
	int xx= zhongshu(x);
	cout << xx << endl;
}