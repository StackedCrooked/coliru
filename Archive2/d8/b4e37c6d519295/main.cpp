#include <iostream>
#include <thread>
auto id = std::this_thread::get_id();
thread_local auto id3 = std::this_thread::get_id();  // (3.7.2/p1-2) what guarantees this is initialised in the thread that runs main ? 
                                                    //(before odr, on the thread that initialises it)
                                                    // also is it same as id or id2/2 
int main()
{

    auto id2 = std::this_thread::get_id(); // is this the same as id
    
    auto id4 = std::this_thread::get_id(); // what guarantees this is the same as id2
    std::cout << id << std::endl << id2 << std::endl << id3 << std::endl;
}
