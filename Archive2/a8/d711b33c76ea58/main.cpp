#include <iostream>
#include<thread>
using namespace std;

void function_1()
{
    cout<<"la superficial "<<endl;
}

int main()
{
    thread t1(function_1); // t1 starts running

    t1.detach(); // t1 will freely on its own  --daemon process
      if(t1.joinable())
    t1.join(); //main thread waits for t1 to finish



//en function objets
//std::thread my_thread((background_task()));  //parentesis extra previenen la interpretacion como una declaracion de funcion que retorna un objeto thread
//std::thread my_thread{background_task()};  //
    return 0;
}
