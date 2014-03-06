template<typename A, typename B, typename C>
class parent {}; 

template<typename A, typename B, typename C>
class child : public parent<A, B, C>
{
    public: 
        
        //child() : parent() {} // Error. 
        child() : parent<A, B,C>() {} // Works!
};



int main()
{
    return 0;
}
