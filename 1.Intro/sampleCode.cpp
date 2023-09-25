//TOPIC: Introduction to smart pointers ( how to work)

// Notes:
// 1- smart pointer is a class which wrapes a raw pointer to manage the life time of the pointer
// 2- the most fundamental job of smart pointer is "to remove the chance of memory leak"
// 3- it makes sure that the object is deleted if it is not refrence any more.

//types
// 1. unique_ptr
//				allows only one owner of the underlying pointer.
// 2. shared_ptr 
//				allows multiple owner of the same pointer ( refrence count is maintained)
// 3. weak_ptr
//				it is special type of shared_ptr which does not count the refrence.
// 4. we have auto_ptr in C++17

#include <iostream>
using namespace std;
class MyInt{
	public:
		MyInt( int* p = nullptr){data = p;}
		~MyInt(){delete data;}
		int& operator* (){return *data;}
		
	private:
		int* data;
};
int main()
{
	int *p = new int(10); // we have to delete p pointer , but we can use MyInt Class as a wrapper
	MyInt myint = MyInt(p);
	//MyInt myint(p);
	cout << *myint << endl;
		
	return 0;
}
