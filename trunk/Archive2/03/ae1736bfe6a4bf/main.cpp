#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/assign/list_of.hpp>

class CommsInterface {
    public:
    typedef std::vector<unsigned char> bytes;
    typedef boost::function<int (const bytes&)> CommsReceiverFn;
    void Write(const bytes& data)
    {
        _fn(data);
    }
    void SetReceiver( CommsReceiverFn f ){
        _fn = f;
    }
    private:
    CommsReceiverFn _fn;
};

class RDPParser {
    public:
    int ProcessInput(const CommsInterface::bytes& buffer){
        for(size_t i=0; i!=buffer.size();i++){
            std::cout<<"got "<<buffer[i]<<std::endl;
        }
        return 0;
    }
};


class RDP {
    public:
    RDP(CommsInterface &ci) : _ci(ci){}
    RDPParser* MakeParser(){
        RDPParser *p = new RDPParser();
        _ci.SetReceiver(boost::bind(&RDPParser::ProcessInput,p,_1));
        return p;
    }
    void Unbind(RDPParser *p){
        _ci.SetReceiver(boost::bind(&RDP::NoOp,this,_1));
    }
    private:
    int NoOp(const CommsInterface::bytes&){
        std::cout<<"noop"<<std::endl;
        return 0; 
    }
    CommsInterface &_ci;
};


int main()
{
    CommsInterface ci;
    RDP r(ci);
    RDPParser* p = r.MakeParser();
    const CommsInterface::bytes buffer = boost::assign::list_of<unsigned char>('1')('2')('3')('4')('5');
    ci.Write(buffer);
    r.Unbind(p);
    ci.Write(buffer);
    delete p;
    return 0;
}