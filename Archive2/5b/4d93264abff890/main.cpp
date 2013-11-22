#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;

struct MyVariant 
{
    MyVariant(bool b) : 
		m_bool(b), 
		m_isBool(true), 
		m_isString(false)
	{
	}
	
	MyVariant(const string &s) : 
		m_bool(false), 
		m_string(s), 
		m_isBool(false),
		m_isString(true)
	{
	}
	
	bool ToBool() {
		if (!m_isBool)
			throw std::exception();
			
		return m_bool;
	}
	
	string ToString() {
		if (!m_isString)
			throw std::exception();
			
		return m_string;
	}
	
	bool m_bool;
	string m_string;
	
	bool m_isBool;
	bool m_isString;
};

struct MyVariantTestWrapper : public MyVariant 
{
	MyVariantTestWrapper(bool b) : MyVariant(b) { }
	MyVariantTestWrapper(const string &s) : MyVariant(s) { }
	
	void ToBool() {
		MyVariant::ToBool();
	}
	
	void ToString() {
		MyVariant::ToString();
	}
};

typedef boost::function<void (MyVariantTestWrapper*)> MyTestFunc;

int main() {
	map<string, MyTestFunc> testCases;
	testCases[typeid(bool).name()] = boost::bind(&MyVariantTestWrapper::ToBool);
	testCases[typeid(string).name()] = boost::bind(&MyVariantTestWrapper::ToString);
    
    MyVariantTestWrapper variant(true);
    testCases.erase(typeid(bool).name());
    for(map<string, MyTestFunc>::const_iterator testCase=testCases.begin(); testCase != testCases.end(); ++testCase) 
    {
        testCase->second(&variant);
    }

	return 0;
}