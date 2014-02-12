#pragma once
#include <vector>
#include 'IKontext.h'


class AsciiKontext : public IKontext
{
private:
    std::vector<std::string> matice;
    char znakPopredi = 'x';
    char znakPozadi = '-';
    int vyska;
    int sirka;

public:
    AsciiKontext(const int pocetRadku, const int pocetSloupcu);
    void NastavZnakPopredi(const char znak);
    void NastavZnakPozadi(const char znak);
    virtual int VratVysku() const final;
    virtual int VratSirku() const final;
    virtual void Zobraz() const final;
    virtual void Zapis(const int x, const int y) final;
    virtual void Vymaz() final;
};