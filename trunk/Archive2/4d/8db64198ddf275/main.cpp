

template<class Type>
class Sample{
    public:    
   Sample( Type T ):test(T)
    {
        
    }
    Sample( ):test{}
    {
        
    }

        Type test;
};

int main(int argc, char* argv[])
{
    Sample<int> a;
    Sample<char> b;
    
    return 0;
}
