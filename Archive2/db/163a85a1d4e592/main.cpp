#include <iostream> 
#include <boost/thread.hpp>

struct myClass { 
    int myFunction(int arg1, int arg2);
};

int myClass::myFunction (int arg1, int arg2)
{
    int counter = 0;
    try
    {
        //some code here
        do {   
            boost::this_thread::interruption_point(); 
            //some other code here
            ++counter;
        } while (counter != 20000); 
    } catch (boost::thread_interrupted&) {
        std::cout << "interrupted" << std::endl;
    }
    return counter;
}

void treadf() {
    myClass x;
    std::cout << "Returned: " << x.myFunction(1,2) << "\n";
}

int main()
{
    boost::thread t(treadf);
    t.interrupt();
    t.join();
}
