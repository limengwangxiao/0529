#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
using namespace std;

/*题目：输入一个数组和一个数字，在数组中查找两个数，使得它们的和正好是输入的那个数字。
要求时间复杂度是O(n)。如果有多对数字的和等于输入的数字，输出任意一对即可。
例如输入数组1、2、4、7、11、15和数字15。由于4+11=15，因此输出4和11。*/

//1、直接穷举法，从数组中任意的取两个数出来，判断和是否为那个数字，此举复杂度为O（N^2）。


//2、转化一下思路，把加法变成减法，原来是求两个数的和，现在针对序列中的一个数a[i]，已知 和 X， 则变为在序列中查找X-a[i] 是否存在，  //每一次 查找都要 O（N）；要提高查找的效率，可以考虑二分查找（若有序，则直接二分查找-O（N*logN）,无序的话，先排序再二分（O（N*logN+N*logN）））  总结:二分查找的时间复杂度均为O（N*logN）

//3、用两个指针i，j，各自指向数组的首尾两端，令i=0，j=n-1，然后i++，j--，逐次判断a[i]+a[j]?=sum，如果某一刻a[i]+a[j]>sum，则要想办法让sum的值减小，所以此刻i不动，j--，如果某一刻a[i]+a[j]<sum，则要想办法让sum的值增大，所以此刻i++，j不动。所以，数组无序的时候，时间复杂度最终为O（n*logn+n）=O（n*logn），若原数组是有序的，则不需要事先的排序，直接O（n）搞定，且空间复杂度还是O（1），此思路是相对于上述所有思路的一种改进。（如果有序，直接两个指针两端扫描，时间O（N），如果无序，先排序后两端扫描，时间O（N*logN+N）=O（N*logN），空间始终都为O（1））。（与上述思路2相比，排序后的时间开销由之前的二分的n*logn降到了扫描的O（N））。




//4、然而现在改变题目，要求不在是两个数相加的和为N，改为
//	输入两个整数 n 和 m，从数列1，2，3.......n 中 随意取几个数,
//使其和等于 m ,要求将其中所有的可能组合列出来。
//这是一个典型的 0-1 背包问题，对于1-n 的数字，每一个数字要么参与加法，要么不参与，初始条件下当前n可以加到包中，尝试下轮的递归，若没有达到返回条件，则当前包还没有满，上一次加入的n可以加入；若sum=0 则表示 当前包中的东西已经满了，则返回 看 sum==n 则表示返回之前最后加上的值 n 使得 sum 满了，则表示找到一种情况， sum< 则返回后，得到n!=sum，则表示上一次加上n之后，使得sum超了，表示上一次的尝试失败，上一次的n不可以加入到bao中，则把n拿出，再进行下一次的递归。



void fun_4(vector<int>& v, int sum, int n){
	if(sum<=0||n<=0){
		return ;
	}
	v.push_back(n);
	fun_4(v,sum-n,n-1);
	if(sum==n){
		for(int i=0;i<v.size();i++){
			cout << v[i] << "--";
		}
		cout << endl;
	}
	v.pop_back();
	fun_4(v,sum,n-1);
}




static int cou11nt = 0;
void fun_3(int *a,int N,int size){ //对应思路3
	
	int i=0,j=size-1;

	while(i<size&&j>=0&&i<j){  //两头夹逼
		//此处i<j 可以做为一个结束的条件，因传进的是排好序的数数列，所要找到的解必然是分布在序列的“两端”，这里的两端并不是实际意义上根据位置来得到的两端，而是说 有序的两端，如 467778889，46 虽然是在一端，但是在对4找对儿的时候，不会在6之前得到与之匹配的值。 加上i<j 这一条件，在序列中不存在重复值的情况下，不会丢失解，当存在重复值的时候，会丢是一部分解，但不会丢失解的种类。
		if(a[i]+a[j]==N){ 
			cout << "getOne" ;
			cout << i <<"--"<< j << "--";
			cout << a[i] << "--" << a[j] << endl;
			i++;
			j--;
		//	break;	
		}else if(a[i]+a[j]>N){ //两者的和过大 超过N  则  a[j] 过大  j-- 寻找更小的 j
			j--;
		}else{  //a[i]+a[j] < N  a[i] 过小 i++
			i++;
		}
		cout << cou11nt++ << endl;
	}
}

