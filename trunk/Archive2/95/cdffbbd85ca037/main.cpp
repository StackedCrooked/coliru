namespace N 
{
    enum E { A, B };
    E operator|(E, E);

    struct C 
    {   
        C(E);
    private:
        C(int);
    };  
}

namespace N
{
    enum F {};
    int operator|(F, int) = delete; 

    void Waldo()
    {   
        C(A | B); 
    }   
}
