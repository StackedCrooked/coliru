#include <string>
#include <fstream>
#include <stdexcept>
#include <limits>

class random_device {
public:
    typedef unsigned int result_type;

    explicit random_device(const std::string& token = "/dev/urandom") : token(token) { }

    result_type operator()() {
        result_type result;

        #ifdef _WIN32
            HCRYPTPROV prov;

            if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))  {
                throw std::runtime_error("CryptAcquireContext failed");
            }

            if (!CryptGenRandom(prov, sizeof(result), reinterpret_cast<unsigned char*>(&result)))  {
                throw std::runtime_error("CryptGenRandom failed");
            }

            CryptReleaseContext(prov, 0);
        #else
            std::ifstream urandom(token.c_str(), std::ios::in | std::ios::binary);

            if (!urandom.read(reinterpret_cast<char*>(&result), sizeof(result))) {
                throw std::runtime_error("reading from the random device failed");
            }
        #endif

        return result;
    }

    random_device(const random_device&) = delete;
    random_device& operator=(const random_device&) = delete;

    double entropy() const { return 0.; }
    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

private:
    std::string token;
};

int main(int argc, char** argv) {
    return 0;
}