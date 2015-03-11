#include <iostream>
#include <string>
#include <map>
#include <memory>

class GnuTlsGlobalInit
{
    public:
        static std::unique_ptr<GnuTlsGlobalInit> make_guard() {
            return std::unique_ptr<GnuTlsGlobalInit> {new GnuTlsGlobalInit};
        }

        ~GnuTlsGlobalInit() {
            std::cout << __func__ << std::endl;
        }

    private:
        GnuTlsGlobalInit() {
            std::cout << __func__ << std::endl;
        }
};

int main()
{
    thread_local static auto gnutlGIG = GnuTlsGlobalInit::make_guard();
    
    std::cout << gnutlGIG << std::endl;
}