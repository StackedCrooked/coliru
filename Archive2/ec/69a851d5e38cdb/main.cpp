#include <string>
#include <memory>
#include <type_traits>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <unordered_map>

#include <boost/optional.hpp>

std::string program = R"program(module hello_world
{
    import lib.console;
    
    auto entry = []()
    {
        a << b;
        c ->> d;
        console.print("hello world!");
    };
})program";

// #include <reaver/unit.h>
namespace reaver
{
    struct unit
    {
    };
}

// #include <reaver/semaphore.h>
namespace reaver
{
    class semaphore
    {
    public:
        semaphore() : _count{ 0 }
        {
        }
    
        void notify(std::size_t i = 1)
        {
            {
                std::unique_lock<std::mutex> lock{ _mutex };
                _count += i;
            }
            
            while (i--)
            {
                _condition.notify_one();
            }
        }
        
        void wait()
        {
            std::unique_lock<std::mutex> lock{ _mutex };
            while (!_count)
            {
                _condition.wait(lock);
            }
            --_count;
        }
    
        bool try_wait()
        {
            std::unique_lock<std::mutex> lock{ _mutex };
            if (!_count)
            {
                return false;
            }
            --_count;
            return true;
        }
        
    private:
        std::mutex _mutex;
        std::condition_variable _condition;
        std::atomic<std::size_t> _count;
    };
}

namespace reaver
{
    namespace vapor
    {
        namespace lexer
        {
            enum class token_type
            {
                none,
                identifier,
                module,
                import,
                auto_,
                dot,
                curly_bracket_open,
                curly_bracket_close,
                square_bracket_open,
                square_bracket_close,
                round_bracket_open,
                round_bracket_close,
                angle_bracket_open,
                angle_bracket_close,
                semicolon,
                right_shift,
                left_shift,
                map,
                count                    // always the last
            };
            
            constexpr std::size_t operator+(token_type type)
            {
                return static_cast<std::size_t>(type);
            }
            
            extern std::array<std::string, +token_type::count> token_types;
            
            extern std::unordered_map<std::string, token_type> keywords;
            extern std::unordered_map<char, token_type> symbols1;
            extern std::unordered_map<char, std::unordered_map<char, token_type>> symbols2;
            extern std::unordered_map<char, std::unordered_map<char, std::unordered_map<char, token_type>>> symbols3;
            
            class iterator;
            
            struct position
            {
                position() {}
                position(const position &) = default;
                position(position &&) = default;
                
                bool operator!=(const position & rhs) const
                {
                    return offset != rhs.offset;
                }
                
                std::size_t operator-(const position & rhs) const
                {
                    // throw assert(offset > rhs.offset)
                    return offset - rhs.offset;
                }
                
                position & operator+=(std::size_t len)
                {
                    offset += len;
                    column += len;
                    return *this;
                }
                
                position operator+(std::size_t len) const
                {
                    position ret(*this);
                    ret += len;
                    return ret;
                }
                
                std::size_t offset = 0;
                std::size_t line = 1;
                std::size_t column = 1;
                std::string file;
            };
            
            class range
            {
            public:
                range() = default;
                range(const range &) = default;
                range(range &&) = default;
            
                range(position s, position e) : _start{ std::move(s) }, _end{ std::move(e) }
                {
                    // throw: assert(s.offset <= e.offset);
                }
                
                const position & start() const
                {
                    return _start;
                }
                
                const position & end() const
                {
                    return _end;
                }
                
            private:
                position _start;
                position _end;
            };

            std::ostream & operator<<(std::ostream & os, const range & r)
            {
                if (r.end() - r.start() > 1)
                {
                    return os << r.start().line << ":" << r.start().column << " - " << r.end().line << ":" << r.end().column;
                }
                
                return os << r.start().line << ":" << r.start().column;
            }    
            
            struct token
            {
                token() {}
                token(const token &) = default;
                token(token &&) = default;
                
