#include <iostream>
#include <vector>

template<typename R>
class AnInterface
{
    public:
        virtual R run() = 0;
        virtual ~AnInterface() {}
};

template<typename R>
class Processor
{
    public:
        Processor(std::vector<AnInterface<R>*> toRun) : toRun(toRun) {}
        std::vector<R> process() {
            std::vector<R> res;
            for(int i = 0; i < this->toRun.size(); ++i)
               res.push_back(toRun[i]->run());
            return res;
            }

    private:
        std::vector<AnInterface<R>*> toRun;
};


class AnInstanceClass : public AnInterface<int>
{
    public:
    int run() override { return 1+1; }
};

int main()
{
    std::vector<AnInterface<int>*> toRun;
    toRun.push_back(new AnInstanceClass{});
    toRun.push_back(new AnInstanceClass{});
    Processor<int> p(toRun);
    std::vector<int> pRes = p.process();
    for(auto& resVal : pRes)
     std::cout << resVal << " ";
    std::cout << std::endl;
    return 0;
}