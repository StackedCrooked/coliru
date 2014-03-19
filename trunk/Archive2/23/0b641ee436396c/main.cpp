#include <iostream>

class IChar
{
    public:
    
        virtual ~IChar() { }
    
        virtual void SetSerie(const int serie) = 0;
        
        virtual int GetSerie() const = 0;
        
};

class CChar : public IChar
{
    public:
    
        CChar() : m_serie(0) { }
        
        virtual ~CChar() { }
        
        void SetSerie(const int serie) override
        {
            m_serie = serie;   
        }
        
        int GetSerie() const override
        {
            return m_serie;   
        }
        
    private:
    
        int m_serie;
    
};

class ICharFrancais : public virtual IChar
{
    public:
    
        virtual ~ICharFrancais() { }
    
        virtual void SetEquipageTotal(const int total) = 0;
        
        virtual int GetEquipageTotal() const = 0;
    
};

class CCharFrancais : public virtual CChar, public virtual ICharFrancais
{
    public:
    
        CCharFrancais() : m_total(0) { }
        
        virtual ~CCharFrancais() { }
    
        void SetEquipageTotal(const int total) override
        {
            m_total = total;
        }
        
        int GetEquipageTotal() const override
        {
            return m_total;   
        }
    
    private:
    
        int m_total;
    
};

int main()
{
    ICharFrancais* pCharFr = new CCharFrancais;
    
    std::clog << pCharFr->GetEquipageTotal() << std::endl;
    
    delete pCharFr;
    
    return 0;   
}