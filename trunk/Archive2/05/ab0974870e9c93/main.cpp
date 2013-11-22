#include <iostream>
#include <memory>

class Particle
{
public:
    Particle( int nID)
    {
        m_nID = nID;
        std::cout << "Particle " << m_nID << "번 생성" << std::endl;
    }
    
    ~Particle()
    {
        std::cout << "Particle " << m_nID << "번 소멸" << std::endl;
    }
    
    int m_nID;
};

Particle* GetParticlePointer(std::shared_ptr<Particle>& ParticlePtr)
{
    return ParticlePtr.get();
}

int main()
{
    std::cout << "shared_ptr " << std::endl;
    
    {
        std::shared_ptr<Particle> ParticlePtr( new Particle[2], std::default_delete<Particle[]>() );
        ParticlePtr.get()[0].m_nID = 11;
        ParticlePtr.get()[1].m_nID = 12;
        
        std::cout << ParticlePtr.get()[0].m_nID << ", " << ParticlePtr.get()[1].m_nID << std::endl;
        
    }
    
    return 0;
}