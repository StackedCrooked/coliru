#include <iostream>

class delim_stream {
  private:
  struct indirection {
    delim_stream const& _ref;

    operator delim_stream const& () {
      _ref._stream << _ref._delim; return _ref;
    }   
  };  

  public:
    delim_stream (std::ostream& s, std::string delim)
      : _stream {s} 
      , _delim  {delim}
    { } 

    template<class T>
    friend indirection operator<< (delim_stream const& ds, T&& data) {
      ds._stream << std::forward<T> (data);
      return { ds };
    }   

  private:
    std::ostream& _stream;
    std::string   _delim;
};

int main () {
  delim_stream (std::cout, ", ") << 1 << "hello" << 3.14f;
}