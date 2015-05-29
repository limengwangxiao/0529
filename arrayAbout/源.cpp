#include <iostream>
#include <vector>
#define SWAP(a,b) {int c=a;a=b;b=c;}
using namespace std;


//������д�� ���Ǻ�����
 int _find(vector<int> &num, int left, int right) //���ص����±�
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
            
            if(num[mid] > num[left]) //ת�۵㵽�Ҳ�
                left = mid;
            else if (num[mid] < num[left]) //ת�۵������
                right = mid;
            else //ת�۵㲻ȷ��
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


	//�ԱȾֲ���Сֵ  ��a[0] ��a[n] = MAX  ��    a[mid] < a[mid+1]  ǰ��һ����
											 //a[mid] > a[mid+1]  ����һ����
int findMin_(vector<int>& nums) {  
	int length = nums.size();
	int len = length;
	int l=0;
	if(nums[length-1]>nums[0]){  //ֱ��˳������
		return nums[0];
	}
	if(length==0){ //Ϊ��
		return 1000000;
	}
	if(length==1){ //��һ��Ԫ��
		return nums[0];
	}
	if(length==2){ //����Ԫ��
		return nums[0]>nums[1]?nums[1]:nums[0];
	}
 	while(1){   //����
		int mid = (l+len)/2;
		if(nums[mid]>=nums[(mid-1+length)%length]&&nums[mid]>nums[(mid+1)%length]){  //<=x<  �����������ж��ǹؼ��� ����<=
			return nums[(mid+1)%length];
		}
		if(nums[mid]<nums[(mid-1+length)%length]&&nums[mid]<=nums[(mid+1)%length]){   //<x<=
			return nums[mid];
		}
		if(nums[mid]>nums[l]){  //mid>l  �� mid--l֮��������ģ�Ҫ������� ���赽����
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


int findX(vector<int> & nums,int x){  //ѭ�����������в���ָ��Ԫ��
	int length = nums.size();
	int len = length-1;
	int l = 0;

	while(1){
		int mid = (l+len) / 2;
		if(nums[mid]==x){
			return mid;
		}
		if(nums[mid]>nums[l]&&x<=nums[mid]&&x>=nums[l]){  // a[l] < x << a[mid]
			 //ֱ�Ӷ���
			return findX(vector<int>(nums.begin(),nums.begin()+mid),x);
		}else {  //����һ��ݹ�
			return findX(vector<int>(nums.begin()+mid,nums.end()),x);
		}
			
		if(nums[mid]<nums[len]&&x>=nums[mid]&&x<=nums[len]){  //a[mid] < x << a[len]
			return findX(vector<int>(nums.begin()+mid,nums.end()),x);
		}else{ 
			return findX(vector<int>(nums.begin(),nums.begin()+mid),x);
		}
	}
}

int findX_aX(vector<int> & nums){  //һ���ϸ������������ҵ� x==a[x]��λ��  �ϸ�������˼���� �������ظ���Ԫ�� ���԰� x �� a[x] ��������ָ�룬 ����x���ٶȺ㶨Ϊ1����a[x]���ٶȲ��㶨 ���ٶȱȽ� a[x] >= x
	int l=0;
	int r=nums.size()-1;
	while(1){
		int mid = (l+r)/2;
		if(mid==nums[mid]){
			return mid;
		}
		if(mid>nums[mid]){  //         mid
							// a[mid]  ����ʱ����ǰ�� ��a[mid] ���ٶȽϿ죬�ʲ�������ǰ���ҵ�a[mid] == mid
			l = mid;        //��Ӧ���Ѱ��
		}else{  //mid < nums[mid]  ��ǰѰ�� 
			r = mid;
		}
	}

}


//��һ�������е�һ��ȱʧ�������� 
/* 1�� ������϶�������1-n ֮�����,����������������򣬲����Ǹ������Ҳ�ȱʧ������� Ϊa[i] = i+1; ���ȱʧ��ֻ������ 1-n ֮�����
2������������a[i]==i+1; ����Ҫ���ľ��Ǵӵ�0��λ���Ͽ�ʼ���� �������Ƿ���� i+1, ֱ���ҵ���һ�������ڵ�λ��Ϊֹ�������Ľⷨ������һ��ʱ�临�Ӷ�Ϊ O��n^2��
3����������Ľ�����
				������һ�������A[0--i]��λ���϶����� a[i] = i+1, a[j--n] ��λ������δ֪�ģ���Ҫ��j��ʼ��������жϣ�
	�������г��ֵ�  ���� �� >n ��������û�õģ����Կ��Կ���ȥ���������ظ���Ԫ�أ�ֻ�豣��һ���Ϳ��� ��Ӱ�����Ľ�����ظ������ ������� i ��ǰ�� �� ���棬 ���������������������Կ����Ƴ�
*/
int firstMissingPositive(vector<int>& nums){ 
	int n = nums.size();
	for(int i=0;i<n;){
		if(nums[i]==i+1){
			i ++;
		}
		else if(nums[i]>n||  // >n 
				nums[i]<=i||  //�ظ����ֵ�Ԫ�� ����ǰ��  ���� ����
					nums[nums[i]-1]==nums[i] //�ظ����ֵ�Ԫ�� ���ں���
			){  //   �Ƴ���Ԫ��
			nums[i] = nums[n-1]; //�����һ��Ԫ�� ����ǰ�� ����iδ�ı䣬�ʵ�ǰ���Ǵ������״̬
			n--;//Ԫ�ظ��� --  �������Ƴ�Ԫ�صķ��� ����Ҫ �𲽵�λ�ñ仯�����ᵼ�� �����ԭ����˳�����ı�
		}else{  // ��Ҫ�ѵ�ǰ�������a[i] ������Ӧ���ڵ�λ����  �� i--��
			int xa=i;
			int xb=nums[i]-1;
			SWAP(nums[xa],nums[xb]);  //��һ�ε�ѭ�����ж� �Ƿ����� a[i]=i+1������
		}
	}
	return n+1;
}

/*
	�������� (ע�ⲻ�ǳ��ִ���������)
	�����ĸ��� > ���������������ĸ�����
	�ӵ�������ͬ��������������
		�ӵ�����������
		�ӵ�һ��������һ��������
*/
int zhongshu(vector<int> &nums){
	int count=0,x;
	for(int i=0;i<nums.size();i++){
		if(count==0){
			x=nums[i];
			count ++;
		}else if(nums[i]==x){  //ģ���ӵ�������ͬ����
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