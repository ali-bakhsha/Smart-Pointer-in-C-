//TOPIC: Unique pointer in C++

// Notes:
// 1. unique_ptr is a class template
// 2. unique_ptr is one of the smart pointer provided by c++11 to prevent memory leak
// 3. unique_ptr wraps a raw pointer in it and deallocates the raw pointer when unique_ptr object goes out of scope.
// 4. similar to actual pointer we can use -> and * on the object of unique_ptr, because it is overloaded in unique_ptr class
// 5. when exception comes then also it will deallocate the memory hence no memory leak.
// 6. not only object we can create array of objects of unique_ptr

// Operations:
// relase, reset, swap , get , get_deleter

// Program
#include <iostream>
#include <memory>
using namespace std;
class Foo{
		int x;
	public:
		explicit Foo(int x):x{x}{}
		~Foo(){cout << "Foo destructor" << endl;}
		int getX(){return x;}
};
int main()
{
	// 1 reqular pointer
	Foo* f = new Foo(10);
	cout << f->getX() << endl;
	
	
	unique_ptr<Foo> f6(f); // you can not point a single pointer to 2 diffrent unique pointer
	unique_ptr<Foo> f7(f); // 
	
	unique_ptr<Foo> f8(new Foo(30)); // it is ok
	unique_ptr<Foo> f9(new Foo(30)); // 
	delete f;
	cout << "*********************************" << endl;
	//2 use unique_ptr
	unique_ptr<Foo> p1(new Foo(10));
	
	unique_ptr<Foo> p2 = std::make_unique<Foo>(20);
	cout << p1->getX() << "    " << p2->getX() << "   " << (*p2).getX() << endl;
	
	//unique_ptr<Foo> p3 = p1; // error copy ownership  not allowed
	// p2 = p1;// error copy ownership  not allowed
	
	unique_ptr<Foo> p3 = std::move(p1); // move ownership is allowed
	cout <<  p3->getX() << "   " << (*p3).getX() << endl;

	Foo *f1 = p3.get(); // get return the managed object inside p3
	cout << f1->getX() << endl;
	
	
	//Foo *f2 = p1.release() or p1.get(); // run time exception 
	Foo *f2 = p3.release(); // release the ownership of managed pointer and return it
	cout << f2->getX() << endl;    
	
	cout << f1 << "   " << f2 << endl; // f2 , f1 are the same address
	delete f2;
	unique_ptr<Foo> p4 = std::move(p1);
	
	p2.reset(p4); // replace the managed object
	cout << p2->getX() << endl;
	
	cout << p4->getX() << endl;
	p4.swap(p1);// swap the managed pointer inside objects
	cout << p4->getX() << endl;
	
	
	
	
	
	return 0;
}
