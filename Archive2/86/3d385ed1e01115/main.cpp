

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct one
{
    void print_me()
    {
        std::cout << "one to rule them all" << std::endl;
    }
};

struct two
{
    int do_it(std::ostream& stream_a)
    {
        stream_a << "two's a crowd" << std::endl;
        return 6666;
    }
};

struct three
{
    void magicality(int param_a)
    {
        std::cout << "Magick! " << param_a << std::endl;
    }
    void magicality2(int param_a)
    {
        std::cout << "Super-Magick! " << param_a  * 2<< std::endl;
    }
};

struct notifier_base
{
    virtual void run()
    {
    }
    virtual ~notifier_base()
    {
    }
};

struct notify_provider;

template <class T, class U>
struct derived_notifier : public notifier_base
{
    derived_notifier(notify_provider& provider_a, T& object_a, U function_a)
    : provider_(&provider_a),
      object_(&object_a),
      function_(function_a)
    {
    }
    void run()
    {
    }
    T* object_;
    U function_;
    notify_provider* provider_;
};


struct notify_provider
{
    std::vector<notifier_base*> notifiers_;
    std::ostream* stream_;
    int int_value_;
    static void delete_notifier(notifier_base*& notifier_a)
    {
        delete notifier_a;
        notifier_a = 0;
    }

    static void run_notifier(notifier_base*& notifier_a)
    {
        notifier_a->run();
    }
    notify_provider() : stream_(&std::cout),
            int_value_(666)
    {
    }
    template <class T, class U> void add_notifier(T& object_a, U function_a)
    {
        notifiers_.push_back(
        new derived_notifier<T, U>(*this, object_a, function_a));
    }
    ~notify_provider()
    {
        std::for_each(notifiers_.begin(),
              notifiers_.end(),
              delete_notifier);
    }
    void run_all()
    {
        std::for_each(notifiers_.begin(),
              notifiers_.end(),
              run_notifier);
    }
};

template<>
void derived_notifier<one, void (one::*)()>::run()
{
    (object_->*function_)();
}

template<>
void derived_notifier<two, int (two::*)(std::ostream&)>::run()
{
    std::cout << (object_->*function_)(*(provider_->stream_))
          << std::endl;
}

template<>
void derived_notifier<three, void (three::*)(int)>::run()
{
    if (function_ == &three::magicality) {
    (object_->*function_)(provider_->int_value_);
    } else if (function_ == &three::magicality2) {
    (object_->*function_)(provider_->int_value_ + 1);
    }
}


int main(void)
{
    one number_one;
    two number_two;
    three number_three;
    notify_provider provider;
    provider.add_notifier(number_one, &one::print_me);
    provider.add_notifier(number_two, &two::do_it);
    provider.add_notifier(number_three, &three::magicality);
    provider.add_notifier(number_three, &three::magicality2);
    provider.run_all();
}