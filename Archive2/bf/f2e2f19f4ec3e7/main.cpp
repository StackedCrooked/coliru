#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>

struct ioes
{
    virtual ~ioes() = default ;
    virtual void on_data( int i ) = 0;
    virtual void from_oes( int i ) = 0;
};

std::mutex stdout_lock ;

struct cms
{
    explicit cms( ioes& oes_object ) : oes_object(oes_object) {}

    void send_data( int i )
    {
          sent_numbers.push_back(i);
          oes_object.on_data(i);
    }

    void recv_data( int i )
    {
        std::lock_guard<std::mutex> body_guard(lock) ;
        recd_numbers.push_back(i) ;
    }

    void print() const
    {
        std::cout << "sent data: " ;
        for( int v : sent_numbers ) std::cout << v << ' ' ;
        std::cout << '\n' ;

        std::cout << "recd data: " ;
        {
            std::lock_guard<std::mutex> body_guard(lock) ;
            for( int v : recd_numbers ) std::cout << v << ' ' ;
        }
        std::cout << '\n' ;
    }

    private:
        ioes& oes_object ;
        std::vector<int> sent_numbers ;
        std::vector<int> recd_numbers ;
        mutable std::mutex lock ;
};

struct oes : ioes
{
    void connect( cms* p ) { cms_object = p ; }

    void on_data( int i ) override
    {
         std::this_thread::sleep_for( std::chrono::milliseconds(100) );
         {
             std::lock_guard<std::mutex> body_guard(stdout_lock) ;
             std::cout << "oes::on_data(" << i << ")\n" << std::flush ;
         }

         from_oes( 1000 - i*i ) ;
    }

    void from_oes( int i ) override { if(cms_object) cms_object->recv_data(i) ; }

    private:
        cms* cms_object = nullptr ;
};

int main()
{
    oes oes_object ;
    cms cms_object(oes_object) ;
    auto pcms = std::addressof(cms_object) ;
    oes_object.connect(pcms) ;

    for( int i = 0 ; i < 10 ; ++i )
        std::thread( &cms::send_data, pcms, i + 10 ).detach() ;

    std::this_thread::sleep_for( std::chrono::seconds(3) );
    cms_object.print() ;
}
