/* Lambdas are anonymous function which can be defined inline wherever we need it.
   Under the hood, the compiler transforms a lambda into an anonymous functor 
   (a class overloading operator()), but the syntax makes your code much cleaner and more readable.
   Lambda function declaration: 
   [capture_list] (parameter_list) mutable exception_specification -> return_type {
    // Function body
   };
   capture_list: comma separated variable names which will be accessed in function body
   parameter_list: comma separated variable name which will be arguments
   mutable: By default, captured variables are treated as const inside lambda body, mutable 
            strips this restriction.
   exception_specification: can be noexcept which tells compiler that lambda expression will
                            not throw any exceptions, unlocking aggressive compiler optimizations.
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
 int n, threshold, count = 0, x = 5, a = 2;
 cin>>n;
 vector<int> v(n);
 for(int i=0;i<n;i++){
    cin>>v[i];
 }
 cin>>threshold;

 for_each(v.begin(), v.end(), [threshold, &count](int x){
    if(x > threshold){
       count++;
    }
 });
 cout<<"Number of elements greater than threshold: "<<threshold<<" is "<<count<<endl;

 auto cache_modifier = [x]() mutable {
   x += 5;  // Valid because of 'mutable'. Does NOT alter the original x outside.
   cout<<"Inside cache_modifier, value of x: "<<x<<endl;
 }; 
 cache_modifier();
 cout<<"Outside cache_modifier, value of x: "<<x<<endl;

 auto safe_lambda = [](int a) noexcept {
    return a*2;
 };
 int p = safe_lambda(a);
 cout<<"p: "<<p<<endl;
 return 0;
}