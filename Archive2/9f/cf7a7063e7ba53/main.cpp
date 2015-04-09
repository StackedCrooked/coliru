#include <iostream>

template<typename T>
class MonitorSwi
{
public:
   typedef void (T::*SwiHandlerFunc_t)();

   MonitorSwi(int id, T* pInstance, SwiHandlerFunc_t handler) :
      m_id(id),
      m_instance(pInstance),
      m_handler(handler)
   {
   }

   void HandleEvent()
   {
      std::cout << "MonitorSwi::HandleEvent() Handle SWI ID = " << m_id << std::endl;
      (m_instance->*m_handler)();
   }

private:
   int              m_id;
   T*               m_instance;
   SwiHandlerFunc_t m_handler;
};


class DeviceManager
{
public:
   DeviceManager() :
      m_Swi1(1, this, &DeviceManager::HandleSwi1Member), // Register handler for SWI 1 events
      m_Swi2(2, this, &DeviceManager::HandleSwi2Member)  // Register handler for SWI 2 events
   {
   }

   void HandleSwi1Member()
   {
      std::cout << "DeviceManager::HandleSwi1Member()" << std::endl;

      // Process event that SWI 1 has signalled...
   }

   void HandleSwi2Member()
   {
      std::cout << "DeviceManager::HandleSwi2Member()" << std::endl;

      // Process event that SWI 2 has signalled...
   }

   MonitorSwi<DeviceManager> m_Swi1;
   MonitorSwi<DeviceManager> m_Swi2;
};

int main()
{
   DeviceManager device;

   // Fake hardware calling SWI 1 (normally performed by hardware event handler)
   device.m_Swi1.HandleEvent();

   // Fake hardware calling SWI 2 (normally performed by hardware event handler)
   device.m_Swi2.HandleEvent();

   return 0;
}
