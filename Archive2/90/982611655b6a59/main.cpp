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
  
     int currentSessions;
     bool running;
     
     void cleanUpSessions(){
         time_t timeNow;
         time(&timeNow);
         
        while(true) {
     
           if(difftime(timeNow, this->sessions.front().time) > 3000)  {
                 this->sessions.pop();
           }
           if(this->sessions.size() == 0) { break; }
        }
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
        this->sessions.push(c);
     }
    int getNumberOfSessions() {
        return this->sessions.size();
    }
}; 

int main(){
    
   SessionWindow<Call>& sw = SessionWindow<Call>::getInstance();

   Call c1;
    time(&c1.time);
     Call c2;
    time(&c2.time);
    sw.addSession(c1);
    sw.addSession(c2);

    std::cout << sw.getNumberOfSessions();
        
    
}