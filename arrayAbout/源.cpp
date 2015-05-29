#include <iostream>
#include <vector>
#define Max(a,b) ( a/b)?a:b 
using namespace std;

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
		if(nums[mid]>=nums[(mid-1+length)%length]&&nums[mid]>nums[(mid+1)%length]){  //<=x<
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

int main(){
	int a[] ={0,0,-1,-1,0,0,0}; 
	vector<int> x(a,a+3);
	int xx= findMin_(x);
	cout << xx << endl;
}