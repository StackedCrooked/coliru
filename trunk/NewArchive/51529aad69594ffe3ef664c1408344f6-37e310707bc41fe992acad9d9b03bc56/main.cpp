#include <functional>

using namespace std;

template <class ObserverPolicy>
class Animation : public ObserverPolicy{
    
};

class FreeFunctionObserver{
    public:
    void play(){
        if(playHandle)
            playHandle();
    }
    void pause(){
        if(pauseHandle)
            pauseHandle();
    }
    void stop(){
        if(stopHandle)
            stopHandle();
    }
    void setPlayHandle(std::function<void(void)> p){
        playHandle = p;
    }
    void setPauseHandle(std::function<void(void)> p){
        pauseHandle = p;
    }
    void setStopHandle(std::function<void(void)> p){
        stopHandle = p;
    }
    private:
    std::function<void(void)> playHandle;
    std::function<void(void)> pauseHandle;
    std::function<void(void)> stopHandle;
};

void play(){}
void pause(){}
void stop(){}

int main(){
    Animation<FreeFunctionObserver> affo;
    affo.setPlayHandle(play);
    affo.play();
}
