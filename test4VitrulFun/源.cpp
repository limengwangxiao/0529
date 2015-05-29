/*
	虚函数 vitrual 就是为了实现多态的，
	一般在 对象调用的时候，并不知道对象所属的类别，
	ptr->fun（）； 
	ptr 可以是由
		1、子类指定的子类对象
		2、基类指定的子类对象
		3、基类指定的 由子类对象自动类型转化
	因此为了实现多态，就必须需要一定的额外信息存放在 ptr 中
	存放在ptr 中的 是 vptr，vptr中存放的是slot (1---n) n即为当前类中存在的虚函数的个数
	假设在fun前面有3个虚函数，则 fun 对应的是 slot[4],则ptr->fun()可以转化为
	*(ptr—>vptr[4])(); 
	
	编译期：
		因vptr是一个对象的属性，因此在对象创建的时候，会将创建该类当中的虚函数的地址映射到
	vptr中，这是在编译期就完成的工作， 此外针对上面ptr的三种情况，则新的指针也会将对应的vptr 直接拷贝（猜测）

	执行期：
		在使用ptr->fun（）时，虽然不知道到底是基类还是子类的fun 函数，但是知道的是fun 的地址一定是在slot 4中，而在
		slot 4在存储的是函数的地址，因此在执行期唯一知道的东西就是 slot 4 到底是哪一个fun 的实例,或者是 基类的或者是子类的



		另外多态的实现是在指针或引用的基础上的
		直接声明的 基类的值 再对其赋值，是不会产生多态的现象的 原因就是 他们的vptr是不一样的
		A a; B _b;
		
		A _a = _b; 这种情况是不会产生多态的，因是A 直接声明的遍变量，他的vptr与a 一致

		A* bb = &_b;  这两种情况下可以产生多态
		A& bbb = _b;

		此外，因为这种比较特殊的调用的方式，会出现一些比较意外的情况， 
		1、父类指定的子类的对象 可以访问在 父类中未定义的虚函数  通过下面的强制类型转化 得到函数的地址
		2、可以访问non-public 的函数， 同样也是直接得到函数的地址
		3、缺省的虚函数的参数，  父类声明的子类的对象 在调用的虚函数中有缺省参数的时候， 因缺省参数静态绑定，函数确实动态绑定的，因此当没有参数传进的时候，缺省参数自动赋值，这是静态过程，但执行过程发生多态，参数的缺省不在执行自动赋值，因此会出现 父类参数，子类的执行的现象

*/






#include <iostream>

using namespace std;



class A{

public:
	int x;
	virtual void p(int x=1){
		cout <<x<<"A"<<endl;
	}
};

class B:public A{
public:
	int x;
	void p(int x=2){
		cout <<x<<"B"<<endl;
	}
private:
	virtual void  fun(){
		cout<<"fun"<<endl;
	}

};
#include <vector>
typedef void(*Fun)(void);
int main(){

	A a ;
	A* b = new B;
	B b_;
	a.p();
	b->p(); //缺省参数下的虚函数，父类参数 子类的执行过程

	int *p_a = (int*)&a; //a 的地
	int *a_f_arr = (int*)*(p_a); //a 的地址转化为 int[]
	// /***实际上就相当于 把a转化成 int[]的数组***/， 
	//但是并不支持将A 转化成int[] 所以通过取址和取值来完成，也包含了很多的强制类型转化.
	//另外对于void 指针的一点理解，虽然所有类型的指针都可以转化成void*，但通过void* 来取值是不可行的
	
	//1、为什么要转化成数组，因虚函数在vptr中的存储就是slot [1-n] 的数组表示
	//2、为什么是int形，因 int型可以表示是一种地址，在对Fun 赋值的时候，也就是将数组中某个位置上的值 赋给Fun 而Fun也是指针 当然也要经过一个强制类型转换
								
	//cout <<&A::p << endl;
	cout << &a << endl;
	cout << b << endl;
	cout << &a.x << endl;
	cout << &b->x << endl;
	
	//
/*
	int n;
	cin >> n;
	int t;
	vector<int> j;
	vector<int> o;
	for(int i=0;i<n;i++){
		cin >> t;
		if(t%2==0){
			o.push_back(t);
		}else{
			j.push_back(t);
		}
	}

	for(int i=0;i<n;i++){
		if(i<j.size()){
			cout << j[i] << " ";
		}else{
			cout << o[i-j.size()] << " ";
		}
	}
*/

	return 0;
}