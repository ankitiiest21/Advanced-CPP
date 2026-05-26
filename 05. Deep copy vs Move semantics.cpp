/* Rule of Five: If we declare any one of these, we should explicitly declare or default 
   all five to ensure consistent behavior:
   1. Destructor
   2. Copy Constructor
   3. Copy Assignment Operator
   4. Move Constructor
   5. Move Assignment Operator
   BigData(BigData&& other) noexcept = default; => this will enable default move semantics if
   we don't want to define it explicitly.
*/

#include <iostream>
#include <utility> // For std::move

class BigData {
public:
    int* data;
    size_t size;

    // Standard Constructor
    BigData(size_t s) : size(s) {
        data = new int[size];
        std::cout << "[CONSTRUCTOR] Allocated resource at address: " << data << "\n";
    }

    // Destructor
    ~BigData() {
        if (data != nullptr) {
            std::cout << "[DESTRUCTOR] Freeing resource at address: " << data << "\n";
            delete[] data;
        } else {
            std::cout << "[DESTRUCTOR] Destructor called for empty/moved object.\n";
        }
    }

    // 1. User-Defined Copy Constructor (Deep Copy)
    BigData(const BigData& other) : size(other.size) {
        data = new int[size]; // Allocate brand new, unique memory block
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "[COPY CONSTRUCTOR] Deep Copied to a new address: " << data << "\n";
    }

    // 2. User-Defined Move Constructor (Resource Stealing)
    BigData(BigData&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr; // Nullify the source pointer so it doesn't free our memory
        other.size = 0;
        std::cout << "[MOVE CONSTRUCTOR] Stole resource pointer from old object. New address: " << data << "\n";
    }
};

int main() {
    std::cout << "--- 1. INITIALIZING SOURCE OBJECT ---\n";
    BigData source(100);
    std::cout << "Source data pointer: " << source.data << "\n\n";

    std::cout << "--- 2. EXECUTING DEEP COPY ---\n";
    // This calls the traditional Copy Constructor
    BigData copied_obj = source; 
    std::cout << "Source data pointer after copy: " << source.data << "\n";
    std::cout << "Copied object data pointer:    " << copied_obj.data << "\n\n";

    std::cout << "--- 3. EXECUTING MOVE SEMANTICS ---\n";
    // std::move casts 'source' into an rvalue, forcing the Move Constructor
    BigData moved_obj = std::move(source); 
    std::cout << "Source data pointer after move: " << source.data << " (Now Null/Safe)\n";
    std::cout << "Moved object data pointer:     " << moved_obj.data << "\n\n";

    std::cout << "--- 4. CLEANUP (DESTRUCTORS) ---\n";
    // Watch what happens when objects go out of scope here
    return 0;
}