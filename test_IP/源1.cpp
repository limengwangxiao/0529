#include<iostream>
#include <string>
#include<vector>
#include<stdio.h>
using namespace std;
int main1(){

	int T,mod;
	cin >> T;
	string tmp;
	string re;
	vector<string> tt;
	for(int j=0;j<T;j++){

		 cin.get();  //接收来自cin >> int 的换行符   ASCII  为10
		
		getline(cin,tmp);
		cin >> mod ;
		int xx = tmp.size()/mod;
		int xxx=xx;
		int m = tmp.size() % mod;

		re.resize(tmp.size());

		int x = 0;
		int t = 0;
		int index = 0;
		for(int i=0;i<tmp.size();i++){
			if(t<=m){  //m
				xx=xxx;
			}else{
				xx=xxx-1;
			}
			if(t==mod){
				t = 0;
				x++;
			}
			if(t==0){
				index = t*xx+x;
			}else{

				index = index + xx + 1;
			}
			re[i] = tmp[index];
			t ++;
		}

		tt.push_back(re);
	}

	for(int i=0;i<tt.size();i++){
		cout << "Case #" << (i+1) <<":" <<endl;
		cout << tt[i] << endl;
	}
	return 0;
}