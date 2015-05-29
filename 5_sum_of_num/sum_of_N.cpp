#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
using namespace std;

/*��Ŀ������һ�������һ�����֣��������в�����������ʹ�����ǵĺ�������������Ǹ����֡�
Ҫ��ʱ�临�Ӷ���O(n)������ж�����ֵĺ͵�����������֣��������һ�Լ��ɡ�
������������1��2��4��7��11��15������15������4+11=15��������4��11��*/

//1��ֱ����ٷ����������������ȡ�������������жϺ��Ƿ�Ϊ�Ǹ����֣��˾ٸ��Ӷ�ΪO��N^2����


//2��ת��һ��˼·���Ѽӷ���ɼ�����ԭ�������������ĺͣ�������������е�һ����a[i]����֪ �� X�� ���Ϊ�������в���X-a[i] �Ƿ���ڣ�  //ÿһ�� ���Ҷ�Ҫ O��N����Ҫ��߲��ҵ�Ч�ʣ����Կ��Ƕ��ֲ��ң���������ֱ�Ӷ��ֲ���-O��N*logN��,����Ļ����������ٶ��֣�O��N*logN+N*logN������  �ܽ�:���ֲ��ҵ�ʱ�临�ӶȾ�ΪO��N*logN��

//3��������ָ��i��j������ָ���������β���ˣ���i=0��j=n-1��Ȼ��i++��j--������ж�a[i]+a[j]?=sum�����ĳһ��a[i]+a[j]>sum����Ҫ��취��sum��ֵ��С�����Դ˿�i������j--�����ĳһ��a[i]+a[j]<sum����Ҫ��취��sum��ֵ�������Դ˿�i++��j���������ԣ����������ʱ��ʱ�临�Ӷ�����ΪO��n*logn+n��=O��n*logn������ԭ����������ģ�����Ҫ���ȵ�����ֱ��O��n���㶨���ҿռ临�ӶȻ���O��1������˼·���������������˼·��һ�ָĽ������������ֱ������ָ������ɨ�裬ʱ��O��N����������������������ɨ�裬ʱ��O��N*logN+N��=O��N*logN�����ռ�ʼ�ն�ΪO��1��������������˼·2��ȣ�������ʱ�俪����֮ǰ�Ķ��ֵ�n*logn������ɨ���O��N������




//4��Ȼ�����ڸı���Ŀ��Ҫ��������������ӵĺ�ΪN����Ϊ
//	������������ n �� m��������1��2��3.......n �� ����ȡ������,
//ʹ��͵��� m ,Ҫ���������еĿ�������г�����
//����һ�����͵� 0-1 �������⣬����1-n �����֣�ÿһ������Ҫô����ӷ���Ҫô�����룬��ʼ�����µ�ǰn���Լӵ����У��������ֵĵݹ飬��û�дﵽ������������ǰ����û��������һ�μ����n���Լ��룻��sum=0 ���ʾ ��ǰ���еĶ����Ѿ����ˣ��򷵻� �� sum==n ���ʾ����֮ǰ�����ϵ�ֵ n ʹ�� sum ���ˣ����ʾ�ҵ�һ������� sum< �򷵻غ󣬵õ�n!=sum�����ʾ��һ�μ���n֮��ʹ��sum���ˣ���ʾ��һ�εĳ���ʧ�ܣ���һ�ε�n�����Լ��뵽bao�У����n�ó����ٽ�����һ�εĵݹ顣



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
void fun_3(int *a,int N,int size){ //��Ӧ˼·3
	
	int i=0,j=size-1;

	while(i<size&&j>=0&&i<j){  //��ͷ�б�
		//�˴�i<j ������Ϊһ���������������򴫽������ź���������У���Ҫ�ҵ��Ľ��Ȼ�Ƿֲ������еġ����ˡ�����������˲�����ʵ�������ϸ���λ�����õ������ˣ�����˵ ��������ˣ��� 467778889��46 ��Ȼ����һ�ˣ������ڶ�4�ҶԶ���ʱ�򣬲�����6֮ǰ�õ���֮ƥ���ֵ�� ����i<j ��һ�������������в������ظ�ֵ������£����ᶪʧ�⣬�������ظ�ֵ��ʱ�򣬻ᶪ��һ���ֽ⣬�����ᶪʧ������ࡣ
		if(a[i]+a[j]==N){ 
			cout << "getOne" ;
			cout << i <<"--"<< j << "--";
			cout << a[i] << "--" << a[j] << endl;
			i++;
			j--;
		//	break;	
		}else if(a[i]+a[j]>N){ //���ߵĺ͹��� ����N  ��  a[j] ����  j-- Ѱ�Ҹ�С�� j
			j--;
		}else{  //a[i]+a[j] < N  a[i] ��С i++
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
                j--;  //�͵�ֵ���� ��Ҫ���͸�ֵ
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

	fun(xx,nums,0,8,index); //��������ĺ�Ϊ����ֵ�Ľⷨ������ 
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
                j--;  //�͵�ֵ���� ��Ҫ���͸�ֵ
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




