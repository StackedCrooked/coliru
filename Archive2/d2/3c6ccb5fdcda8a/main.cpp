#include <exception>
#include <iostream>

#include <vector>
#include <list>
#include <set>
#include <queue>
#include <algorithm>
#include <iterator>
#include <functional>


#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/function.hpp>
#include <boost/chrono.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/variant.hpp>
#include <boost/concept_check.hpp>

using namespace std;
using namespace boost;


//--------ZAD1--------------------------------------------------------------------------
//szablon do znajdowania mediany dla trzech liczb. Powinien działać dla typów, które da się porównywać operatorem mniejszości

template<typename T>
T mediana(T a, T b, T c) {
    BOOST_CONCEPT_ASSERT(( LessThanComparableConcept<T>));
	if(a < b) {
		if(b < c)
			return b;
		if (a < c)
			return c;
		return a;
	} else {
		if(a < c)
			return a;
		if(b < c)
			return c;
		return b;
	}
}

void zad1() {
	cout << mediana(1,2,3) << endl;
	cout << mediana(1,3,2) << endl;
	cout << mediana(2,1,3) << endl;
	cout << mediana(2,3,1) << endl;
	cout << mediana(3,1,2) << endl;
	cout << mediana(3,2,1) << endl;
}

// //--------ZAD2--------------------------------------------------------------------------
// // Logger współbieżny

class Logger {
public:
	static Logger& getInstance() {
		static Logger logger;
		return logger;
	}

	void msg(const std::string& s) {
		//mutex::scoped_lock l(m_);
		cout << ++counter_ << ':' << s;
		cout << endl;

	}
private:
	Logger() : counter_(0) {}
	//mutex m_;
	int counter_;
};

void thread_fun() {
	for(int i=0;i<1000;++i) {
		Logger::getInstance().msg("thread log");
	}
}

void zad2() {
    boost::thread thrd1( thread_fun );
    boost::thread thrd2( thread_fun );
    thrd1.join();
    thrd2.join();
}


// //--------ZAD3--------------------------------------------------------------------------
// //wydruk (kod)
const string NAZWISKO("Nowak");

class Vis : public boost::static_visitor<void> {
public:
	Vis() : str_("") {}
	void operator()(const int& i){
		if(i < str_.length()) {
			str_ += str_[i];
		}
		cout << str_ << endl;
	}
	void operator()(const string& s) {
		str_ += s;
		cout << str_ << endl;
	}
	string str_;
};


void zad3() {
	typedef boost::variant<string,int> V;
	list<V> l;
	l.push_back(1);
	l.push_back(NAZWISKO.size());
	l.push_back(NAZWISKO);
	l.push_back(NAZWISKO.size());
	l.push_back(1);

	Vis vis;
	for(list<V>::const_iterator i = l.begin(); i != l.end(); ++i) {
		apply_visitor(vis, *i);
	}
	cout << vis.str_ << flush;
}

//--------ZAD4--------------------------------------------------------------------------
// podaj wydruk

class Foo {
public:
	Foo(int idx = 0) : idx_(idx) {}
	char get() const { return NAZWISKO[idx_]; }
	Foo next() const { return Foo(idx_ + 1); }
private:
	int idx_;
};

void zad4() {
	list<Foo> l;
	l.push_back(Foo());
	l.push_back(Foo());
	l.push_back(Foo());
	l.push_back(Foo());
	transform(l.begin(), l.end(), l.begin(), boost::bind(&Foo::next, _1) );
	vector<char> v;
	transform(l.begin(), l.end(), back_inserter(v), boost::bind(&Foo::get, _1) );
	copy(v.begin(), v.end(), ostream_iterator<char>(cout, "") );
}


//--------ZAD5--------------------------------------------------------------------------
//  użyć algorytm find_if
// Jeżeli f jest obiektem typu std::modulus<T> oraz x i y są obiektami typu T, to f(x,y) zwraca x%y.

//znajdź pierwszą liczbę niepodzielną przez liczbę liter w stałej NAZWISKO. Jeżeli nie znaleziono, zwróć 0.
int find_not_multiples(const vector<int>& v) {
	vector<int>::const_iterator i = find_if( v.begin(), v.end(), boost::bind( modulus<int>(), _1, NAZWISKO.length() ) );
	if(i != v.end())
		return *i;
	return 0;
}

void zad5() {
	const int TAB [] = {5, 10, 0, 15, 16, 15 };
	const int TAB_SIZE = sizeof(TAB)/sizeof(TAB[0]);
	vector<int> v(TAB, TAB + TAB_SIZE);
	cout << "Found:" << find_not_multiples(v) << endl;
}

//--------ZAD6--------------------------------------------------------------------------
//Co daje używanie repozytorium?

int main() {
    cout << "zad1: "; zad1(); cout << endl;
    cout << "zad2: "; zad2(); cout << endl;
    cout << "zad3: "; zad3(); cout << endl;
    cout << "zad4: "; zad4(); cout << endl;
    cout << "zad5: "; zad5(); cout << endl;
    return 0;
}
