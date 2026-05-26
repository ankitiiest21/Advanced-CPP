/* If we pass an incompatible data type into a template, the compiler wouldn't notice 
   until it was deep inside the template's implementation code, resulting in massive 
   unreadable errors. Constraints and Concepts allow us to define a compile-time 
   interface(a contract) that a datatype must satisfy befire it is allowed in our
   template.
   1. Constraint: a specific condition or logical expression that evaluates to true or
   false at compile-time.
   2. Concept: a named collection of one or more constraints. It is a reusable compile-
   time predicate that defines a specific category of types.(e.g. an Iterable type).
   Concepts are defined using the template syntax, the concept keyword, and a requires 
   expression. A requires expression can evaluate four distinct types of constraints:
   template <typename T>
   concept AdvancedContainer = requires(T container) {
    // 1. Simple Constraint: This exact syntax must compile
    container.clear(); 
    // 2. Type Constraint: This nested type must exist inside the class
    typename T::value_type; 
    // 3. Compound Constraint: This expression must compile AND return a specific type
    { container.size() } -> std::same_as<std::size_t>; 
    // 4. Nested Constraint: An additional evaluation condition that must hold true
    requires sizeof(T) > 8; 
};
*/

#include<iostream>
#include<concepts>

using namespace std;

template <typename T>
concept Serializable = requires(T entity){
  { entity.to_string() } -> same_as<string>;
};

template <typename T>
requires Serializable<T> && is_trivially_copyable_v<T>
class DataPacketC{
  private:
    T m_payload;
  public:
    DataPacketC(T payload): m_payload(payload) {}

    void dispatch(){
      cout<<"Dispatching packet payload: "<<m_payload.to_string()<<endl;
    }
};

struct SensorReading{
  int device_id;
  double volt;
  string to_string() const{
    return "Device " + std::to_string(device_id)+" (Volt: " + std::to_string(volt) + ")";
  }
};

struct ComplexStringPayload{
  string data;
  string to_string() const{
    return data;
  }
};


int main()
{
 SensorReading reading{1, 1.417};
 DataPacketC<SensorReading> safe_packet(reading);
 safe_packet.dispatch();

 ComplexStringPayload heavy_payload{"System Error Log Trace"};
 /*DataPacketC<ComplexStringPayload> broken_packet(heavy_payload);
 broken_packet.dispatch();*/

 return 0;
}