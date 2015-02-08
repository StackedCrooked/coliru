#pragma once

#include <algorithm>
#include <functional>
#include <forward_list> //TODO vector vs forward_list
#include <vector>



namespace cw{

    template<typename R, typename... Args>
    class delegate
    {
    public:
        template<typename U>
        delegate& operator += (const U &function)
        {
            auto before_end = callbacks.before_begin();
            for (auto& _ : callbacks)
                ++ before_end;

            callbacks.insert_after(before_end, function);

            return *this;
        }

        template<typename U>
        delegate& operator -= (const U &function){

            callbacks.remove(function);
            return *this;

        }

        std::vector<R> operator () (Args... args)
        {
            std::vector<R> res;
            for (auto callback : callbacks)
            {
                res.push_back(callback(args...));
            }
            return res;
        }

        void clear(){
            callbacks.clear();
            return *this;
        }

    private:
        std::forward_list<std::function<R(Args... args)> > callbacks;
    };

    //Void specialization
    template<typename... Args>
    class delegate<void, Args...>
    {
    public:
        template<typename U>
        delegate& operator += (const U &function)
        {
            auto before_end = callbacks.before_begin();
            for (auto& _ : callbacks)
                ++ before_end;

            callbacks.insert_after(before_end, function);

            return *this;
        }

        template<typename U>
        delegate& operator -= (const U &function){

            callbacks.remove(function);
            return *this;

        }

        void operator () (Args... args)
        {
            for (auto callback : callbacks)
            {
                callback(args...);
            }
        }

        void clear(){
            callbacks.clear();
            return *this;
        }

    private:
        std::forward_list<std::function<void(Args... args)> > callbacks;
    };


}
