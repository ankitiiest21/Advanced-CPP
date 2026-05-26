/* Functor(function object) is an object which can be treated as if it were a function.
   Achieved by overloading the function call operator () within a class or a struct.
   Advantages over a regular function:
   1. A regular function loses its local variable after it returns but functors being
      a class instance can store data in its member variables across multiple calls.
   2. Functors are fast as whenever we pass a standard function pointer to an algorithm 
      like for_each, the compiler usually invokes it via a pointer dereference at runtime. 
      The compiler knows the exact type at compile-time. This allows it to completely 
      inline the function call, stripping away the function-call overhead entirely.
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Accumulator{
  private:
    int sum = 0;
  public:
    //Every time this is called, it updates its internal state 
    void operator()(int x){
        sum += x;
    }
    int getSum(){
        return sum;
    } 
};

int main()
{
 int n;
 cin>>n;
 vector<int> v(n);
 for(int i=0;i<n;i++){
    cin>>v[i];
 }
 Accumulator ac;
 ac = for_each(v.begin(), v.end(), ac);
 cout<<"Total Sum: "<<ac.getSum()<<endl;
 return 0;
}