int partition(int *a,int l,int r){

	int x=a[l];
	while(l<r){
		while(l<r&&a[r]>x){
			r--;
		}
		a[l] = a[r];
		while(l<r&&a[l]<=x){
			l++;
		}
		a[r] = a[l];
	}
	a[l] =x;
	return l;
}

void quick_sort(int *a, int l, int r){
	if(l<r){
		int mid = partition(a,l,r);
		quick_sort(a,l,mid-1);
		quick_sort(a,mid+1,r);
	}
	return ;
}
 vector<int> twoSum(vector<int>& nums, int target) {
	 vector<int> copy=nums;
	 quick_sort(&nums[0],0,nums.size()-1);
	 int high=nums[nums.size()-1];
	 int lo=nums[0];
	 vector<vector<int>> hash(high-lo+1);
	 for(int i=0;i<copy.size();i++){
		 hash[copy[i]-lo].push_back(i);
	 }



        vector<int> x;
        for(int i=0,j=nums.size()-1;i<j;){
            if(nums[i]+nums[j]==target){
                //if(nums[i]>n)
				x.clear();
				if(nums[i]==nums[j]){
					x.push_back(hash[nums[i]-lo][0]+1);
					x.push_back(hash[nums[j]-lo][1]+1);
				}else{
					x.push_back(hash[nums[i]-lo][0]+1);
					x.push_back(hash[nums[j]-lo][0]+1);
				}
				if(x[0]>x[1]){
					int t=x[0];
					x[0]=x[1];
					x[1]=t;
				}
                return x;
            }else if(nums[i]+nums[j]>target){  
                j--;  //和的值超了 需要降低该值
            }else{
                i++;
            }
        }
    }


void fun(vector< vector<int> >& xx, vector<int>& nums,int i,int target,vector<int>&index) {
	if(i>=nums.size()){
		return;
	}
	index.push_back(nums[i]);
	target-=nums[i];
	if(target==0){
		xx.push_back(index);
	}
	fun(xx,nums,i+1,target,index);
	index.pop_back();
	target+=nums[i];
	fun(xx,nums,i+1,target,index);
}
vector<vector<int>> NSum(vector<int>& nums) { 
	vector<vector<int>> xx;
	vector<int> index;

	fun(xx,nums,0,8,index); //任意个数的和为任意值的解法，搜索 
	return xx;
}


void twoSum(vector<int>& nums, int target,vector<vector<int>>& xx,int index) {
    for(int i=index+1,j=nums.size()-1;i<j;){
            if(nums[i]+nums[j]==target){
                vector<int> x;
				
				x.push_back(nums[i]);
				x.push_back(nums[j]);
				x.push_back(-target);
				sort(x.begin(),x.end());
				xx.push_back(x);
				i++;
				j--;
			   // while(i < nums.size() && nums[i]==nums[i - 1]) i++;    
             //   while(j >= 0 && nums[j] == nums[j + 1]) j--; 
            }else if(nums[i]+nums[j]>target){  
                j--;  //和的值超了 需要降低该值
            }else{
                i++;
            }
        }
    }


vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> xx;
    if(nums.size()<3){
        return xx;
    }
    sort(nums.begin(),nums.end());
    for(int i=0;i<nums.size();i++){
        if(i>0&&nums[i]==nums[i-1]){
            continue;
        }
	    twoSum(nums,-nums[i],xx,i);
    }
	return xx;
}

int main(){
	//-1 0 1 2 -1 -4
	vector<int> x;
	x.push_back(10);
	x.push_back(1);
	x.push_back(2);
	x.push_back(7);
	x.push_back(6);
	x.push_back(1);
	x.push_back(5);
	NSum(x);
	/*int N = 10;
	string s = "657465413212327543200894353432120";
	cout << s.size() << endl;
	cout << s.length() << endl;
	sort(s.begin(),s.end());
	cout << s << endl;
	int *a = new int[s.length()];
	for(int i=0;i<s.length();i++){
		a[i] = s[i] - '0';
	}
	fun_3(a,N,s.length());



	delete []a;
	return 0;*/
}




