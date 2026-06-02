/* Optional, Any and Variant classes are type-safe wrapper classes explicitly introduced to replace 
   unsafe, legacy C-style patterns like returning magic dummy values, using raw void* pointers
   or deploying error-prone raw C unions. Unlike raw pointers or dynamic structures, they 
   manages their data on the stack (unless data type itself allocates heap memory), making
   them highly efficient and cache-friendly.
   std::optional manages a value that may or may not exist, commonly used as a function return
   type to represent a clean, type-safe fallback, completely eliminating the need to return
   magic error codes(like -1 or 0).
*/
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

using namespace std;

optional<string> fetch_user_email(int user_id){
    unordered_map<int, string> db = {{1, "john_doe@gmail.com"}, {2, "sam_winchester@gmail.com"}, 
                                     {3, "dean_winchester@gmail.com"}};
    auto it = db.find(user_id);
    if(it != db.end()){
        return it->second;
    }                     
    return nullopt;            
}

int main()
{
 int usrId1, usrId2 = 999;
 cout<<"Enter user_id: ";
 cin>>usrId1;
 auto email = fetch_user_email(usrId1);
 if(email){
    cout<<"Email found: "<<*email<<endl;
 }
 auto missing_email = fetch_user_email(usrId2);
 //If the return value from the optional is empty(or nullopt), string passed in value_or is printed
 string final_address = missing_email.value_or("unknown@domain.com");
 cout<<"Target email: "<<final_address<<endl;
 return 0;
}