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
            blocks.push(b);
        }
        class Empty{};
        BlockType pop_front(){
            std::lock_guard<std::mutex> guard(m);
            if(blocks.empty())
                throw Empty();
            
            auto ret = blocks.front();
            blocks.pop();
            
            return ret;
        }
    private:
        std::queue<BlockType> blocks;
        std::mutex m;
};

class Input{
    public:
        Input(std::istream& s) : stream(s), bp(){
        }
        void inputMain(){
            while(i++ < 8){
                double val;
                stream >> val;
                bp.push_back(val + 1);
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

class Output{
    public:
        Output(BlockPassing<double>& b) : bp(b){
        }
        void outputMain(){
            while(1){
                try{
                    auto val = bp.pop_front();
                    std::cout << "obtained: " << val << std::endl;
                    first = false;
                }
                catch(BlockPassing<double>::Empty&){
                    if(!first)
                        break;
                }
            }
        }
        ~Output(){
            myThread.join();
        }
        
    private:
        unsigned int i = 0;
        BlockPassing<double>& bp;
        bool first = true;
        std::thread myThread{std::function<void()>(std::bind(&Output::outputMain, this))};
};

int main() {
    Input in(std::cin);
    Output out(in.getBlockPassing());
    return 0;
}
