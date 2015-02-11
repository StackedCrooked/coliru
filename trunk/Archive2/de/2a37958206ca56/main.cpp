#include <iostream>
#include <string>
#include <vector>


        class storage{

        };


        class placeholder
        {
        public:
            virtual ~placeholder() {}


            template<typename T>
            T get(){
                return 0;
            }

        };

        template<typename ValueType>
        class holder : public placeholder
        {

        public:
            holder(ValueType value) : held(value) {}

            auto& value(){
                return held;
            };



/*
            std::string get(std::string& str){
                std::stringstream ss;
                ss << held;
                return ss.str();
            }

            template<typename Type>
            Type get(std::string& str){

                std::stringstream ss(str);
                Type result;
                return ss >> result ? result : 0;

            }
*/



            template<typename Type>
            Type get(){

                return 0;
            }


        private:
            ValueType held;
        };





        class var
        {
        public:


            struct storage{

                storage(){
                    stored = false;
                }

                struct inner
                {

                    template <typename T>
                    auto operator()(T value, storage* ptr) // N3386 Return type deduction
                    {


                            static auto lambda = [&](){
                                std::shared_ptr<T> param(new T(value));

                            return [param](){

                                return *param;
                            };

                        }();

                        if(ptr->stored){
                            return lambda();
                        } else {
                            ptr->stored = true;
                        }

                    }



                };


                inner in;

                template<typename T>
                auto operator()(T value){
                    return in(value, this);
                }

                bool stored;
            };


            storage stooge;

            var() : content(0) {}

            template<typename ValueType>
            var(ValueType value) : content(new holder<ValueType>(value)) {

                stooge(value);

                decltype(stooge(0)) val = 10;

                std::cout << val <<std::endl;

            }



            var& operator=(const var& other) // copy assignment
            {
                if (this != &other) { // self-assignment check expected
                    this-> content = other.content;
                }
                return *this;
            }


            template <typename ValueType>
            operator ValueType() const {

                return 0;
/*
                auto* container = std::dynamic_pointer_cast<holder<decltype(stooge(0))> >(content);

                return container->get<ValueType>();*/

            }

            template <typename ValueType>
            auto operator=(const ValueType& other)
            {
                this->content = std::shared_ptr<placeholder>(new holder<ValueType>(other));
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
    std::cout << "Code" << std::endl;
}
