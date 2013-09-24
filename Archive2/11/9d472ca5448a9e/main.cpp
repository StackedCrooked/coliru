#include <queue>
#include <ctime>
#include <thread>
#include <mutex>
#include <iostream>

struct Call{
    time_t  time;
};

template <class T>
class SessionWindow {

  private:
  
     std::queue<T> sessions;
     std::mutex sessionsMutex;
     std::mutex runnningMutex;
  std::unique_ptr<std::thread> cleanUpThread;
     int currentSessions;
     bool running;
     
     void cleanUpSessions(){
         std::lock_guard<std::mutex> guard(sessionsMutex);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
         time_t timeNow;
         time(&timeNow);
         
        while(true) {
           
          std::cout << "in cleanup thread " << timeNow << " -- " << this->sessions.front().time << " -- " << this->sessions.size() << std::endl;
           std::this_thread::sleep_for(std::chrono::milliseconds(1000));
           if(difftime(timeNow, this->sessions.front().time) > 3000)  {
                 this->sessions.pop();
           }
           runnningMutex.lock();
           if(!running) { break; }
           runnningMutex.unlock();
        }
          std::cout << "thread stopped " << std::endl;
     }
     
     /* Singleton */
    SessionWindow() {};
    SessionWindow(SessionWindow const&);            
    void operator=(SessionWindow const&); 
    
    public: 
    
     static SessionWindow& getInstance()
        {
            static SessionWindow instance;
            return instance;
        }


     void addSession(T c){
        std::lock_guard<std::mutex> guard(sessionsMutex);
        this->sessions.push(c);
     }
    int getNumberOfSessions() {
        return this->sessions.size();
    }
    void start(){
        running = true;
        cleanUpThread = std::unique_ptr<std::thread>(new std::thread(&SessionWindow::cleanUpSessions, this));
    }
    void stop(){
         runnningMutex.lock();
        std::cout << "stopping" << std::endl;
        running = false;
        runnningMutex.unlock();
        cleanUpThread->join();
  
    }
 
 
}; 

int main(){
    
   SessionWindow<Call>& sw = SessionWindow<Call>::getInstance();
    sw.start();
   Call c1;
    time(&c1.time);
     Call c2;
    time(&c2.time);
    sw.addSession(c1);
    sw.addSession(c2);
      sw.stop();

        
    
}