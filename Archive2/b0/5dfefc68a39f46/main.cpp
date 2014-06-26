#include<iostream>

    class X{
        private:
        int* i_data;
        public: 
        
        X()
        {
            i_data = new int(10);
        }
        
        static void* operator new(std::size_t sz)
        {
            std::cout << "custom new operator for size " << sz << std::endl;
            return ::operator new(sz);
        }
        
        static void* operator new[](std::size_t sz)
        {
            std::cout << "custom new array operator " << sz << std::endl;
            return ::operator new[](sz);
        }
        
        bool operator != (const X& rhs)
        {
            return this != &rhs;   
        }
        
        X operator=(const X& rhs)
        {
            if ( *this != rhs)
            {
                delete this->i_data;
                this->i_data = new int(*rhs.i_data);
                return *this;
            }
            else
            return *this;            
        }
        void SetData(int data)
        {
            *(this->i_data) = data;
        }
        
        int GetData()
        {
            return *(this->i_data);
        }
        
    };

int main()
{
    X xa;
    xa.SetData(20);
    
    std::cout << "Xa->i_data = " << xa.GetData() << std::endl;
    
    xa.SetData(30);
    X xb = xa;
    std::cout << "Xb->i_data = " << xb.GetData() << std::endl;
    
    X* p = new X;
    delete p;
    
    X* pa = new X[10];
    delete[] pa;  
}
    
    