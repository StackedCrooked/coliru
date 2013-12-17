#include <unordered_map>
#include <vector>
#include <memory>

#include <iostream>
int main()
{
    std::unordered_map<int, std::vector<std::unique_ptr<int>>> thing_ptrs;
}

//WHYYY MSVC ;_;

//D:\Apps\Visual Studio 12.0\VC\include\xmemory0(593): error C2280: 'std::unique_ptr<int,std::default_delete<_Ty>>::unique_ptr(const std::unique_ptr<_Ty,std::default_delete<_Ty>> &)' : attempting to reference a deleted function
//1>          with
//1>          [
//1>              _Ty=int
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\memory(1486) : see declaration of 'std::unique_ptr<int,std::default_delete<_Ty>>::unique_ptr'
//1>          with
//1>          [
//1>              _Ty=int
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\xmemory0(592) : while compiling class template member function 'void std::allocator<_Ty>::construct(_Ty *,const _Ty &)'
//1>          with
//1>          [
//1>              _Ty=std::unique_ptr<int,std::default_delete<int>>
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\xmemory0(723) : see reference to function template instantiation 'void std::allocator<_Ty>::construct(_Ty *,const _Ty &)' being compiled
//1>          with
//1>          [
//1>              _Ty=std::unique_ptr<int,std::default_delete<int>>
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\type_traits(572) : see reference to class template instantiation 'std::allocator<_Ty>' being compiled
//1>          with
//1>          [
//1>              _Ty=std::unique_ptr<int,std::default_delete<int>>
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\vector(650) : see reference to class template instantiation 'std::is_empty<_Alloc>' being compiled
//1>          with
//1>          [
//1>              _Alloc=std::allocator<std::unique_ptr<int,std::default_delete<int>>>
//1>          ]
//1>          C:\Program Files (x86)\Microsoft Visual C++ Compiler Nov 2013 CTP\include\utility(201) : see reference to class template instantiation 'std::vector<std::unique_ptr<int,std::default_delete<_Ty>>,std::allocator<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>' being compiled
//1>          with
//1>          [
//1>              _Ty=int
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\vector(1567) : see reference to class template instantiation 'std::pair<const _Kty,_Ty>' being compiled
//1>          with
//1>          [
//1>              _Kty=int
//1>  ,            _Ty=std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\vector(1565) : while compiling class template member function 'void std::vector<std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const _Kty,_Ty>>>>,std::_Wrap_alloc<std::allocator<_Other>>>::_Destroy(std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const _Kty,_Ty>>>> ,std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const _Kty,_Ty>>>> )'
//1>          with
//1>          [
//1>              _Kty=int
//1>  ,            _Ty=std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>
//1>  ,            _Other=std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const int,std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>>>>>
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\vector(1626) : see reference to function template instantiation 'void std::vector<std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const _Kty,_Ty>>>>,std::_Wrap_alloc<std::allocator<_Other>>>::_Destroy(std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const _Kty,_Ty>>>> ,std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const _Kty,_Ty>>>> )' being compiled
//1>          with
//1>          [
//1>              _Kty=int
//1>  ,            _Ty=std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>
//1>  ,            _Other=std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const int,std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>>>>>
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\xhash(1042) : see reference to class template instantiation 'std::vector<std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const _Kty,_Ty>>>>,std::_Wrap_alloc<std::allocator<_Other>>>' being compiled
//1>          with
//1>          [
//1>              _Kty=int
//1>  ,            _Ty=std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>
//1>  ,            _Other=std::_List_unchecked_iterator<std::_List_val<std::_List_simple_types<std::pair<const int,std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>>>>>
//1>          ]
//1>          D:\Apps\Visual Studio 12.0\VC\include\unordered_map(81) : see reference to class template instantiation 'std::_Hash<std::_Umap_traits<_Kty,_Ty,std::_Uhash_compare<_Kty,_Hasher,_Keyeq>,_Alloc,false>>' being compiled
//1>          with
//1>          [
//1>              _Kty=int
//1>  ,            _Ty=std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>
//1>  ,            _Hasher=std::hash<int>
//1>  ,            _Keyeq=std::equal_to<int>
//1>  ,            _Alloc=std::allocator<std::pair<const int,std::vector<std::unique_ptr<int,std::default_delete<int>>,std::allocator<std::unique_ptr<int,std::default_delete<int>>>>>>
//1>          ]
//1>          main.cpp(8) : see reference to class template instantiation 'std::unordered_map<int,std::vector<std::unique_ptr<int,std::default_delete<_Ty>>,std::allocator<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>,std::hash<int>,std::equal_to<_Ty>,std::allocator<std::pair<const _Kty,std::vector<std::unique_ptr<_Ty,std::default_delete<_Ty>>,std::allocator<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>>>>' being compiled
//1>          with
//1>          [
//1>              _Ty=int
//1>  ,            _Kty=int
//1>          ]