#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>

using namespace std;

enum ContentType{TEXTURE,MODEL,AUDIO};




class CModel
{
    public:
    ~CModel();
    CModel();
    void Load(string filePath){};
    void Draw(){};
    private:
    
};
vector<CModel*> Model;

class Core
{
    public:  
    ~Core(){};
     Core(){}; 
    // it can be texture,model,audio
   
   int TextureId=0,ModelId=0;
    bool LoadContent(string filePath,ContentType Type)
    {
 
     
        switch(Type)
        {
            case 0:
            {   
                TextureId++;
                cout<<"Texture Loading:"<<TextureId<<endl;               
                
            }break;
            case 1:
            {
                ModelId++;
                cout<<"Model Loading:"<<ModelId<<endl;
                // MODEL LOAD
                CModel *Car;
                Car->Load(filePath.c_str());
                Model.push_back(Car);
            }break;
            case 2:
            {
                cout<<"AUDIO Loading"<<endl;
                // AUDIO LOAD
            }break;
        };
     
        return true;
    };
    void Render()
    {
       for(auto &M : Model) 
       {
        M->Draw("YOU");
       }
    }
        
    private:    
    int CanYou;
};
int main()
{  
    Core Base;    
    Base.LoadContent("HeightMap",ContentType::TEXTURE);
    Base.LoadContent("Plane.x"  ,ContentType::MODEL); 
    Base.LoadContent("Truck.x"  ,ContentType::AUDIO);
    Base.LoadContent("Train.x"  ,ContentType::MODEL);
    
    

    
        
    int ModelCount  =Base.ModelId;
    int TextureCount=Base.TextureId;
    
    cout<<ModelCount<<endl;
    cout<<TextureCount<<endl;
    
}