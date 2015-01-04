#include <vector>       // std::vector
#include <map>
#include <iostream>

struct Command {
    int cmdNum;
    int numArgs;
    std::vector<int> args;
};

struct Invocation {
    enum Source {
        SOURCE_X = 0, SOURCE_Y, SOURCE_Z,
        SOURCE_END
    };
    Source src;
    Command cmd;
};

struct Bindable {
    virtual void handleCmd(Command Cmd) = 0;
};

struct A : Bindable {
    void handleCmd (Command cmd) {
        std::cout << "called handler-method of class A" <<std::endl;
        std::cout << "cmdNum: " << cmd.cmdNum <<std::endl;
    }
};

struct B : Bindable {
    void handleCmd (Command cmd) {
        std::cout << "called handler-method of class B" <<std::endl;
        std::cout << "cmdNum: " << cmd.cmdNum <<std::endl;
    }
};

struct Mapper {
    void bindCmd(Command cmd, Bindable* mBindable) {
        //Fill a multimap with cmd.cmdNum as keys and mBindable as values
        mBinds.insert({cmd.cmdNum, mBindable});
    }

    //Send cmd to each registered Bindable for the respective cmdNum
    void handleInv(Invocation inv) {
        auto mMatches = mBinds.equal_range(inv.cmd.cmdNum);
        
        struct pair_range
        {
            decltype(mMatches) r;
            auto begin() -> decltype(r.first) { return r.first; }
            auto end() -> decltype(r.second) { return r.second; }
        };

        for(auto mMatch : pair_range{mMatches}) {
            mMatch.second->handleCmd(inv.cmd);
        }
    }

private:
    std::multimap<int, Bindable*> mBinds;
};

int main() {
    A a;
    B b;

    Command cmdA = {200, 4, {1,2,3,4}};
    Command cmdB = {400, 3, {3,2,1}};
    Command cmdC = {600, 2, {8,9}};

    Invocation invA = {Invocation::SOURCE_X, cmdA};
    Invocation invB = {Invocation::SOURCE_Z, cmdB};
    Invocation invC = {Invocation::SOURCE_Z, cmdC};

    Mapper mMapper;

    //Register Commands
    mMapper.bindCmd(cmdA, &a);
    mMapper.bindCmd(cmdB, &a);
    mMapper.bindCmd(cmdA, &b);
    mMapper.bindCmd(cmdC, &b);

    //React to incoming Invocations
    mMapper.handleInv(invA); //Call handleCmd of a and b
    mMapper.handleInv(invB); //Call handleCmd of a
    mMapper.handleInv(invC); //Call handleCmd of b
}