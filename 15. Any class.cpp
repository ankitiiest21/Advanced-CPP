/* Any is a true polymorphic container that can store a value of any type whatsoever. 
   It is completely type-safe, modernized version of a legacy void* pointer. Unlike
   std::variant, we don't need to declare a list of allowed data types in advance.
   To get the data back out, we must explicitly perform std::any_cast. 
*/
#include <iostream>
#include <any>
#include <string>
#include <unordered_map>

using namespace std;

class UserPreferenceManagerC{
  private:
    unordered_map<string, any> m_settings;
  public:
    void set_preference(const string& key, any value){
        m_settings[key] = value;
    }
    template <typename T>
    T get_preference(const string& key, T default_value){
        auto it = m_settings.find(key);
        if( it == m_settings.end()){
            return default_value;
        }
        try{
            return std::any_cast<T>(it->second);
        }
        catch(const bad_any_cast&){
            cerr<<"[WARNING] Mis-matched type cast requested for setting: "<<key<<endl;
            return default_value;
        }
    }
};

int main()
{
 UserPreferenceManagerC app_settings;
 app_settings.set_preference("dark_mode", true);
 app_settings.set_preference("font_size", 14);
 app_settings.set_preference("ui_theme", string("Cyberpunk"));
 cout<<" --- Loading Dashboard Configurations ---\n";
 bool mode = app_settings.get_preference<bool>("dark_mode", false);
 int size = app_settings.get_preference<int>("font_size", 12);
 string theme = app_settings.get_preference<string>("ui_theme", "Default");

 cout<<"Dark Mode Active: "<<mode<<endl;
 cout<<"Render Font Size: "<<size<<endl;
 cout<<"Active UI Theme: "<<theme<<endl;

 int broken_cast = app_settings.get_preference<int>("ui_theme", 999);
 cout<<"Fallback value triggered an error: "<<broken_cast<<endl;
 return 0;
}