                token(token_type t, std::string s, class range r) : type{ t }, string{ std::move(s) }, range{ std::move(r) }
                {
                }
                
                token_type type;
                std::string string;
                class range range;
            };
            
            std::ostream & operator<<(std::ostream & os, const token & tok)
            {
                return os << "token type: `" << token_types[+tok.type] << "` token value: `" << tok.string << "` token range: " << tok.range;
            };
            
            namespace _detail
            {
                class _iterator_backend;
                
                class _lexer_node
                {
                public:
                    friend class lexer::iterator;
                    friend class _iterator_backend;
                    
                    _lexer_node(token tok) : _token{ std::move(tok) }
                    {
                    }
                    
                    void wait_next()
                    {
                        std::unique_lock<std::mutex> lock{ _m };
                        _cv.wait(lock);
                    }
                    
                private:
                    std::shared_ptr<_lexer_node> _next;
                    token _token;
                    std::mutex _m;
                    std::condition_variable _cv;
                };
                
                class _iterator_backend
                {
                public:
                    template<typename Iter>
                    _iterator_backend(Iter begin, Iter end, std::shared_ptr<_lexer_node> & node) : _thread{ [&](){ _worker(begin, end); } }
                    {
                        _sem.wait();
                        node = std::move(_initial);
                    }

                    ~_iterator_backend()
                    {
                        _end_flag = true;
                        // _thread.join();
                        _thread.detach();
                    }
                    
                private:
                    template<typename Iter>
                    void _worker(Iter begin, Iter end, std::string filename = "")
                    {
                        std::shared_ptr<_lexer_node> node = nullptr;
                        
                        position pos;
                        pos.offset = 0;
                        pos.column = 0;
                        pos.line = 1;
                        pos.file = std::move(filename);
                        
                        auto get = [&]() -> boost::optional<char>
                        {
                            if (begin == end)
                            {
                                return {};
                            }
                            
                            if (*begin == '\n')
                            {
                                pos.column = 0;
                                ++pos.line;
                            }
                            else
                            {
                                ++pos.column;
                            }
                            
                            return *begin++;
                        };
                        
                        auto peek = [&](std::size_t x = 1) -> boost::optional<char>
                        {
                            for (int i = 0; i < x; ++i)
                            {
                                if (begin + i == end)
                                {
                                    return {};
                                }
                            }
                            
                            return *(begin + x);
                        };
                        
                        auto generate_token = [&](token_type type, position begin, position end, std::string string)
                        {
                            if (!node)
                            {
                                _initial = std::make_shared<_lexer_node>(token{ type, std::move(string), range(begin, end) });
                                _sem.notify();
                                node = _initial;
                            }
                            
                            else
                            {
                                node->_next = std::make_shared<_lexer_node>(token{ type, std::move(string), range(begin, end) });
                                node->_cv.notify_all();
                                node = node->_next;
                            }
                        };
                        
                        while (!_end_flag && begin != end)
                        {
                            auto next = get();
                            
                            {
                                auto second = peek();
                                auto third = peek();
                                
                                if (second && third && symbols3.find(*next) != symbols3.end() && symbols3[*next].find(*second) != symbols3[*next].end() 
                                    && symbols3[*next][*second].find(*third) != symbols3[*next][*second].end())
                                {
                                    auto p = pos;
                                    generate_token(symbols3[*next][*second][*third], pos, pos + 3, { *next, *get(), *get() });
                                }

                                else if (second && symbols2.find(*next) != symbols2.end() && symbols2[*next].find(*second) != symbols2[*next].end())
                                {
                                    auto p = pos;
                                    generate_token(symbols2[*next][*second], pos, pos + 2, { *next, *get() });
                                }
                                
                                else if (symbols1.find(*next) != symbols1.end())
                                {
                                    auto p = pos;
                                    generate_token(symbols1[*next], pos, pos + 1, { *next });
                                }
                            }   
                        }
                    }
                
