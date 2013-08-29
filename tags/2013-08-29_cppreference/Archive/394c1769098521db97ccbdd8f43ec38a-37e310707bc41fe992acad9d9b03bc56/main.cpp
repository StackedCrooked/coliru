#include <functional>

using namespace std;

template <class ObserverPolicy>
class Animation : public ObserverPolicy{
    
};

class MonolithicObserver{
    public:
    void play(){
        state = playing;
    }
    void pause(){
        if(playing == state)
            state = stopped;
    }
    void stop(){
        state = stopped;
    }
    private:
    enum {playing, paused, stopped} state;
};

struct doNothing{
    static void play(){}
    static void pause(){}
    static void stop(){}
};

struct throwException{
    class noPlay{};
    class noPause{};
    class noStop{};
    static void play(){
        throw noPlay();
    }
    static void pause(){
        throw noPause();
    }
    static void stop(){
        throw noStop();
    }
};

template <class DefaultPolicy = doNothing>
class FreeFunctionObserver{
    public:
    void play(){
        if(playHandle)
            playHandle();
        else
            DefaultPolicy::play();
    }
    void pause(){
        if(pauseHandle)
            pauseHandle();
        else
            DefaultPolicy::pause();
    }
    void stop(){
        if(stopHandle)
            stopHandle();
        else
            DefaultPolicy::stop();
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
    Animation<FreeFunctionObserver<> > affo;
    affo.setPlayHandle(play);
    affo.setPauseHandle(pause);
    affo.setStopHandle(stop);
    affo.play();
    affo.pause();
    affo.stop();
    
    Animation<FreeFunctionObserver<throwException> > affot;
    try{
        affot.play();
    }
    catch(throwException::noPlay&){}
    
    Animation<MonolithicObserver> amo;
    amo.play();
    amo.pause();
    amo.stop();
}
