/* Jump tables is a compiler optimization technique to implement multi way branching
   (like switch statements). Instead of executing a long chain of slow conditional
   jumps(if-else-if), compiler creates an array of memory addresses pointing directly
   to the target code blocks. The code then "jumps" directly to the correct address 
   using index lookup in O(1) time.
*/

#include<iostream>
#include<array>
#include<vector>

using namespace std;

int main()
{
 int n;
 /*Creating a clean array of function pointers
   Since our lambdas capture nothing [], they automatically turn into raw function pointers.
 */
 array<void(*)(), 3> jump_table = {
   []() { cout<<"Task 0: Initializing system...\n";},
   []() { cout<<"Task 1: Processing data structures...\n";},
   []() { cout<<"Task 2: Cleaning up memory...\n";}
 };
 cout<<"Enter number of input codes: ";
 cin>>n;
 cout<<"Enter input codes: ";
 vector<int> input_commands(n,0);
 for(int i=0;i<n;++i){
    cin>>input_commands[i];
 }
 for(int i=0;i<n;++i){
    size_t cmd=input_commands[i];
    if(cmd<jump_table.size()){
        jump_table[cmd]();
    }
    else{
        cout<<"Invalid command code: "<<cmd<<endl;
    }
 }
 return 0;
}