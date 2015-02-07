#include <functional>
#include <vector>
using namespace std;

struct Button
{
  function<void()> OnClick;
};

int main()
{
  vector<Button> buttons = 
  {
      {[] { printf("Button1::OnClick()\n"); }},
      {[] { printf("Button2::OnClick()\n"); }},
      {[] { printf("Button3::OnClick()\n"); }},
  };
  
  for(auto& button : buttons)
    button.OnClick();
}


