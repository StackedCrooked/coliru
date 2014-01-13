#include <iostream>
#include <thread>
#include <map>
#include <vector>
#include <future>
#include <mutex>
#include <algorithm>
#include <utility>

using namespace std;

// queste non vanno qua, serve solo per far compilare

void foo(char*) {}//1
void foo(int) {}  //2

void run() {}

string readLines (const char* path) { return ""; }

// TEMPLATE METAPROGRAMMING SUPPORT //

// variadic templates

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... params);

// unpack via  ...
template<typename... Types>
struct Count;

template<typename T, typename... Rest>
struct Count<T, Rest...> {
  const static int value = Count<Rest...>::value+1;
};

template<> struct Count<> {   // end
  const static int value = 0;
};

// sizeof... is the same as our Count struct
template<typename... Args>
void PrintHowMany(Args... args)
{
   cout << sizeof...(args) << endl;
}

// decltype

int val, *ptr;
decltype(val) i1;   // i1 is int
decltype(ptr) p1; // p1 is int*

int& valRef = val;   	   
decltype(valRef) valRef2 = val; // xRef2 is int&
auto notRef = valRef;       // notRef is int

//    return types deduction
template<typename T1, typename T2>
auto mult(T1&& a, T2&& b) -> decltype(a*b);

// static_assert

template<short size>
class SmallAllocator {
   static_assert(size > 32, "max size is 32");
   //...
};

// perfect forwaring

// args’ types are preserved
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
   return unique_ptr<T>{new T{forward<Args>(args)...}};
}

// template aliases

// 
//template<typename T>
//using MyAllocVec = vector<T, MyAllocator>;
//MyAllocVec<int> v;

using Point = pair<int, int>; // same as typedef


int main()
{
	

// auto
auto x = 10;   
map<int, string> m;  
auto it = m.begin();

// range-based for loop
vector<int> v {1,2,3,4,5}; 
for(auto i : v)
   cout << i << endl;

// nullptr
// VA INSERITO NEL CHEATSHEET
//void foo(char*);//1
//void foo(int);  //2
foo(nullptr);   // calls 1

// trailing return type
// VA INSERITO NEL CHEATSHEET
// the following are the same
// void myFunction() {}
// auto myFunction() -> void {}

// uniform initialization
int x1 {};   	 // x1 = 0
int x2 {x1}; 	 // x2 = 0
int x3 {10}; 	 // x3 = 10;
//int  x4 {1.0}; 	 // error, narrowing

struct Point {
   Point(float x, float y) : m_x{x}, m_y{y} {}
private:
   float m_x, m_y;
};

Point p{1.0f, 2.0f};

// VA INSERITO NEL CHEATSHEET
// Point CreateOrigin() { return {0.0f, 0.0f}; }
// void SetOrigin(const Point& o) {...}
// SetOrigin({0.0f, 1.0f});

// initializer_list
vector<int> v2 {1,2,3,4,5};

class MyVector
{
public:
   MyVector(initializer_list<int> l)
     : m_inner{l.begin(), l.end()} {}
   //...
private:
	vector<int> m_inner;
};

// lambda expressions

vector<int> v3 {1,2,3,4,5}; 
auto firstEven = find_if(v3.cbegin(), v3.cend(), 
	[](int i) { return i%2 == 0; });

auto counter = 0;
auto adder = [&counter] { ++counter; };
adder(); // counter = 1;

counter = 0;
auto mutableAdder = [counter] () mutable { 
   ++counter; cout << counter << endl; };

auto anotherMutable = mutableAdder;
mutableAdder();   // prints 1
mutableAdder();   // prints 2
anotherMutable(); // prints 1

// CONCURRENCY //

// thread

// VA INSERITO NEL CHEATSHEET
//void run() { /*...*/ }
struct Runner {
   void operator()() { /*...*/ }
};

thread t1 {run};
Runner r{};
thread t2 {r};
thread t3 {[] { 
  cout << "from lambda" << endl; }};
t1.join(); t2.join(); t3.join();

// asynchronous calls

// VA INSERITO NEL CHEATSHEET
// string readLines(const char* path) { /*...*/ };

//auto path = R"(c:\temp\file.txt)";
auto path = "c:\\temp\\file.txt";
future<string> f = std::async([=]{return readLines(path);});
//... other work
auto lines = f.get(); // blocks now, get result or exception

// invocation occurs upon get() or wait()
auto deferredLaunch = async(std::launch::deferred, [=]{return readLines(path);});

// get() can be called more than once
shared_future<string> sharedF = f.share();

// mutexes

mutex mut;

{
 lock_guard<mutex> l{mut}; // lock
} // unlock

{
 unique_lock<mutex> l{mut}; // lock
 //...
 l.unlock();		 // unlock
} // nothing

}
