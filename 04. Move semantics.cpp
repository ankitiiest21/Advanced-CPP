/*
Move semantics relies on differentiating between two types of expressions:
1. Lvalue: An object that has a identifiable location in memory (it has a name, 
   and we can take its address). Ex: int x = 5; (x is an lvalue).
2. Rvalue: A temporary value that does not have a persistent memory location (it has no name, 
   and we cannot take its address). Ex: The literal 5, or the temporary object returned by 
   a function like createBigData().
 C++11 introduces Rvalue References using a double ampersand (&&). An rvalue reference can 
 bind directly to temporary objects, signaling to the compiler that the object's resources 
 can be safely harvested.
*/

#include <iostream>
#include <algorithm>

using namespace std;

class BigDataC
{
public:
    int *data;
    size_t size;
    BigDataC(size_t s) : size(s)
    {
        this->data = new int[this->size];
    }
    ~BigDataC()
    {
        if (data)
        {
            delete[] data;
        }
    }
    // Move constructor
    BigDataC(BigDataC &&other) noexcept : data(other.data), size(other.size)
    {
        other.data = NULL;
        other.size = 0;
        cout << "Moving Resources!!!\n";
    }
    // Move Assignment operator
    BigDataC &operator=(BigDataC &&other) noexcept
    {
        if (this != &other)
        {
            if (this->data)
            {
                delete[] this->data;
            }
            this->data = other.data;
            this->size = other.size;
            other.data = NULL;
            other.size = 0;
        }
        cout << "Move Assignment!!!\n";
        return *this;
    }
};

BigDataC createBigData(){
    BigDataC temp(1000000);
    return temp;
}

int main()
{
 /*When createBigData() returns,the compiler detects that it's returning a temporary object(an rvalue) and 
   calls the Move Constructor.
   Cost of a Copy: Allocating space for 1 million integers + copying 1 million elements.
   Cost of a Move: Copying a single 64-bit pointer address and an integer size variable. It's 
   essentially instantaneous.
 */
 BigDataC my_data = createBigData();
 return 0;
}