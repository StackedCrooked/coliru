struct Base
{
    Base operator->(){ return *this; }    
};


int main()
{
    Base()->operator=(Base());
}