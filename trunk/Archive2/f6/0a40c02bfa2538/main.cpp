struct Material // external interface
{
  void some_interface_function(){ _base->some_interface_function(); }

  struct MaterialBase{ virtual void some_interface_function(); };

  template<class T>
  struct ActualMaterial{
    T v;
    void some_interface_function(){ v.some_interface_function(); }
  };

  std::unique_ptr<MaterialBase> _base;
};