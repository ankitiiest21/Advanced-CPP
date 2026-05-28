/* Unique pointers represents exclusive ownership. It cannot be copied, 
   only moved. At its core, it is a class template. When we write std::
   unique_ptr<int> or std::unique_ptr<CustomClassC>, we are passing a 
   type parameter T to a generic wrapper class. It uniquely owns the 
   resource it points to. Copying a std::unique_ptr<> is strictly
   forbidden, its copy constructor and copy assignment operator are
   explicitly = delete d.
*/
#include<iostream>
#include<memory>
#include<string>

using namespace std;

class HardwareDeviceC{
    private:
      string m_data;
    public:
      HardwareDeviceC(const string& s):m_data(s){
        cout<<"[Device] "<<m_data<<" initialized and powered on!!\n";
      }
      ~HardwareDeviceC(){
        cout<<"[Device] "<<m_data<<" safely powered down and deallocated!!\n";
      }
      void run_diagnostics(){
        cout<<"[Device] "<<m_data<<" is running acive simulations!!\n";
      }
};

//A function taking exclusive ownership of a device
void upgrade_firmware(unique_ptr<HardwareDeviceC> device){
    cout<<">> Firmware upgrade routine started!!\n";
    device->run_diagnostics();
    cout<<">> Firmware upgrade routine finished!!\n";
} //'device' goes out of scope here and is automatically destroyed

int main()
{ 
  cout<<"----- Creating a unique ptr -----\n";
  unique_ptr<HardwareDeviceC> dev_ptr = make_unique<HardwareDeviceC>("Core_ALU_01");
  dev_ptr->run_diagnostics();
  cout<<"\n----- Transferring ownership via move semantics -----\n";
  upgrade_firmware(move(dev_ptr));
  cout<<"\n----- Checking original pointer status -----\n";
  if(dev_ptr == NULL){
    cout<<"dev_ptr is now null, it no longer owns any resource.\n";
  }
  return 0;
}