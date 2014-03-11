template<typename A, typename B, typename C>
class parent {}; 

template<typename A, typename B, typename C>
class child : public parent<A, B, C>
{
    public: 
        child() : parent() {}
        //child() : parent<A, B,C>() {}
};



int main()
{
    return 0;
}
