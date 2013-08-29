#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct x{
    
	bool udaloSie;
	
	
	
	struct yes{
			int nom;
			int hehe;
            
            ~yes(){ cout << "deleted yes" << endl; }
	};

	struct no{
		std::string error;
		int retcode;
        
        ~no(){ cout << "deleted no" << endl; }
	};
	
	union{ yes* y; no* n; } data;
    
    std::shared_ptr<void> garbage_collect;
};

void f(x const&);

int main()
{
    x yes;
    yes.udaloSie = true;
    auto y = std::make_shared<x::yes>();
    yes.garbage_collect = y;
    y->nom = 13;
    y->hehe = 37;
    yes.data.y = y.get();
    f(yes);
    
    
    x no;
    no.udaloSie = false;
    auto n = std::make_shared<x::no>();
    no.garbage_collect = n;
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
