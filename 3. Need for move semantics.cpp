#include <iostream>
#include <algorithm>

using namespace std;

class BigDataC{
  public:
    int*data;
    size_t size;
  BigDataC(size_t s):size(s){
    data=new int[this->size];
  }
  //Declared copy constructor illustrating Deep Copy
  BigDataC(const BigDataC& other):size(other.size){
    this->data = new int[this->size];
    cout<<"Deep copying!!!";
    for(size_t i=0;i<other.size;++i){
        this->data[i] = other.data[i];
    }
  }
  ~BigDataC(){
    if(data){
        delete []data;
    }
  }
};

BigDataC createBigData(){
    BigDataC temp(1000000);
    return temp;
}

int main(){
    /*Whenever we call createBigData():
    1. temp is created inside the function.
    2. When returning, temp is copied into my_data using the copy constructor. This triggers a 
       deep copy, allocating memory for another 1 million integers and copying them one by one.
    3. temp is immediately destroyed, freeing its memory.
    This deep copy is completely wasteful because temp was about to die anyway. It would be 
    much faster to just hand over temp's memory pointer directly to my_data. That is exactly
    what move semantics does.*/
    BigDataC my_data = createBigData();
    return 0;
}