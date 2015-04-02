#include <iostream>
#include <string>


std::string foo(
    void (*bar)(
		void (*collectFunc)(
			std::string message
		)
	)
) {
    std::string result = "";
    auto collectFunc = [&](
    		std::string message
	) {
		result = result + message;
	};
    
    bar(collectFunc);
    
    return result;
}

int main()
{
    std::string result = foo([&](void (*collect)(std::string message)) {
        collect("asdf");
        collect("qwer");
    });
    
    std::cout << result << std::endl;
    
    return 0;
}

