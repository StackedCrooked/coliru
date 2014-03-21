typedef int SOCKET;
typedef int THREADID;

int recv(SOCKET, char*, int, int);

template <typename F> struct wrapper;


template <typename R, typename T1, typename T2, typename T3, typename T4>
struct wrapper<R(T1,T2,T3,T4)> 
{
  typedef R result_type;
  typedef R (type)(T1,T2,T3,T4,THREADID);
};

int main()
{
    typedef int recv_t(SOCKET,char*,int,int);
    typedef wrapper<recv_t>::type recv_wrapper_t_1;    
      
    typedef decltype(recv) recv_t;
    typedef wrapper<recv_t>::type recv_wrapper_t_2;
}