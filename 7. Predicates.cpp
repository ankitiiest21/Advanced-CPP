/* Algorithm predicate is a callable entity(function,functor or a lambda expression)
   that returns a boolean value based on the arguments passed to it.
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main()
{
 vector<int> v={9, 5, 1, 4, 2, 17};
 //Unary Predicate: takes an argument, returns true if it is even
 auto isEven = [](int x){
   return x%2==0;
 };
 auto it = find_if(v.begin(), v.end(), isEven);
 if(it != v.end()){
    cout<<"First even number: "<<*it<<endl;
 }

 //Binary Predicate: takes two arguments, compares two items to sort in descending order
 auto descending = [](int a,int b){
   return a>b;
 };
 //can also use sort(v.begin(), v.end(), greater<int>()) for below code
 sort(v.begin(), v.end(), descending);
 cout<<"Vector(after sorting): ";
 for(const auto& it: v){
    cout<<it<<" ";
 }
 cout<<endl;
 return 0;
}