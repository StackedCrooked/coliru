#include <iostream>
#include <string>
#include <vector>

struct Telewizor
{
    std::string nazwa;
    int cena;
    int przekatna;
};

void pokaz(const std::vector<Telewizor>& telewizory)
{
    std::cout << "ilosc telewizorow: " << telewizory.size() << ", oto one:\n";
    for (auto& t : telewizory)
        std::cout << t.nazwa << " w cenie " << t.cena << '\n';
}

int main()
{
    std::vector<Telewizor> telewizory;
    telewizory.push_back({"SONY", 10000, 40});
    telewizory.push_back({"Samsung", 999, 30});
    telewizory.push_back({"Samsung", 2999, 50});
    pokaz(telewizory);
    telewizory[0].cena -= 2000; //promocja!!!
}
