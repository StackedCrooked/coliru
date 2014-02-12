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
            while(1){
                double val;
                stream >> val;
                bp.push_back(val);
                if(val == 0)
                    return;
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

class Elaborate{
    public:
        Elaborate(BlockPassing<double>& bIn) : bpIn(bIn), bpOut(){
        }
        void elaborateMain(){
            while(1){
                try{
                    auto input = bpIn.pop_front();
                    if(input == 0){
                        bpOut.push_back(input);
                        return;
                    }
                    else
                        bpOut.push_back(++input);
                }
                catch(BlockPassing<double>::Empty&){
                }
            }
        }
        BlockPassing<double>& getBlockPassing(){
            return bpOut;
        }
        ~Elaborate(){
            myThread.join();
        }
        
    private:
        BlockPassing<double>& bpIn;
        BlockPassing<double> bpOut;
        std::thread myThread{std::function<void()>(std::bind(&Elaborate::elaborateMain, this))};
};

class Output{
    public:
        Output(BlockPassing<double>& b) : bp(b){
        }
        void outputMain(){
            while(1){
                try{
                    auto val = bp.pop_front();
                    if(val == 0)
                        return;
                    std::cout << "obtained: " << val << std::endl;
                }
                catch(BlockPassing<double>::Empty&){
                }
            }
        }
        ~Output(){
            myThread.join();
        }
        
    private:
        unsigned int i = 0;
        BlockPassing<double>& bp;
        std::thread myThread{std::function<void()>(std::bind(&Output::outputMain, this))};
};

int main() {
    Input in(std::cin);
    Elaborate elaborate(in.getBlockPassing());
    Output out(elaborate.getBlockPassing());
    return 0;
}
