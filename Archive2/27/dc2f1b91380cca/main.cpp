#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdint.h>
#include <boost/ptr_container/ptr_vector.hpp>
// #include <boost/chrono.hpp>
#include <chrono>

using namespace std;
//#ifdef WIN32
//namespace chron = boost::chrono;
//#else
namespace chron = std::chrono;

typedef uint32_t MyType;
//struct MyType {
//    std::string m_str;
//	MyType() = default;
//	MyType(uint32_t x)
//	: m_str(x % 3, 'a')
//	{ }
//};
//std::ostream& operator<<(std::ostream& os, const MyType& obj) {
//	return os << obj.m_str;
//}

typedef unique_ptr<MyType> MyUqPtr;
typedef vector<MyUqPtr> MyUqPtrVector;
typedef boost::ptr_vector<MyType> MyBoostPtrVec;

extern MyType* pGlobalDummy;
MyType* pGlobalDummy = nullptr;

const size_t n = size_t(1e6);
const size_t loop_count = 200;
const size_t repeat_count = 3;


template<typename C>
void FillPtrContainer(C& c) {
	c.clear();
	c.reserve(n);
	for (size_t i = 0; i != n; ++i) {
		c.push_back(typename C::value_type(new MyType(i)));
	}
}

MyType* PtrShim(MyType& t) {
	return &t;
}

MyType* PtrShim(MyUqPtr& p) {
	return p.get();
}


template<typename C>
void RunContainerAccess(C& c) {
	for (size_t i = 0; i != loop_count; ++i) {
		for (auto& e : c) {
			// This is relevant: 
			// If the if-condition is present, VC++2013 will show 
			// approx. the same runtime for both cases. However,
			// if the only line in this loop is assigning the element
			// to the pGlobalDummy, *then* ptr_vector will run approx. 50%
			// faster than the unique_vector version!
			//
			// g++-4.8 does not show this behaviour
			//
			// Note: VS2013 commmand line: (release; /O2; no whole prg opt)
			//   /GS /analyze- /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /sdl /Fd"Release\vc120.pdb" /fp:precise /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_LIB" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /Gd /Oy- /Oi /MD /Fa"Release\" /EHsc /nologo /Fo"Release\" /Fp"Release\simple.pch" 
			//
			// Note: http://coliru.stacked-crooked.com/ command line:
			//   g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
			
			// if (pGlobalDummy)
				pGlobalDummy = PtrShim(e);
		}
	}
}

MyType aValue = 42;
MyUqPtrVector v1;
MyBoostPtrVec v2;

void run_test() {
	chron::nanoseconds time[2];

	for (size_t i = 0; i != repeat_count; ++i) {
		const auto t1 = chron::high_resolution_clock::now();
		RunContainerAccess(v1);
		const auto t2 = chron::high_resolution_clock::now();
		RunContainerAccess(v2);
		const auto t3 = chron::high_resolution_clock::now();
		time[0] += t2 - t1;
		time[1] += t3 - t2;
	}

	typedef chron::milliseconds output_time;
	const char* const out_unit = " ms";

	cout << "The timings are as follows for accessing all (" << n << ") elements " << loop_count << " times:\n";
	cout << "* " << typeid(v1).name() << ": " << chron::duration_cast<output_time>(time[0]).count() << out_unit << "\n";
	cout << "* " << typeid(v2).name() << ": " << chron::duration_cast<output_time>(time[1]).count() << out_unit << "\n";
}

int main() {
	cout.imbue(locale(""));
	cout << "Start...\n";
	pGlobalDummy = &aValue;

	// Set up containers:
	FillPtrContainer(v1);
	FillPtrContainer(v2);

	run_test();

	// Just test output to not make the optimizer mess up measurement:
	pGlobalDummy = &*v1[n/2];
	if (pGlobalDummy) {
		pGlobalDummy = &v2[n / 2];
	}
	cout << "Dummy output: " << *pGlobalDummy << endl;
}
