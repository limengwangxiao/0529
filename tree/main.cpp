#include <iostream>
#include <vector>
#include "tree.h"
using namespace std;

void * operator new(size_t size) 
        { 
        void *p;
		while ((p = malloc(size)) == 0){};
        return (p);
        }

int main(){

	cout << sizeof(Tree_);
	Tree_ *tt = new Tree_;
	Tree_ t;
	t.insert(t.r,62);
	t.insert(t.r,58);
	t.insert(t.r,47);
	t.insert(t.r,35);
	t.insert(t.r,51);
	t.insert(t.r,29);
	t.insert(t.r,37);
	t.insert(t.r,36);
	t.insert(t.r,49);
	t.insert(t.r,56);
	t.insert(t.r,48);
	t.insert(t.r,50);
	t.insert(t.r,88);
	t.insert(t.r,73);
	t.insert(t.r,99);
	t.insert(t.r,93);


	cout <<t.height(t.r);

	//t.delete_(t.r,47,n);


	//t.zx(t.r);
	//t.delete_ (t.r);

}