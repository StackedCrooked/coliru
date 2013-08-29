#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct x{
    
	bool udaloSie;
	
	
	
	struct yes{
			int nom;
			int hehe;
	};

	struct no{
		std::string error;
		int retcode;
	};
	
	union{ yes* y; no* n; } data;
};

void f(x const&);

int main()
{
    x yes;
    yes.udaloSie = true;
    std::unique_ptr<x::yes> y(new x::yes);
    y->nom = 13;
    y->hehe = 37;
    yes.data.y = y.get();
    f(yes);
    
    
    x no;
    no.udaloSie = false;
    std::unique_ptr<x::no> n(new x::no);
    n->retcode = 666;
    n->error = "elles jest lolem";
    no.data.n = n.get();
    f(no);
}


void f(x const& val)
{
	if(val.udaloSie){
		cout << "YEAAAAAAAH!" << endl;
		cout << val.data.y->nom << ", " << val.data.y->hehe << endl;
	}else{
		cout << ":((((((((((" << endl;
		cout << "(" << val.data.n->retcode << ") - " << val.data.n->error << endl;
	}
}
