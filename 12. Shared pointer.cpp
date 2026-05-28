/* Shared pointer represents shared ownership. Multiple smart pointers can point 
   to the exact same resource. It maintains an internal reference count(located 
   on the heap). Everytime, a shared pointer is copied, its reference count 
   increases by 1. When a shared pointer is destroyed, its reference count 
   decreases by 1. The actual resource is deleted only when the reference count
   exactly hits zero. At its core, it is a class template. When we write std::
   shared_ptr<int> or std::shared_ptr<CustomClassC>, we are passing a 
   type parameter T to a generic wrapper class.
   1. use_count(): track how many pointer share ownership of object.
   2. reset(): release or replace the ownership.
      e.g.-> shared_ptr<int> main_ptr = make_shared<int>(10); 
             main_ptr.reset(new int(20)); -> replacing the ownership
*/
#include<iostream>
#include<memory>
#include<string>
using namespace std;

class SharedResourceC{
  private:
    string m_id;
  public:
    SharedResourceC(const string& s):m_id(s){
        cout<<"[Resource] "<<m_id<<" created in heap memory.!!\n";
    }
    ~SharedResourceC(){
        cout<<"[Resource] "<<m_id<<" completely cleared from heap memory.!!\n";
    }
    void use(){
        cout<<"[Resource] "<<m_id<<" is being accessed.!!\n";
    }
};

void inspect_pointer(shared_ptr<SharedResourceC>& ptr, const string& scope_name){
    cout<<"["<<scope_name<<"] Reference Count: "<<ptr.use_count()<<endl;
}

int main()
{
 cout<<"--- 1. Initializing shared resource ---\n";
 shared_ptr<SharedResourceC> main_ptr = make_shared<SharedResourceC>("Global_Database_Config");
 inspect_pointer(main_ptr, "main - initial");
 cout<<"\n--- 2. Entering inner scopes, creating copies ---\n";
 {
  shared_ptr<SharedResourceC> local_scope_ptr1 = main_ptr;
  shared_ptr<SharedResourceC> local_scope_ptr2 = local_scope_ptr1;
  inspect_pointer(main_ptr, "Inner Scope Active");
  local_scope_ptr2->use();
 }
 cout<<"--- Left Inner Scope ---\n";
 inspect_pointer(main_ptr, "main - post inner scope");
 cout<<"\n--- 3. Resetting Main Pointer Explicitly ---\n";
 main_ptr.reset();
 cout<<"\n--- 4. End of main() ---\n";
 return 0;
}