#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <queue>
#include <memory>

template <typename BlockType>
class BlockPassing{
    public:
        BlockPassing() : blocks(), m() {}
        void push_back(const BlockType& b){
            std::lock_guard<std::mutex> guard(m);
            if(terminated)
                throw Terminated();
            blocks.push(b);
        }
        class Terminated{};
        void terminate(){
            std::lock_guard<std::mutex> guard(m);
            terminated = true;
        }
        class Empty{};
        BlockType pop_front(){
            std::lock_guard<std::mutex> guard(m);
            if(terminated && blocks.empty())
                throw Terminated();
            if(blocks.empty())
                throw Empty();
            
            auto ret = blocks.front();
            blocks.pop();
            
            return ret;
        }
        class TerminationGuard{
            public:
                TerminationGuard(BlockPassing& bp_) : bp(bp_) {}
                ~TerminationGuard(){
                    bp.terminate();
                }
            private:
                BlockPassing& bp;
        };
        TerminationGuard guard(){
            return TerminationGuard(*this);
        }
    private:
        std::queue<BlockType> blocks;
        std::mutex m;
        
        bool terminated = false;
};

class Input{
    public:
        Input(std::istream& s) : stream(s), bp(){
        }
        void inputMain(){
            auto terminationGuard = bp.guard();
            while(1){
                double val;
                stream >> val;
                bp.push_back(val);
                if(val == 0){
                    return;
                }
            }
        }
        BlockPassing<double>& getBlockPassing(){
            return bp;
        }
        ~Input(){
            myThread.join();
        }
        
    private:
        std::istream& stream;
        unsigned int i = 0;
        BlockPassing<double> bp;
        std::thread myThread{std::function<void()>(std::bind(&Input::inputMain, this))};
};

template <unsigned int i>
class Process{
    public:
        Process(BlockPassing<double>& bIn) : bpIn(bIn), bpOut(){
        }
        void processMain(){
            auto terminationGuard = bpOut.guard();
            while(1){
                try{
                    auto input = bpIn.pop_front();
                    bpOut.push_back(input + i*100);
                }
                catch(BlockPassing<double>::Empty&){
                }
                catch(BlockPassing<double>::Terminated&){
                    return;
                }
            }
        }
        BlockPassing<int>& getBlockPassing(){
            return bpOut;
        }
        ~Process(){
            myThread.join();
        }
        
    private:
        BlockPassing<double>& bpIn;
        BlockPassing<int> bpOut;
        std::thread myThread{std::function<void()>(std::bind(&Process::processMain, this))};
};

class Output{
    public:
        Output(BlockPassing<int>& b) : bp(b){
        }
        void outputMain(){
            while(1){
                try{
                    auto val = bp.pop_front();
                    std::cout << "obtained: " << val << std::endl;
                }
                catch(BlockPassing<int>::Empty&){
                }
                catch(BlockPassing<int>::Terminated&){
                    return;
                }
            }
        }
        ~Output(){
            myThread.join();
        }
        
    private:
        unsigned int i = 0;
        BlockPassing<int>& bp;
        std::thread myThread{std::function<void()>(std::bind(&Output::outputMain, this))};
};

int main() {
    Input in(std::cin);
    Process<1> process1(in.getBlockPassing());
    Process<2> process2(in.getBlockPassing());
    Output out1(process1.getBlockPassing());
    Output out2(process2.getBlockPassing());
    return 0;
}
