    #include <setjmp.h>
    jmp_buf env;
    
    class timeBomb{
    public:
        timeBomb() {}
        void detonate(int time){
            sleep(time);
            longjmp(env,0);
        }
    };
    int main(){
        int callBack;
        
        timeBomb *myBomb = new timeBomb();
        callBack = setjmp(env);
        if (callBack) {
            delete myBomb;
            return callBack;
        }     
        myBomb->detonate(2);
    }