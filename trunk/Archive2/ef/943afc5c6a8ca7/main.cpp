#include <iostream>
#include <functional>
#include <utility>

struct Session {
    void dowork(){}
};

class task {
protected:
    task() {}
public:
    virtual void execute()=0;
    virtual ~task() {};
    void spawn(){/*something*/}
private:
    //Some private properties
};

template<typename T>
class ServerTask: public task {
public:
    ServerTask(T handler) {}
    void execute() {
        
    }
private:
	T task_work;
};

template<typename T>
ServerTask<T> make_task(T handler){
    return ServerTask<T>(std::move(handler));
}

int main(int argc,char** argv)
{
	Session session;
	std::function<void()> handler = std::bind(&Session::dowork,&session);
//    ServerTask<std::function<void()>> task(handler);
    auto task = make_task(std::move(handler));
}