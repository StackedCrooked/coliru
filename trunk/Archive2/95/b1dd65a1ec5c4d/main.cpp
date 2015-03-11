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
        std::cout<<"Setting receiver to "<<f<<std::endl;
        _fn = f;
    }
    private:
    CommsReceiverFn _fn;
};

class RDPParser {
    public:
    ~RDPParser(){
        std::cout<<"destroying parser"<<std::endl;
    }
    int ProcessInput(const CommsInterface::bytes& buffer){
        for(size_t i=0; i!=buffer.size();i++){
            std::cout<<"got "<<buffer[i]<<std::endl;
        }
        return 0;
    }
};

int devNULL(const CommsInterface::bytes&){
       std::cout<<"noop stub"<<std::endl;
        return 0; 
}

class RDP {
    public:
    RDP(CommsInterface &ci) : _ci(ci){}
    ~RDP(){
        std::cout<<"destroying RDP"<<std::endl;
        _ci.SetReceiver(boost::bind(&devNULL,_1));
        delete _p;
    }
    RDPParser* MakeParser(){
        _p = new RDPParser();
        _ci.SetReceiver(boost::bind(&RDPParser::ProcessInput,_p,_1));
        return _p;
    }
    private:
    CommsInterface &_ci;
    RDPParser* _p;
};


int main()
{
    const CommsInterface::bytes buffer = boost::assign::list_of<unsigned char>('1')('2')('3')('4')('5');
    CommsInterface ci;
    {
        RDP r(ci);
        r.MakeParser();
        ci.Write(buffer);
    }
    ci.Write(buffer);
    return 0;
}