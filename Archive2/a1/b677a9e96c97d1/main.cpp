class ioes
{
public:
      virtual int on_data(int i) = 0;
      virtual void from_oes(int i) = 0;
};

#include <iostream>

class oes : public ioes
{
public:
      oes() {}
      int on_data(int i) override;
      void from_oes(int ) override { }
};

int oes::on_data(int i)
{
      std::cout << "from oes::on_data: " << (i + 100) << '\n' << std::flush;
      return i*i ;
}

class oms
{
public:
      oms() = delete;
      oms(ioes& param) : ioesobj(param) {}
      int send_data(int i);

private:
      ioes& ioesobj;
};

int oms::send_data(int i)
{
      return ioesobj.on_data(i);
}

#include <iostream>
#include <thread>
#include <future>
#include <functional>

void pt_ssleep(const int delay);

int main()
{
      std::cout << " --- start prototype --- " << std::endl;

      oes oesobj;
      oms omsobj(oesobj);

      for( int i = 0 ; i < 5 ; ++i )
      {
          std::cout << i << ". sending data aynchronously\n" << std::flush ;
          
          // http://en.cppreference.com/w/cpp/thread/async
          auto future = std::async( std::launch::async, &oms::send_data, std::addressof(omsobj), i+23 ) ;
          // omsobj.send_data(99);
          
          std::cout << "waiting for async operation to complete\n" << std::flush ;
          pt_ssleep(1);
          future.wait() ;
          
          // http://en.cppreference.com/w/cpp/thread/future/get
          std::cout << "done. result: " << future.get() << "\n.................\n" << std::flush ;
      }
      std::cout << " --- end prototype --- " << std::endl;
}

void pt_ssleep(const int delay)
{
      std::this_thread::sleep_for(std::chrono::seconds(delay));
}