                    std::atomic<bool> _end_flag{ false };
                    std::mutex _m;
                    std::shared_ptr<_lexer_node> _initial = nullptr;
                    semaphore _sem;
                    std::thread _thread;
                };                
            }

            class iterator
            {
            public:
                template<typename Iter, typename std::enable_if<std::is_same<typename std::iterator_traits<Iter>::value_type, char>::value, int>::type = 0>
                iterator(Iter begin, Iter end) : _backend{ std::make_shared<_detail::_iterator_backend>(begin, end, _node) }
                {
                }

                explicit operator bool() const
                {
                    return static_cast<bool>(_node);
                }

                iterator & operator++()
                {
                    if (_node)
                    {
                        if (!_node->_next)
                        {
                            _node->wait_next();
                        }
                        
                        _node = _node->_next;
                    }
                    
                    return *this;
                }

                iterator operator++(int)
                {
                    iterator iter{ *this };
                    ++*this;
                    return iter;
                };

                token & operator*()
                {
                    return _node->_token;
                }

                const token & operator*() const
                {
                    return _node->_token;
                }

            private:
                std::shared_ptr<_detail::_lexer_node> _node = nullptr;
                std::shared_ptr<_detail::_iterator_backend> _backend = nullptr;
            };
        }
    }
}

using reaver::vapor::lexer::token_types;
using reaver::vapor::lexer::token_type;

std::array<std::string, +token_type::count> reaver::vapor::lexer::token_types;

reaver::unit token_types_init = []() -> reaver::unit
{
    token_types[+token_type::identifier] = "identifier";
    token_types[+token_type::module] = "module";
    token_types[+token_type::import] = "import";
    token_types[+token_type::auto_] = "auto";
    token_types[+token_type::dot] = ".";
    token_types[+token_type::curly_bracket_open] = "{";
    token_types[+token_type::curly_bracket_close] = "}";
    token_types[+token_type::square_bracket_open] = "[";
    token_types[+token_type::square_bracket_close] = "]";
    token_types[+token_type::round_bracket_open] = "(";
    token_types[+token_type::round_bracket_close] = ")";
    token_types[+token_type::angle_bracket_open] = "<";
    token_types[+token_type::angle_bracket_close] = ">";
    token_types[+token_type::semicolon] = ";";
    token_types[+token_type::right_shift] = ">>";
    token_types[+token_type::left_shift] = "<<";
    token_types[+token_type::map] = "->>";
    
    token_types[+token_type::none] = "<EMPTY TOKEN>";
    
    return {};
}();

std::unordered_map<std::string, token_type> reaver::vapor::lexer::keywords = {
    { "module", token_type::module },
    { "import", token_type::import },
    { "auto", token_type::auto_ },
};

std::unordered_map<char, token_type> reaver::vapor::lexer::symbols1 = {
    { '{', token_type::curly_bracket_open },
    { '}', token_type::curly_bracket_close },
    { '[', token_type::square_bracket_open },
    { ']', token_type::square_bracket_close },
    { '(', token_type::round_bracket_open },
    { ')', token_type::round_bracket_close },
    { '<', token_type::angle_bracket_open },
    { '>', token_type::angle_bracket_close },
    { ';', token_type::semicolon },
};

std::unordered_map<char, std::unordered_map<char, token_type>> reaver::vapor::lexer::symbols2 = {
    { '<', { 
        { '<', token_type::left_shift } } 
    },
    
    { '>', { 
        { '>', token_type::right_shift } } 
    },
};

std::unordered_map<char, std::unordered_map<char, std::unordered_map<char, token_type>>> reaver::vapor::lexer::symbols3 = {
    { '-', { 
        { '>', { 
            { '>', token_type::map } 
        } } 
    } } 
};

int main()
{
    for (reaver::vapor::lexer::iterator it{ program.begin(), program.end() }; it; ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << std::endl;
}
