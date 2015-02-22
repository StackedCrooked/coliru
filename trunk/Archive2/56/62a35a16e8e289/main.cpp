#include <iostream>
#include <thread>
#include <vector>

using namespace std;

struct Line
{
    void hello() const {std::cout<<"hello"<<std::endl;}
};

struct Point {};

struct Environment
{
    std::vector<Line> _lines;
    std::vector<Point> _points;
};

struct Worker {
    int _threadId;
    Environment const* env;
    Worker(Environment const*, int);
    void run() const;
    void run2() const;
};

Worker::Worker(Environment const* e, int id):_threadId(id),env(e)
{
}

// worker that seems to do his job.
void Worker::run() const
{
    cout<<"in thread n "<<_threadId<<endl;
    vector<Line> const* lines = &env->_lines;

    for(std::vector<Line>::const_iterator it = lines->begin() ;it != lines->end(); ++it ){
        it->hello();
    }
}

// create a segfault
void Worker::run2() const
{
    cout<<"in thread n "<<_threadId<<endl;
    vector<Line> const& lines = env->_lines;

    for(auto it : lines){
        it.hello();
    }
}

int main() {
    Environment e;
    e._lines.resize(8);
    Worker w1{&e, 0};
    Worker w2{&e, 1};
    std::thread t1{&Worker::run, &w1};
    std::thread t2{&Worker::run2, &w2};
    t1.join();
    t2.join();
}
