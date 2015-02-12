#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

class Market1 {
  public:
  Market1() {};
  void MarketCreateOrder(int arg1, int& arg2) {
    arg2 = 20;
    std::cout << "Market1::MarketCreateOrder " << arg2 << std::endl;
  }
};

class Market2 {
  public:
  Market2() {};
  void MarketCreateOrder(int arg1, int& arg2) {
    std::cout << "Market2::MarketCreateOrder " << arg2 << std::endl;
  }
};

class MultiMarket {
  private:
  int market;
  Market1 *m1;
  Market2 *m2;

  public:
  MultiMarket(int m) {
    market = m;
    switch (market) {
      case 1:
        m1 = new Market1();
        break;
      case 2:
        m2 = new Market2();
        break;
      default:
        break;
    }
  }

  struct MarketCreateOrderDispatcher
  {
    template <typename MktConn, typename ... ArgT>
    void operator() (MktConn& mkt, ArgT&&... args) const {
      mkt.MarketCreateOrder(std::forward<ArgT>(args)...);
    }
  };

  void MarketCreateOrder(int arg1, int& arg2) {
    SwitchMarket(MarketCreateOrderDispatcher(), arg1, arg2);
  }

  template <typename Dispatcher, typename ... ArgT>
  void SwitchMarket(Dispatcher dispatch, ArgT&&... args) {
    switch(market) {
      case 1:
        dispatch(*m1, std::forward<ArgT>(args)...);
        break;
      case 2:
        dispatch(*m2, std::forward<ArgT>(args)...);
        break;
      default:
        break;
    }
  }
};

int main () {
  int j = 10;
  MultiMarket market(1);
  market.MarketCreateOrder(1, j);

  std::cout << j << std::endl;
}
