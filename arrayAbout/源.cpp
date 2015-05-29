#include <iostream>
#include <vector>
using namespace std;
int findMin(vector<int>& nums) {
	int len = nums.size();
	int length = len;
	if(len==1){
		return nums[0];
	}
	int l=0;
	while(1){
		int mid = (l+len)/2;
		if(nums[mid]>nums[mid-1]&&nums[mid]>nums[(mid+1)%length]){
			return nums[(mid+1)%length];
		}
		if(nums[mid]<nums[mid-1]&&nums[mid]<nums[(mid+1)%length]){
			return nums[mid];
		}

		if(nums[mid]>nums[l]){
			l = mid+1;
			//len = len;
		}else{
			//l = l;
			len = mid-1;
		}
	}
}

int main(){
	int a[] ={1};
	vector<int> x(a,a+1);
	cout << findMin(x);
}