#include <iostream>
#include <functional>
#include <vector>

struct Requester {};
struct Response {};

struct Response1 : public Response {};

typedef std::function<void(Requester*, const Response&)> ResponseCallback;

template<typename TResponse>
class ConcreteResponseCallback
{
    typedef std::function<void(Requester*, const TResponse&)> ConcreteCallback;

public:
	ConcreteResponseCallback(const ConcreteCallback& concreteCallback)
		: m_concreteCallback(concreteCallback)
	{
	}

	void operator()(Requester* requester, const Response& response) const
	{
        std::cout << __FUNCTION__ << std::endl;
		m_concreteCallback(requester, response);
	}

private:
	ConcreteCallback m_concreteCallback;
};

void freeFunc(Requester*, const Response&)
{
    std::cout << __FUNCTION__ << std::endl;
}

int main()
{
    std::vector<ResponseCallback> v;
    v.push_back(&freeFunc);
    v.push_back(&freeFunc);

    for (const ResponseCallback& c : v)
    {
        c(NULL, Response());
    }
}
