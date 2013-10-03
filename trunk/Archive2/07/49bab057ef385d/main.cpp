#include <list>
#include <utility>
#include <string>


using namespace std;
typedef list<pair<string, string> > KeyVal;
struct Header { string name; string value; };
struct Param { string name; string value; };

/* Something that contains headers */
template<typename T> class WithHeaders {
  KeyVal headers;
public:
  virtual T &operator <<(const Header &h) {
    headers.push_back(pair<string, string>(h.name, h.value));
    return static_cast<T&> (*this);
  }
};

/* Something that contains query params */
template<class T> class WithQuery {
    KeyVal query_params;

public:
    virtual T &operator <<(Param const&q) {
      query_params.push_back(pair<string, string>(q.name, q.value));
      return static_cast<T&> (*this);
    }

    const KeyVal &get_query() const {return query_params;}
};

/* Http Request has both headers and query parameters */
class HttpRequest: public WithQuery<HttpRequest>, public WithHeaders<HttpRequest> {};

int
main (int argc, char *argv[])
{
  HttpRequest request;

  request << Header {"foo","bar"} << Param{"page", "1"};
}