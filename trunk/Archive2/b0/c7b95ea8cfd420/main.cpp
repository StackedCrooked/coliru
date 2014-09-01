1>------ Build started: Project: Test, Configuration: Debug Win32 ------
1>  main.cpp
1>c:\program files (x86)\microsoft visual studio 12.0\vc\include\xmemory0(600): error C2280: 'std::unique_ptr<test,std::default_delete<_Ty>>::unique_ptr(const std::unique_ptr<_Ty,std::default_delete<_Ty>> &)' : attempting to reference a deleted function
1>          with
1>          [
1>              _Ty=test
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\memory(1486) : see declaration of 'std::unique_ptr<test,std::default_delete<_Ty>>::unique_ptr'
1>          with
1>          [
1>              _Ty=test
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xmemory0(723) : see reference to function template instantiation 'void std::allocator<_Other>::construct<_Objty,const std::unique_ptr<test,std::default_delete<_Ty>>&>(_Objty *,const std::unique_ptr<_Ty,std::default_delete<_Ty>> &)' being compiled
1>          with
1>          [
1>              _Other=std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>
1>  ,            _Objty=std::unique_ptr<test,std::default_delete<test>>
1>  ,            _Ty=test
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xmemory0(723) : see reference to function template instantiation 'void std::allocator<_Other>::construct<_Objty,const std::unique_ptr<test,std::default_delete<_Ty>>&>(_Objty *,const std::unique_ptr<_Ty,std::default_delete<_Ty>> &)' being compiled
1>          with
1>          [
1>              _Other=std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>
1>  ,            _Objty=std::unique_ptr<test,std::default_delete<test>>
1>  ,            _Ty=test
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xmemory0(872) : see reference to function template instantiation 'void std::allocator_traits<_Alloc>::construct<_Ty,const std::unique_ptr<test,std::default_delete<test>>&>(std::allocator<_Other> &,_Objty *,const std::unique_ptr<test,std::default_delete<test>> &)' being compiled
1>          with
1>          [
1>              _Alloc=std::allocator<std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>>
1>  ,            _Ty=std::unique_ptr<test,std::default_delete<test>>
1>  ,            _Other=std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>
1>  ,            _Objty=std::unique_ptr<test,std::default_delete<test>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xmemory0(872) : see reference to function template instantiation 'void std::allocator_traits<_Alloc>::construct<_Ty,const std::unique_ptr<test,std::default_delete<test>>&>(std::allocator<_Other> &,_Objty *,const std::unique_ptr<test,std::default_delete<test>> &)' being compiled
1>          with
1>          [
1>              _Alloc=std::allocator<std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>>
1>  ,            _Ty=std::unique_ptr<test,std::default_delete<test>>
1>  ,            _Other=std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>
1>  ,            _Objty=std::unique_ptr<test,std::default_delete<test>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(835) : see reference to function template instantiation 'void std::_Wrap_alloc<std::allocator<_Other>>::construct<_Ty,const std::unique_ptr<test,std::default_delete<test>>&>(_Ty *,const std::unique_ptr<test,std::default_delete<test>> &)' being compiled
1>          with
1>          [
1>              _Other=std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>
1>  ,            _Ty=std::unique_ptr<test,std::default_delete<test>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(835) : see reference to function template instantiation 'void std::_Wrap_alloc<std::allocator<_Other>>::construct<_Ty,const std::unique_ptr<test,std::default_delete<test>>&>(_Ty *,const std::unique_ptr<test,std::default_delete<test>> &)' being compiled
1>          with
1>          [
1>              _Other=std::_List_node<std::unique_ptr<test,std::default_delete<test>>,void *>
1>  ,            _Ty=std::unique_ptr<test,std::default_delete<test>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(1062) : see reference to function template instantiation 'std::_List_node<std::unique_ptr<test,std::default_delete<_Ty>>,void *> *std::_List_buy<std::unique_ptr<_Ty,std::default_delete<_Ty>>,_Alloc>::_Buynode<const std::unique_ptr<_Ty,std::default_delete<_Ty>>&>(std::_List_node<std::unique_ptr<_Ty,std::default_delete<_Ty>>,void *> *,std::_List_node<std::unique_ptr<_Ty,std::default_delete<_Ty>>,void *> *,const std::unique_ptr<_Ty,std::default_delete<_Ty>> &)' being compiled
1>          with
1>          [
1>              _Ty=test
1>  ,            _Alloc=std::allocator<test_ptr>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(1062) : see reference to function template instantiation 'std::_List_node<std::unique_ptr<test,std::default_delete<_Ty>>,void *> *std::_List_buy<std::unique_ptr<_Ty,std::default_delete<_Ty>>,_Alloc>::_Buynode<const std::unique_ptr<_Ty,std::default_delete<_Ty>>&>(std::_List_node<std::unique_ptr<_Ty,std::default_delete<_Ty>>,void *> *,std::_List_node<std::unique_ptr<_Ty,std::default_delete<_Ty>>,void *> *,const std::unique_ptr<_Ty,std::default_delete<_Ty>> &)' being compiled
1>          with
1>          [
1>              _Ty=test
1>  ,            _Alloc=std::allocator<test_ptr>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(1424) : see reference to function template instantiation 'void std::list<test_ptr,std::allocator<_Ty>>::_Insert<const std::unique_ptr<test,std::default_delete<test>>&>(std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<_Ty>>,std::_Iterator_base0>,const std::unique_ptr<test,std::default_delete<test>> &)' being compiled
1>          with
1>          [
1>              _Ty=test_ptr
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(1424) : see reference to function template instantiation 'void std::list<test_ptr,std::allocator<_Ty>>::_Insert<const std::unique_ptr<test,std::default_delete<test>>&>(std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<_Ty>>,std::_Iterator_base0>,const std::unique_ptr<test,std::default_delete<test>> &)' being compiled
1>          with
1>          [
1>              _Ty=test_ptr
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(1384) : see reference to function template instantiation 'void std::list<test_ptr,std::allocator<_Ty>>::_Insert_range<_Iter>(std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<_Ty>>,std::_Iterator_base0>,_Iter,_Iter,std::forward_iterator_tag)' being compiled
1>          with
1>          [
1>              _Ty=test_ptr
1>  ,            _Iter=std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<test,std::default_delete<test>>>>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(1384) : see reference to function template instantiation 'void std::list<test_ptr,std::allocator<_Ty>>::_Insert_range<_Iter>(std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<_Ty>>,std::_Iterator_base0>,_Iter,_Iter,std::forward_iterator_tag)' being compiled
1>          with
1>          [
1>              _Ty=test_ptr
1>  ,            _Iter=std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<test,std::default_delete<test>>>>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(924) : see reference to function template instantiation 'std::_List_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<test,std::default_delete<_Ty>>>>> std::list<test_ptr,std::allocator<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>::insert<std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>>>(std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>>,_Iter,_Iter)' being compiled
1>          with
1>          [
1>              _Ty=test
1>  ,            _Iter=std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<test,std::default_delete<test>>>>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(924) : see reference to function template instantiation 'std::_List_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<test,std::default_delete<_Ty>>>>> std::list<test_ptr,std::allocator<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>::insert<std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>>>(std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<_Ty,std::default_delete<_Ty>>>>>,_Iter,_Iter)' being compiled
1>          with
1>          [
1>              _Ty=test
1>  ,            _Iter=std::_List_const_iterator<std::_List_val<std::_List_simple_types<std::unique_ptr<test,std::default_delete<test>>>>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\list(917) : while compiling class template member function 'std::list<test_ptr,std::allocator<_Ty>>::list(const std::list<_Ty,std::allocator<_Ty>> &)'
1>          with
1>          [
1>              _Ty=test_ptr
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xstring(1123) : see reference to function template instantiation 'std::list<test_ptr,std::allocator<_Ty>>::list(const std::list<_Ty,std::allocator<_Ty>> &)' being compiled
1>          with
1>          [
1>              _Ty=test_ptr
1>          ]
1>          c:\program files (x86)\microsoft visual c++ compiler nov 2013 ctp\include\utility(201) : see reference to class template instantiation 'std::list<test_ptr,std::allocator<_Ty>>' being compiled
1>          with
1>          [
1>              _Ty=test_ptr
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(498) : see reference to class template instantiation 'std::pair<const _Kty,_Ty>' being compiled
1>          with
1>          [
1>              _Kty=int
1>  ,            _Ty=std::list<test_ptr,std::allocator<test_ptr>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(589) : see reference to class template instantiation 'std::_Tree_node<std::pair<const _Kty,_Ty>,void *>' being compiled
1>          with
1>          [
1>              _Kty=int
1>  ,            _Ty=std::list<test_ptr,std::allocator<test_ptr>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(588) : while compiling class template member function 'std::_Tree_node<std::pair<const _Kty,_Ty>,void *> *&std::_Tree_val<std::_Tree_simple_types<std::pair<const _Kty,_Ty>>>::_Left(std::_Tree_node<std::pair<const _Kty,_Ty>,void *> *)'
1>          with
1>          [
1>              _Kty=int
1>  ,            _Ty=std::list<test_ptr,std::allocator<test_ptr>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(859) : see reference to function template instantiation 'std::_Tree_node<std::pair<const _Kty,_Ty>,void *> *&std::_Tree_val<std::_Tree_simple_types<std::pair<const _Kty,_Ty>>>::_Left(std::_Tree_node<std::pair<const _Kty,_Ty>,void *> *)' being compiled
1>          with
1>          [
1>              _Kty=int
1>  ,            _Ty=std::list<test_ptr,std::allocator<test_ptr>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(761) : see reference to class template instantiation 'std::_Tree_val<std::_Tree_simple_types<std::pair<const _Kty,_Ty>>>' being compiled
1>          with
1>          [
1>              _Kty=int
1>  ,            _Ty=std::list<test_ptr,std::allocator<test_ptr>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(879) : see reference to class template instantiation 'std::_Tree_alloc<false,std::_Tree_base_types<_Ty,_Alloc>>' being compiled
1>          with
1>          [
1>              _Ty=std::pair<const int,std::list<test_ptr,std::allocator<test_ptr>>>
1>  ,            _Alloc=std::allocator<std::pair<const int,std::list<test_ptr,std::allocator<test_ptr>>>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(991) : see reference to class template instantiation 'std::_Tree_buy<std::pair<const _Kty,_Ty>,std::allocator<std::pair<const _Kty,_Ty>>>' being compiled
1>          with
1>          [
1>              _Kty=int
1>  ,            _Ty=std::list<test_ptr,std::allocator<test_ptr>>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\xtree(1024) : see reference to class template instantiation 'std::_Tree_comp<false,_Traits>' being compiled
1>          with
1>          [
1>              _Traits=std::_Tmap_traits<int,std::list<test_ptr,std::allocator<test_ptr>>,std::less<int>,std::allocator<std::pair<const int,std::list<test_ptr,std::allocator<test_ptr>>>>,false>
1>          ]
1>          c:\program files (x86)\microsoft visual studio 12.0\vc\include\map(70) : see reference to class template instantiation 'std::_Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>' being compiled
1>          with
1>          [
1>              _Kty=int
1>  ,            _Ty=std::list<test_ptr,std::allocator<test_ptr>>
1>  ,            _Pr=std::less<int>
1>  ,            _Alloc=std::allocator<std::pair<const int,std::list<test_ptr,std::allocator<test_ptr>>>>
1>          ]
1>          c:\code\test\test\main.cpp(19) : see reference to class template instantiation 'std::map<int,std::list<test_ptr,std::allocator<_Ty>>,std::less<_Kty>,std::allocator<std::pair<const _Kty,std::list<_Ty,std::allocator<_Ty>>>>>' being compiled
1>          with
1>          [
1>              _Ty=test_ptr
1>  ,            _Kty=int
1>          ]
========== Build: 0 succeeded, 1 failed, 0 up-to-date, 0 skipped ==========
