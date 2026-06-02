/* Variant represents a type-safe companion to a C-style union. It holds exactly one value
   at a time, but that value can belong to any of the distinct types specified in its 
   template list. As it tracks which type it is currently holding, it is impossible to 
   read the wrong type accidentally. 
*/
#include <iostream>
#include <variant>
#include <string>
#include <vector>

using namespace std;

struct CreditCardS{
  string m_card_number;
  string m_expiry;
};

struct PayPalS{
  string m_email_address;
};

struct CryptoWalletS{
  string m_wallet_address;
  string m_token_type;
};

using PaymentMethod = variant<CreditCardS, PayPalS, CryptoWalletS>;

/* To read data from std::variant, we have to pass a formal class object(functor) to std::visit
   that has multiple overloaded versions of operator(). Writing an entire custom class just to read
   a variant is tedious and introduces a lot of boilerplate code.
   We want to write separate inline lambdas for each type directly inside std::visit like this:
   std::visit(overloaded {
       [](const CreditCardS& cc) {...},
       [](const PayPalS& pp) { ... }
   }, payment)
   But std::visit only accepts one object as its first argument. The 'overloaded' struct acts as the
   glue that morphs those individual lambdas into that single object.
*/

template<class... Ts> struct overloaded: Ts... {using Ts::operator()...; };
/* Above line does two massive things:
   1. struct overloaded: Ts... (Inheriting from everything): The ... means "a list of multiple things".
      This tells compiler that overloaded struct will inherit directly from every single lambda function
      we pass into it. In C++, qvery lambda is technically an anonymous class that overloads operator(). 
      By inheriting from them, overloaded gains access to all their execution paths.
   2. using Ts::operator()...; (Bringing them into scope): Normally, if the class inherits function
      with the same names from different parent classes, the compiler gets confused about which one 
      to use(called name hiding). This using statement tells the compiler: "Take the operator() from
      every single parent lambda, pull them into this one struct, and overload them normally."
*/

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
/* Above line represents User-Defined Deduction Guide. It is a hint to compiler that tells it to
   automatically figure out the template types when someone initializes an overloaded object without
   explicitly typing out template arguments inside angle brackets.
   1. Without this line: we have to type out the massive, unreadable internal compiler names of 
      every single lambda function when instantiating it.
   2. With this line: we can type simply overloaded{ lambda1, lambda2 } and the compiler looks at 
      arguments, deduce their types and handles background template generation seamlessly. 
*/

int main()
{
 vector<PaymentMethod> transactions;
 transactions.push_back(CreditCardS{"4111-XXXX-XXXX-1111", "02/27"});
 transactions.push_back(PayPalS{"john_doe@gmail.com"});
 transactions.push_back(CryptoWalletS{"0x71C...3A9", "BTC"});
 transactions.push_back(CreditCardS{"4051-XXXX-XXXX-1051", "02/27"});
 cout<<"--- Processing Daily Checkout Transactions ---\n";
 for(const auto& payment: transactions){
    visit(overloaded{
        [](const CreditCardS& cc){
            cout<<"[PAYMENT] Charging credit card: "<<cc.m_card_number<<endl;
        },
        [](const PayPalS& pp){
            cout<<"[PAYMENT] Authenticating PayPal account: "<<pp.m_email_address<<endl;
        },
        [](const CryptoWalletS& crypto){
            cout<<"[PAYMENT] Verifying "<<crypto.m_token_type<<" Transfer to "<<crypto.m_wallet_address<<endl;
        }
    }, payment);
 }
 return 0;
}