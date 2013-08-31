template<typename T>
struct Helper
{
    T & getRegisterImpl()
    {
        static T instance;
        return instance;
    }

    template<typename Interface>
    void registerModuleClass()
    {
        T & reg = getRegisterImpl();
        (void)reg;
    }
};


struct RegisterImpl
{
    int data;
};


Helper<RegisterImpl> helper;


int main()
{    
    helper.registerModuleClass<int>();
    helper.getRegisterImpl();
}