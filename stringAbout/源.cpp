/*
�ַ�����ص����� �漰���ıȽ϶������ ����hash��partition�� �Ӻ���ǰ��ʽ�ı���������ͬʱ����
1��0-1 ����  0110010010001  ������0 �ŵ�1  ��ǰ�� --- partition ����
2���ַ���ɾ���͸���  abcabbbacccabb  �����е�a ȥ�����������е�b����һ�ݣ�����ԭ��b�ĺ���     ---�Ӻ��濪ʼ����
3������*   *2*45*45**74  �����е�* ���ŵ� ���ֵ�ǰ��   ---   �����ԴӺ����, Ҳ����partition ����
4����λ��  �ж� b �Ƿ��� a  �ı�λ��
5���ַ����ķ�ת  abcdef  ��n���ַ� �Ƶ�ԭ���ĺ���
6���ַ����İ���     �ж�A�Ƿ����B �е����е��ַ�  �ȶ�����������������˳��Ĳ�ѯ
7���ַ����ķ�ת ���룺 ��I am a student.�����������student. a am I��  ��ȫ��ת��Ϊ ��������ͬ���ĺ��� ��ÿһ����������
�ַ��������� һ������õ��Ƚ�����ķ���ȥ�����
	����
	�Ӻ�ʼ����
	������ͬʱ��ʼ����

*/

#include <iostream>
#include <string>
using namespace std;
#define SWAP(a,b){int c=a;a=b;b=c;}
void fun_7(char* i,char* j){
	while(i<j){
		SWAP(*i,*j);
		++i,--j;
	}
}
void fun_4(string a,string b){
	int num[26];
	memset(num,0,26);
	int nZero = 0;
	for(int i=0;i<b.size();i++){
		num[b[i]-'a']++;
		if(num[b[i]-'a']==1){
			nZero ++;
		}
	}
	for(int i=0;i<b.size();i++){ //��һ����������
		num[a[i]-'a'] --;
		if(num[a[i]-'a']==0){ //
			nZero --;
		}
 	}
	
	for(int i=b.size();i<a.size();i++){ //��һ����������  i �ƶ�һλ����һ����������
		//ȥ����һ�����ڵĵ�һ���ַ�
		num[a[i-b.size()]-'a']++;
		if(num[a[i-b.size()]-'a']==1){
			nZero ++;
		}
		//���ӵ�i���ַ� + ǰһ�����ڵĺ������ַ� ��� ��һ�� ��������
		num[a[i]-'a']--;
		if(num[a[i]-'a']==0){
			nZero --;
		}
		if(nZero==0){
			cout << "��λ��" << endl;
		}
	}
	cout << nZero << endl;
}
void fun_3(int *a,int l, int h){
	int j=l;
	for(int i=l;i<h;i++){
		if(a[i]=='*'){
			SWAP(a[i],a[j++]); //j �� i ���� �� j����������֣�
								//���������˼����� �� ǰ�������j ��������*��λ��i��
								//�����������  1��a[j] �����֣��������еĽ����ķ�ʽ
											 //2��a[i] �� * ���� �������ֻ������� i jָ��ͬһ��λ�õ����
												//�� i j ��ָ��Ķ������ֵ������  ��j�ᱣ����ǰ��������� i��ǰ�ƶ� ֱ��
										//iָ�����һ�� * ������ʱ i j ֮��ı�Ȼȫ�� ���� �Ҳ����ܳ��� j��ʱָ�����*
							
		}
	}
}
void fun_1(int *a,int l, int r){
	while(l<r){
		while(l<r&&a[l]==0){
			l++;
		}
		while(l<r&&a[r]==1){
			r--;
		}
		SWAP(a[l],a[r]);
	}
}
void fun_2(string& ch){
	int n = 0;
	int num_b = 0;
	for(int i=0;ch[i]!='\0';i++){
		if(ch[i]!='a'){ //ɾ��a  n���ٶȱ�i�� ��ʼ��Ϊa��ʱ�� ֱ�Ӹ��ƣ�����a�� n���ٶȱ�i���������м���a �ͻ������ λ��
			ch[n++] = ch[i];
		}
		if(ch[i]=='b'){
			num_b ++;
		}
	}
	//�Ӻ���ǰ ���� b
	int newlen = n + num_b;
	ch.resize(newlen);
	
	for(int i=newlen-1,j=n-1;j>=0;j--){
		ch[i--] = ch[j];
		if(ch[j]=='b'){
			ch[i--]='b';
		}
	}
}
int main(){
	int  a[10] ={0,1,1,0,1,1,0,0,1,0};
	string s = "I am a student.";
	string s2 = "cbb";
	//fun_4(s,s2);
//	cout << s << endl;
	fun_7(&s[0],&s[0]+s.size()-1);
	cout << s << endl;
	int cur=0,t=0;
	for(int i=0;i<s.size();){  
		if(s[i]!=' '){
			i++;
		}else{
			fun_7(&s[0]+cur,&s[0]+i-1);
			cur = i++ + 1;
		}
	}

	for(int i=0;i<10;i++){
		cout << a[i] <<endl;
	}
}