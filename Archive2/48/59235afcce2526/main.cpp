#include <iostream>

class IRenderWindow
{
    
};

typedef IRenderWindow* RenderWindowPtr;

class CRenderWindow : public IRenderWindow
{
public:

static CRenderWindow& GetInstance() { return ms_instance; }
  private:
    CRenderWindow() { }
    ~CRenderWindow() { }
    static CRenderWindow ms_instance;  
};

#define RenderWindow CRenderWindow::GetInstance()

CRenderWindow CRenderWindow::ms_instance;

class Device
{
  public:
  
    RenderWindowPtr GetRenderWindow()
    {
        return static_cast<RenderWindowPtr>(&RenderWindow);
    }
    
};

int main()
{ 
    return 0;
}