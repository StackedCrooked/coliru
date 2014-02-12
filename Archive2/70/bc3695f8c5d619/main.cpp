#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <queue>
#include <memory>
#include <vector>
#include <boost/numeric/interval.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/optional.hpp>

struct GCode {
    GCode() : address(), value() {}
    char address;
    boost::optional<double> value;
};

std::vector<GCode> parse(const std::string& line){
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    using qi::double_;
    using qi::char_;
    using qi::phrase_parse;
    using ascii::space;
    
    std::vector<boost::fusion::vector<char, boost::optional<double>>> v;
    qi::phrase_parse(
        std::begin(line),
        std::end(line),
        *(char_ >> (-double_)),
        space,
        v
    );
        
    std::vector<GCode> ret;
    auto populate = [&ret](const boost::fusion::vector<char, boost::optional<double>>& c){
        GCode res;
        res.address = boost::fusion::at_c<0>(c);
        std::cout << "GCode: " << res.address;
        if(boost::fusion::at_c<1>(c)){
            res.value = *(boost::fusion::at_c<1>(c));
            std::cout << ", " << *(res.value);
        }
        std::cout << std::endl;
        ret.push_back(res);
    };
    std::for_each(
        std::begin(v),
        std::end(v),
        populate
    );
    return ret;
}

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
        using outBlock = double;
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
        BlockPassing<outBlock>& getBlockPassing(){
            return bp;
        }
        ~Input(){
            myThread.join();
        }
        
    private:
        std::istream& stream;
        unsigned int i = 0;
        BlockPassing<outBlock> bp;
        std::thread myThread{std::function<void()>(std::bind(&Input::inputMain, this))};
};

class Process{
    public:
        using inBlock = Input::outBlock;
        using outBlock = boost::numeric::interval<inBlock>;
        Process(BlockPassing<inBlock>& bIn) : bpIn(bIn), bpOut(){
        }
        void processMain(){
            auto terminationGuard = bpOut.guard();
            while(1){
                try{
                    auto input = bpIn.pop_front();
                    auto plus = 0.001;
                    auto interval = outBlock{input - plus, input + plus};
                    bpOut.push_back(interval + interval/100.);
                }
                catch(BlockPassing<inBlock>::Empty&){
                }
                catch(BlockPassing<inBlock>::Terminated&){
                    return;
                }
            }
        }
        BlockPassing<outBlock>& getBlockPassing(){
            return bpOut;
        }
        ~Process(){
            myThread.join();
        }
        
    private:
        BlockPassing<inBlock>& bpIn;
        BlockPassing<outBlock> bpOut;
        std::thread myThread{std::function<void()>(std::bind(&Process::processMain, this))};
};

template <typename T>
std::ostream& operator << (std::ostream& stream, const boost::numeric::interval<T>& val){
    stream << '[' << boost::numeric::lower(val) << ", " << boost::numeric::upper(val) << ']';
    return stream;
}

class Output{
    public:
        Output(BlockPassing<Process::outBlock>& b) : bp(b){
        }
        void outputMain(){
            while(1){
                try{
                    auto val = bp.pop_front();
                    std::cout << val << std::endl;
                }
                catch(BlockPassing<Process::outBlock>::Empty&){
                }
                catch(BlockPassing<Process::outBlock>::Terminated&){
                    return;
                }
            }
        }
        ~Output(){
            myThread.join();
        }
        
    private:
        unsigned int i = 0;
        BlockPassing<Process::outBlock>& bp;
        std::thread myThread{std::function<void()>(std::bind(&Output::outputMain, this))};
};

int main() {
    Input in(std::cin);
    Process process(in.getBlockPassing());
    Output out(process.getBlockPassing());
    
    parse("G01 X100.2 Y Z10.4");
    return 0;
}
