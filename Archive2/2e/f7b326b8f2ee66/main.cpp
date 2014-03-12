    

    #include <iostream>
    #include <string>
    #include <thread>
    #include <mutex>
    #include <condition_variable>
    #include <vector>
    #include <random>
    std::mutex p_mutex;
    std::vector<std::pair<std::thread::id ,int > > komunikat;
    std::mt19937 eng;
    std::uniform_int_distribution<int> randoms(1, 6);
    void watek(){
            p_mutex.lock();
            komunikat.push_back(std::make_pair(std::this_thread::get_id() ,randoms(eng)));
            p_mutex.unlock();
    }
     
    int main(){
             std::cout<<"Główny Wątek"<<std::endl;
             std::vector<std::thread> Threadss(10);
            for(auto&& t: Threadss){
                     t = std::thread(watek);
            }
            
            for(auto&& t: Threadss){
                     t.join();
            }
            for(auto l: komunikat){
                    std::cout<<"Wątek "<<l.first<<": "<<l.second<<std::endl;
            }
    }

