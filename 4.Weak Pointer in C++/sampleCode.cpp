//TOPIC: Weak pointer in C++

// Notes:
// 1. If we say unique_ptr is for unique ownership and shared_ptr is for shared ownership then weak_ptr is for no ownership smart pointer.
// 2. It actually refrence to an object which is managed by shared_ptr
// 3. A weak_ptr is created as a copy of shared_ptr.
// 4. We have to convert weak_ptr to shared_ptr in order to use the managed object.
// 5. It is used to remove cyclic dependency beyween shared_ptr.


// Program
#include <iostream>
#include <memory>
using namespace std;
/*
int main1()
{
	auto sharedPtr = std::make_shared<int>(10);
	std::weak_ptr<int> weakPtr(sharedPtr);
	
	
	
	cout << "weakPtr.useCont " << weakPtr.use_count() << endl;
	cout << "SharedPtr.useCont " << sharedPtr.use_count() << endl;
	cout << "weakPtr.expired " << weakPtr.expired() << endl; // 0 means not expired

	cout << endl << endl;
std::shared_ptr<int> sharedPtr1;
	if( sharedPtr1= weakPtr.lock()){ // convert weak to shared
		cout << "SharedPtr " << *sharedPtr1 << endl;
		cout << "SharedPtr1.useCont " << sharedPtr.use_count() << endl;
	}
	else{
		cout << "Dont get the resource!" << endl;
	}

	
	cout << endl << endl;
	weakPtr.reset();
		cout << "weakPtr.expired " << weakPtr.expired() << endl;
		cout << "aftrer reset SharedPtr1.useCont " << sharedPtr1.use_count() << endl;
		cout << "aftrer reset SharedPtr.useCont " << sharedPtr.use_count() << endl;

	if(std::shared_ptr<int> sharedPtr1 = weakPtr.lock()){
		cout << "SharedPtr " << *sharedPtr << endl;
		cout << "SharedPtr1.useCont " << sharedPtr1.use_count() << endl;
	}
	else{
		cout << "Dont get the resource!" << endl;
	}
	return 0;
}
*/


struct Son;
struct Daughter;
struct Mother{
	~Mother(){
		cout << "Mother gone.." << endl;
	}
	void setSon(std::shared_ptr<Son> s){
		mySon = s;
	}
	void setDaughter(std::shared_ptr<Daughter> d){
		myDaughter = d;
	}
	// uncommenct to check cyclic problem
	//std::shared_ptr<Son> mySon;
	//std::shared_ptr<Daughter> myDaughter;
	
	// to solve cyclic problem
	std::weak_ptr<Son> mySon;
	std::weak_ptr<Daughter> myDaughter;

};


struct Son{
	Son(std::shared_ptr<Mother> m):myMother(m){}
	~Son(){
		cout << "Son gone.." << endl;
	}
	std::shared_ptr<Mother> myMother;
};

struct Daughter{
	Daughter(std::shared_ptr<Mother> m):myMother(m){}
	~Daughter(){
		cout << "Daughter gone.." << endl;
	}
	std::shared_ptr<Mother> myMother;
};
int main()
{
	std::shared_ptr<Mother> mother = std::shared_ptr<Mother>(new Mother);
	std::shared_ptr<Son> son = std::shared_ptr<Son>(new Son(mother));
	std::shared_ptr<Daughter> daughter = std::shared_ptr<Daughter>(new Daughter(mother) );
	
	mother->setSon(son);
	mother->setDaughter(daughter);
	
}
