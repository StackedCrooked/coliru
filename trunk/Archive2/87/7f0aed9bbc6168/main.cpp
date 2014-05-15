struct Material // external interface
{
  void some_interface_function(){ _base->some_interface_function(); }

  struct MaterialBase{ virtual void some_interface_function(); };

  template<class T>
  struct ActualMaterial{
    T v;
    void some_interface_function(){ v.some_interface_function(); }
  };

  template<class T>
  Material(T v)
    : _base(make_unique<ActualMaterial<T>>(v)) {}
    
  std::unique_ptr<MaterialBase> _base;
};

// and then `std::vector<Material>`