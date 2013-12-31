#include <iostream>
#include <bitset>
#include <map>
#include <utility>

enum tpErros {errCadPref,
			  errPredio,
			  errLote,
			  errQuadra,
			  errTestada,
			  errLogradouro,
			  errAgua,
			  errEsgoto,
			  numErros};
              
typedef std::bitset<tpErros::numErros> setErros;


struct TConsumidor{
    int cdc;
    int lol;
    TConsumidor(int cod, int dum): cdc(cod), lol(dum) {
        std::cout << cdc << " criado"  << "\n";        
    };
    ~TConsumidor() {
        std::cout << cdc << " sendo destruido"  << "\n";        
    };
};
typedef struct TConsumidor TConsumidor;

typedef std::map<int,TConsumidor> TConsumidores;
    
int main()
{
    TConsumidores consumidores;
    
    {
        
        TConsumidor consumidor1(1,2);
        TConsumidor consumidor2(2,4);
        TConsumidor consumidor3(3,6);
        
        std::cout << "\n";
        
        if ( consumidores.insert(std::make_pair(1, consumidor1)).second )
            std::cout << consumidor1.cdc << " inserido"  << "\n";
        if ( consumidores.insert(std::make_pair(2, consumidor2)).second )
            std::cout << consumidor2.cdc << " inserido"  << "\n";
        if ( consumidores.insert(std::make_pair(1, consumidor3)).second )
            std::cout << consumidor3.cdc << " inserido"  << "\n";
        else 
            std::cout << consumidor3.cdc << " não inserido"  << "\n";
    
        std::cout << "\n";
    }
    
    std::cout << "\n";
    
    for (const auto &pair : consumidores) {
        std::cout << pair.first
              << " tem o valor '"
	          << pair.second.lol << "'\n";
    }
    
    std::cout << "Clear\n";
    consumidores.clear();
    std::cout << "Done\n";
    
    
}
