
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define SWAP(a,b){int tmp=a;a=b;b=tmp;}
#define K 0


/************************************************************************/
/*  ��Ŀ������������С��k��Ԫ��
		��Ŀ������n�����������������С��k����
		��������1��2��3��4��5��6��7��8��8�����֣�����С��4������Ϊ1��2��3��4��
		
		1����ԭ���н����������ǰk���� ���������ʱ�临�Ӷ� Ϊ O��n^2�� �� O��nlogN�� 
		2��������������н�������ֻ����ԭ�������������ѡ�� k����С�ļ��ɣ�ÿ���������в�����С�� ����� n�� �������k�β���
					��O��n*k��
		3��ά��һ��k��Ԫ�ص���С��,��ʼ������K��Ԫ�ؽ��ѣ�����Ϊ��������С��k�����������αȽ�ʣ�µ�Ԫ�أ�
					���¶ѻ��߲����£������е�Ԫ�ؾ��ǽ����������
		4�����ƿ��������еĻ��ֹ��̣�����2��3 ��������ʵ������������K��Ԫ�ض�������ģ�����ĳ�̶ֳ���Ҳ��һ���˷ѣ�
				��ˣ����ԶԱȿ��ŵĻ��ֹ��̣� �����ص�mid ֵ ����==K ��ǰK ������������Ҫ�Ľ������������������ݹ�������С�
				�˹��̵�Ч���ܵ� ��������ŦԪ��

		ͬ����С��K ����ת��Ϊ����K���� ͬ��
		����Ѱ�ҵ�K�����, ��ʵ��������������TOP K ת�������ģ����ҵ�TOP K ֮������ԭ���������Ե�Ѱ��K�������� 

		5����STL Ҳ�� top K ���������һ���ⷨ��ͬ�������û��ֵĹ��̣� �Ƚ���Ҫ�Ĳ���Ҳ���ڻ��ֹ�������Ŧ���ѡȡ
			��SGI STL �� ѡȡ���� ��ǰ ��K ���� ��β  ����������С�ĵ���Ϊ��Ŧ��  _algo.c 83 ��
		6����Ȼȷ����Ŧ���ѡȡ��Ӱ��ʱ�临�ӶȵĹؼ����أ����������һ��ѡ����Ŧ��ķ���  BFPRT 
		BFPRT  ���Գ�Ϊ ����ֻ���������������λ������λ���� ���� median-of-medians �� median ��λ����
			BFPRT ������������������������Ѱ�ҵ�K С���� ���Էֳ�������Ĳ���
			1�� һ�������Ѱ����ŦԪ�صķ���
			2�� �����ҵ�����ŦԪ�ض����н��л���

				

				getMedian();

		1����arr�е�n��Ԫ�ػ��ֳ�n/5�飬ÿ��5��Ԫ�أ���������鲻��5��Ԫ�أ���ô���ʣ�µ�Ԫ��Ϊһ��(n%5��Ԫ��)
		2����ÿ������в�������(ֻ��ÿ�������5��Ԫ��֮�����������������֮�䲢������)��������ҵ�ÿ�������λ����������Ԫ�ظ���			Ϊż����ͳһ�ҵ�����λ����
		3������2��һ�����ҵ�n/5����λ��������Щ��λ�����һ���µ����飬��ΪmedianArr���ݹ����getMedian
(medianArr,medianArr.length/2)���������ҵ�medianArr��������е���λ��(median�еĵ�(medianArr.length/2)С����)��


4��getMedian�еõ�����Ŧ ����
			
																	*/
/************************************************************************/


int getTopK(int *l,int *r,int x){ //�ҵ�ÿһ������Ϊ5 �������е�3С���� ��Ϊ��ǰ���е���λ��

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
		//�Ҵ�ǰ�����е����ֵ ��������ǰ��
		SWAP(*(l+maxIndex),*(l+count));
		count ++;
		i=l+count;
	}

	return maxIndex;
}

int medianOfmedian(int *a, int l,int r,int k){

	vector<int> tmp;
	int i;
	for(i=l;i<=r-5;i+=5){ //����ʣ��һ��С��5��������
		getTopK(a+i,a+i+5,3);
		int x = a[i+2];
		tmp.push_back(x);
	}


	if(r-i==4){  //���ʣ�µ�Ԫ�صĸ�����Ϊ5��
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
	//��һ��ѡȡ��ŦԪ�صķ����� ��ԭ���������ѡȡһ��Ԫ����Ϊ��Ŧ
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

	int x = a[l];//��ŦԪ��  ���������һ�µ��� �����㷨Ч�ʵ����ؾ�����Ŧ��ѡȡ
				// �˴�ֱ��ѡȡ ��һ��Ԫ����Ϊ��Ŧ  Ȼ���ж���ѡȡ��Ŧ�ķ���
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

#ifdef _DEBUG  //Ŀǰ�������� ������#if ����#ifdef _DEBUG��Ч������һ���ģ������۵������ֻҪ��������Debug���������ɵ�
				//���ڱ���׶λὫ��δ����������������ִ�еĴ��� Ԥ����׶��Ѿ�ȥ���� 
				//����Release ���������ɵ��򲻻������δ���
	cout << "DEBUG" << endl;
#endif // _DEBUG

	int mid = l;
	if(mid==k){  //���� a[mid] + ǰ mid-1��k-1�� ����
		print(k,a);
		return mid;
	}else if(mid==k+1){ //���� mid ǰ k ����
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