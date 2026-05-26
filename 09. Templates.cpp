/* A Class Template allows us to create a blueprint for a generic class where the 
   data types of its member variables and function parameters aren't fixed. 
   The compiler instantiates a concrete class type in memory only when we 
   explicitly specify the data types during object creation. Unlike 
   regular classes, we cannot easily split template class declarations into 
   a .h file and their implementations into a separate .cpp file. Because 
   the compiler needs to see the full implementation to generate the concrete 
   classes at compile-time, the entire template definition must live inside the header file.
*/

#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

/* StaticBuffer by itself is not a class—it is a code generator.
   When the compiler reads StaticBuffer<int, 3>, it stops and generates a unique 
   class type in the background that looks like this:

   class StaticBuffer_int_3 {
    int m_data[3];
    void set(std::size_t index, const int& value);
    // ...
   };
   When it hits StaticBuffer<std::string, 4>, it generates an entirely
   distinct class binary layout replacing T with std::string and Size with 4.
*/

template <typename T, size_t Size>
class StaticBuffer{
  private:
     T m_data[Size];
  public:
     void set(size_t index, const T& value){
        if(index >= Size){
          throw out_of_range("Buffer index out of range!");
        }
        m_data[index] = value;
     }
     const T& get(size_t index){
        if(index >= Size){
          throw out_of_range("Buffer index out of range!");  
        }
        return m_data[index];
     }
     size_t capacity() const{
        return Size;
     }
};

int main()
{
  StaticBuffer<int, 3> intBuffer;
  intBuffer.set(0, 1);
  intBuffer.set(1, 2);
  intBuffer.set(2, 3);
  cout<<"intBuffer capacity: "<<intBuffer.capacity()<<endl;
  cout<<"intBuffer elements: ";
  for(size_t i=0;i<intBuffer.capacity();++i){
    cout<<intBuffer.get(i)<<" ";
  }
  cout<<endl;
  StaticBuffer<string, 4> strBuffer;
  strBuffer.set(0, "one");
  strBuffer.set(1, "two");
  strBuffer.set(2, "three");
  strBuffer.set(3, "four");
  cout<<"strBuffer capacity: "<<strBuffer.capacity()<<endl;
  cout<<"strBuffer elements: ";
  for(size_t i=0;i<strBuffer.capacity();++i){
    cout<<strBuffer.get(i)<<" ";
  }
  return 0;
}