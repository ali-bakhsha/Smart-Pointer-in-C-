//TOPIC: Shared pointer in C++

// Notes:
// 1. Shared pointer is a smart pointer which can share the ownership of object(managed object)
// 2. Several shared_ptr can point to the same object (managed object)
// 3. It keeps a refrence count to maintain how many shared_ptr are pointiong to the same object and once last shared_ptr goes out of scope, then managed object gets deleted.
// 4. Shared_ptr is Thread safe and not thread safe(what is this). It has 2 parts - Managed Object and Control block(ref count).
//		a. Control block is thread safe
//		b. Managed object is not thread safe
// 5. There are 3 ways shared_ptr will destroyed managed object
//		a. If the last shared object goes out of scope.
//		b. if you initial shared_ptr with some other shared_ptr
//		c. If you reset your shared_ptr
// 6. Refrence count doesnt work when you use refrence or pointer of shared_ptr.

// Program
#include <iostream>
#include <thread>
#include <memory>
using namespace std;
class Foo{
		int x;
	public:
		explicit Foo(int x):x{x}{}
		~Foo(){cout << "Foo destructor" << endl;}
		int getX(){return x;}
};

void fun(shared_ptr<Foo> sp){
	cout << "Ref Count is: " << sp.use_count() << endl; 
}
int main()
{
	// 1 reqular pointer
	Foo* f = new Foo(10);
	//cout << f->getX() << endl;
	
	shared_ptr<Foo> s(new Foo(10));
	cout << s->getX() << endl;
	cout << s.use_count() << endl;
	cout << "****************" << endl;
	// increate ref count 
	shared_ptr<Foo> s1 = s;
	cout << s.use_count() << endl;
	cout << s1.use_count() << endl;
	cout << "****************" << endl;
	
	// use ref and ref count wont work
	shared_ptr<Foo> &s2 = s;   // you can use shared_ptr<Foo> s2 = s;
	cout << s.use_count() << endl;
	cout << s2.use_count() << endl;
	cout << "****************" << endl;
	
	// use ref and ref count wont work
	shared_ptr<Foo> *s3 = &s;   // you can use shared_ptr<Foo> s2 = s;
	cout << s.use_count() << endl;
	cout << s3->use_count() << endl;
	cout << "****************" << endl;
	
	// use in thread . when copy by value ref count will be added
	thread t1(fun , s);
	thread t2(fun , s);
	thread t3(fun , s);
	thread t4(fun , s);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	
	return 0;
}
