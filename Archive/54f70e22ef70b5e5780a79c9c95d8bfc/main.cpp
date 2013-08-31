template <typename Init, typename Destroy>
struct Initializer
{
    Initializer() 
    {
        Init();        
    }

	~Initializer()
    {
        Destroy();
    }
};


//Then, just include a static instance of Initializer<> at the bottom
// of your class definition, and you have a cheap and free "static constructor".