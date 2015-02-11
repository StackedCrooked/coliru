#include <iostream>
#include <string>
#include <vector>
#include <memory> 

    class placeholder
    {
    public:
        virtual ~placeholder() {}

    };

    template<typename ValueType>
    class holder : public placeholder
    {
    public:
        holder(ValueType value) : held(value) {}

        template<typename Type>
        Type get(){
            return static_cast<Type> (held);
        }

    private:
        ValueType held;
    };


    class var
    {
    public:
        var() : content(0) {}

        template<typename ValueType>
        var(ValueType const & value) : content(new holder<ValueType>(value)) {

        }

        var(std::shared_ptr<var> other):
                content(other->content ? other->content : nullptr) {

        }

        var& operator=(const var& other) // copy assignment
        {
            if (this != &other) { // self-assignment check expected
                this-> content = other.content;
            }
            return *this;
        }

        template<typename ValueType>
        ValueType get(){
            return std::dynamic_pointer_cast<holder<ValueType> >(content)->get<ValueType>();
        }


// Implement swap as swapping placeholder pointers, assignment
// as copy and swap.

    private:
        std::shared_ptr<placeholder> content;
    };
    
int main()
{
    std::cout << "Hello world" << std::endl;
}
