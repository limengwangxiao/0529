#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <set>
using namespace std;

vector<int> logicAnd(int j,//mask
					 int k,//ip
					 string ip,string mask,vector<int>& ip_,vector<int>& mask_){

	vector<int> x;
	vector<int> re;
	string tmp_ip;
	string tmp_mask;
	int ip_size = ip_.size();
	int mask_size = mask_.size();
	if(k*4+3>=ip_size){
		int index =0;
		int index_x=0;
		while(index<4){
			int t_ip = atoi(&ip[index_x]);
			ip_.push_back(t_ip);
			char a[10];
			string str;
			itoa(t_ip, a, 10);
			str = a;
			index_x += str.length()+1;
			index ++;
		}
		
	}
	if(j*4+3>=mask_size){
		int index =0;
		int index_x=0;
		while(index<4){
			int t_ip = atoi(&mask[index_x]);
			mask_.push_back(t_ip);
			char a[10];
			string str;
			itoa(t_ip, a, 10);
			str = a;
			index_x += str.length()+1;
			index ++;
		}
	}
	
	for(int i=k*4,t=j*4;i<k*4+4&&t<j*4+4;i++,t++){

		//for(int t=j*4;t<j*4+4;t++){
			int xx = ip_[i]&mask_[t];
			x.push_back(xx);
		//}
	}
	return x;
}

int main(){

	string str;
	str.resize(1000000);
	int x = 10^7;
	cout << x << endl;

	cout << str.size () << endl;
	//set< vector<int> > test;
	//vector< vector<int> > re;

	//int T,m,n;
	//string tmp_IP;
	//string tmp_MASK;
	//vector<string> IP;
	//vector<string> MASK;
	//cin >> T;

	//for(int i=0;i<T;i++){
	//	IP.clear();
	//	MASK.clear();
	//	vector<int> ip__;
	//	vector<int> mask__;
	//	vector<int> tmp;
	//	cin >>m>>n;

	//	for(int j=0;j<m;j++){ //地址
	//		cin >> tmp_IP;
	//		IP.push_back(tmp_IP);
	//	}
	//	for(int j=0;j<n;j++){ //掩码
	//		cin >> tmp_MASK;
	//		MASK.push_back(tmp_MASK);
	//	}

	//	//IP MASK 输入完成
	//	//将所有的IP MASK 转化为 数组

	//	for(int j=0;j<MASK.size();j++){
	//		for(int k=0;k<IP.size();k++){
	//			test.insert(logicAnd(j,k,IP[k],MASK[j],ip__,mask__));
	//		}
	//		tmp.push_back(test.size());
	//		test.clear();
	//	}
	//	re.push_back(tmp);
	//	tmp.clear();
	//}

	//for(int i=0;i<re.size();i++){
	//	cout << "Case #" << (i+1) << ":" << endl;
	//	for(int j=0;j<re[i].size();j++){
	//		cout << re[i][j] << endl;
	//	}
	//}
	return 0;
}

