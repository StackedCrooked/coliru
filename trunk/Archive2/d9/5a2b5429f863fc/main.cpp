#include<memory>
using namespace std;
class IFace{};
class Face : /*private*/ IFace{};

int main() {
    shared_ptr<Face> s_face = make_shared<Face>();
    shared_ptr<IFace> s_iface = s_face; //works
    
    Face* p_face = new Face();
    IFace* p_iface = p_face; //compiler complains (righteously) 
                             //about the base class being inaccessible
}