#include "list_table.h"
#include "stack.h"
#include <hash_set>
#include <vector>

using namespace std;
using namespace stdext;

int main(){
	static_assert(1<2,"das");
	stack<int> s1;
	string s;
	//hash_set<int> hs;
	//hs.insert(1);
	//hs.insert(1);

	//cout <<hs.size() << endl;

	/*
	list_table<int> l;
	cout << l.size() << endl;*/



	/************************************************************************/
	/* list table test;                                                     */
	/************************************************************************/
	list_table<int> l;
	l.add(1);
	l.add(2);
	l.add(3);
	cout << l.nth_element(2)->data << endl;;
	//cout << "size--" << l.size() << endl;
	////l.add(11,1,1);
	////l.add(12,3,0);
	//l.print();
	////l._delete(2);
	//l.print();
	//cout << "resort" << endl;
	//l.resort();
	//l.print();
	//
	//l.resort();
	//cout << "sort" << endl;
	//l.sort_insert(8);
	//l.sort_insert(6);
	//l.print();
	////delete l.head;


	//stack<int> s;
	//s.push(1);
	//s.push(2);

	//cout << s.empty() << endl;;
	//cout << s.pop()<< endl;
	//cout << s.empty() << endl;
	//cout << s.pop()<< endl;
	//cout << s.empty() << endl;;
	return 0;
}