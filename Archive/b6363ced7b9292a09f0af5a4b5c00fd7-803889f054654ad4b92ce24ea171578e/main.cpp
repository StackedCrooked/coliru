#include <stdexcept>

struct CURL;
enum CURLoption {CURLOPT_URL};
enum CURLcode {CURLE_OK};
CURL* curl_easy_init() {return NULL;}
void curl_easy_cleanup(CURL*) {}
CURLcode curl_easy_setopt(CURL*, CURLoption, ...) {return CURLE_OK;}

class curl_wrapper
{
    curl_wrapper(const curl_wrapper&);
    curl_wrapper& operator=(const curl_wrapper&);
 
    CURL *_curl_handle;
	CURLcode _curl_code;
 
public:
	curl_wrapper()
		: _curl_handle(curl_easy_init()), _curl_code(CURLE_OK)
	{
		if (_curl_handle == NULL)
			throw std::runtime_error("curl_easy_init() failed");
	}
 
	curl_wrapper(curl_wrapper&& c)
		: _curl_handle(nullptr), _curl_code(CURLE_OK)
	{
		std::swap(_curl_handle, c._curl_handle);
		std::swap(_curl_code, c._curl_code);
	}
 
	~curl_wrapper()
	{
		if (_curl_handle)
			curl_easy_cleanup(_curl_handle);
	}
 
	template <typename T>
	curl_wrapper& operator()(CURLoption option, T value) &
	{
		if ((_curl_code = curl_easy_setopt(_curl_handle, option, value)) != CURLE_OK)
			throw std::runtime_error("curl_easy_setopt() failed"); 
		return *this;
	}
 
    template <typename T>
	curl_wrapper&& operator()(CURLoption option, T value) &&
	{
		if ((_curl_code = curl_easy_setopt(_curl_handle, option, value)) != CURLE_OK)
			throw std::runtime_error("curl_easy_setopt() failed"); 
		return std::move(*this);
	}
};


#include <vector>
int main() {
    std::vector<curl_wrapper> vec;
        vec.push_back
            (
            curl_wrapper()
                (CURLOPT_URL, "some_url.com")
            );
}