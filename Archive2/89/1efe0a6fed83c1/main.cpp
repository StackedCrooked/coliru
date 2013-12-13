#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>

using namespace std;

class Base
{
private:
    virtual string  	doGetname(  ) const { return "Base"; };
    
protected:
    virtual void  	   	doGetValue( map<string,string> &ds, const bool include ) const;
	inline void  	   	doGetValue( map<string,string> &ds ) const { doGetValue(ds, true); };
    
public:
    string 			    GetValue(  ) const;
    string    		    GetName(  ) const { return doGetname(); };
};

class Derived : public Base
{
private:
    virtual void  		doGetValue( map<string,string> &ds ) const;
    virtual string 	    doGetname(  ) const { return "Derived"; };
};

struct generate_value_from_map : std::unary_function<void, void>
{
    generate_value_from_map( string *_val, const string assignment = "  " ):val(_val)
	{
		count = 0;
		insert = (*_val);
        first = "(";
		second = ") "+assignment+" (";
	}
	void operator() (pair<const string,string> &i)
	{
		first += ( count > 0 ? "," : "" ) + i.first;
		second += ( count > 0 ? "," : "" ) + i.second;

		(*val) = insert + first + second + ")";

		++count;
	}

private:
	int count;
	string *val;
	string insert;
	string first;
	string second;
};

string  Base::GetValue(  ) const
{
    string ret_val = "name is: " + GetName() + " \n";
	map<string,string> ret_map;
	this->doGetValue(ret_map);
	for_each(ret_map.begin(), ret_map.end(), generate_value_from_map(&ret_val));
	return ret_val;
}

void  Base::doGetValue( map<string,string> &ds, const bool include ) const
{
    //base implementation
    //fills ds with values from Base
    ds["type"] = "Base";
    ds["id"] = "Id";
}

void  Derived::doGetValue( map<string,string> &ds ) const
{
    Base::doGetValue( ds );
    //derived implementation
    //fills ds with values from Derived
    ds["type"] = "Derived";
    ds["name"] = "Name";
}

int main()
{
    shared_ptr<Derived> obj ( new Derived() );
    
    string val = obj->GetValue();
    
    cout << val;
    
    //do stuff with val
}
