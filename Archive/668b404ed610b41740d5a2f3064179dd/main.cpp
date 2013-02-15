#include <memory>
#include <vector>

class __declspec(dllexport) VertexBuffer {
    
};

class __declspec(dllexport) GraphicsDevice {
private:
    std::vector<std::unique_ptr<VertexBuffer>> myvertexbuffers; 

};

/* Produces:

warning C4251: 'GraphicsDevice::myvertexbuffers' : class 'std::vector<std::unique_ptr<VertexBuffer,std::default_delete<_Ty>>,std::allocator<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>' needs to have dll-interface to be used by clients of class 'GraphicsDevice'
1>          with
1>          [
1>              _Ty=VertexBuffer
1>          ]

*/

/* To export, you'd need to do the following: */

template class __declspec(dllexport) std::unique_ptr<VertexBuffer>;
template class __declspec(dllexport) std::vector<std::unique_ptr<VertexBuffer>>;

/* But this doesn't work, because in instantiant the class for use, 
std::unique_ptr will complain about operator= being used with std::unique_ptr, as it does not allow that operation
*/