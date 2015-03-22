#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <boost/asio.hpp>

// plain old data
template<typename T, typename std::enable_if<std::is_pod<T>::value>* = nullptr>
auto make_asio_buffer(const T& val)
{
    return boost::asio::buffer(&val, sizeof(T));
}

// string
auto make_asio_buffer(const std::string& str)
{
    return boost::asio::buffer(str.data(), str.size());
}

// vector
template<typename T>
auto make_asio_buffer(const std::vector<T>& vec)
{
    return boost::asio::buffer(vec.data(), vec.size());
}

template<typename... Ts>
auto make_asio_buffer_seq(const Ts&... args)
{
    return std::array<boost::asio::const_buffers_1, sizeof...(Ts)>{make_asio_buffer(args)...};
}

int main(int argc, char* argv[])
{
    int i{666};
    std::string s{"Satan"};
    std::vector<int> v{6, 6, 6};
    
    auto seq = make_asio_buffer_seq(i, s, v);
    // Powyzsza sekwencje podajesz boostowi do operacji zapisu. Generalnie, std::array spelnia wszystkie wymagania 
    //(Const)BufferSequence. Asio spodziewa sie po prostu kontenera, ktory bedzie mial poczatek oraz koniec
    // i ktorego iterator bedzie sie dalo inkrementowac. Iterator ma zwracac obiekty typu const_buffers_1 (dla zapisu)
    // lub mutable_buffers_1 dla odczytu. Asio wygeneruje wektoryzowane operacje zapisu i odczytu: writev i readv.
    
    std::size_t total{};
    for (const auto& buf : seq) 
    {
        total += boost::asio::buffer_size(buf);
    }
    
    std::cout << total << " bytes will be written" << std::endl;
        
    return 0;  
}
