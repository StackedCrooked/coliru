// code inserted to fix compiler errors:
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

class Economy {};

void writeToLog(char const* ) { }
// end code inserted to fix compiler errors:

class Aapl: public Economy
{
public:
    Aapl(); //Constructor. Creats a semi-random starting value for stockPriceAAPL
    ~Aapl(){};
    int stockPriceAAPL;//Price of AAPL
    void changeStockPrice(); //Changes the stock prices for the tickers
    int pastAaplPrice; //The past prices are used to calculate change in the stock market.
};

class Avcal: public Aapl
{
public:
    void changeStockPrice(); // Calculates change in the stock market
};

Aapl::Aapl()
{
    stockPriceAAPL = rand() % 40 + 40; //Generates random starting stock
    writeToLog("Creating AAPL stock");
}


void Avcal::changeStockPrice()
{
    int changeAAPL;
    writeToLog("Calculating AVCAL");
    changeAAPL = stockPriceAAPL - pastAaplPrice;
    writeToLog("Outputting Stock Market");
    cout << "AAPL(" << changeAAPL << ") %" << (changeAAPL/pastAaplPrice)*100 << endl << endl;
}

int main() {
//gathering together the calls you mentioned:
  Aapl Aapl;
  Avcal Avcal;
  Avcal.changeStockPrice();
}