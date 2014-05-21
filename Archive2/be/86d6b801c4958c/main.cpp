#include <string>
#include <iostream>

using namespace std;

class Assets
{
public:
  void editConsoleState(bool newstate)
  {
    isConsole = newstate;
  }

  bool consoleState()
  {
    bool state;
    state = isConsole;
    return state;
  }
private:
  bool isConsole;
};



class TextPlay {
public:
  TextPlay(Assets &_assets) : assets(_assets) {}

  void consoleRefresh()
  {
    cout << " -Input Command-" << endl;
    cout << "" << endl;
    cout << "> ";
  }

  void consoleIntro()
  {
    cout << "Welcome to the console!" << endl;
    cout << "" << endl;
    consoleRefresh();

  }

  void makeCommand()
  {
    cin >> command;

    if (command == "exit")
    {

      assets.editConsoleState(false);
    }
    else
    {
      cout << "" << endl;
      cout << " INVALID COMMAND" << endl;
      cout << "" << endl;
    }
  }
private:
  Assets &assets;
  std::string command;
};

Assets assets;
TextPlay textplay(assets);

///----------------\\\

int main() {
  assets.editConsoleState(true);

  ///----Console---\\\

  while (assets.consoleState() == true) {
    textplay.consoleRefresh();
    textplay.makeCommand();
  }
  ///--------------\\\

  return 0;
}