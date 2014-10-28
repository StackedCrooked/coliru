#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

using namespace std;

struct Foo : enable_shared_from_this<Foo> 
{
    Foo()
	{
		m_value = new int(0);
        m_init = false;
	}
	
	~Foo() 
    { 
		delete m_value;
		cout << "destroying Foo" << endl; 
	}
	
	int *m_value;
    bool m_init;

    void StartLooping()
    {
        if (!m_init)
        {        
            std::shared_ptr<Foo> thisFoo = shared_from_this();
    	    static thread myThread(loop, thisFoo);
            m_init = true;            
        }        
    }

private:
    static void loop(std::weak_ptr<Foo> weakFoo)
    {
    	while(1)
    	{
    		if (std::shared_ptr<Foo> strongFoo = weakFoo.lock())
    		{
			    cout << "looping: foo=" << ++*strongFoo->m_value << endl;
    		}
    		else
    		{
    			cout << "Foo is invalid!" << endl;
    			break;
    		}
    		
    		this_thread::sleep_for(chrono::milliseconds(100));
    	}
    }
};


int main() 
{
    try {
    	std::shared_ptr<Foo> foo(new Foo());
        foo->StartLooping();
        
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    catch(const std::exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
    cout << "exiting" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
	return 0;
}