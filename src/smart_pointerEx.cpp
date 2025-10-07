#include <iostream>
#include <memory> // Required for smart pointers (shared_ptr, unique_ptr, weak_ptr)
#include <string>
#include "helloEx.h" // for printLine
#include "smart_pointerEx.h"

// A simple class to demonstrate object lifetime
class MyClass {
public:
    MyClass(const std::string& name) : name_(name) {
        std::cout << "  Constructor for MyClass '" << name_ << "' called.\n";
    }
    ~MyClass() {
        std::cout << "  Destructor for MyClass '" << name_ << "' called.\n";
    }
    void greet() const {
        std::cout << "  Hello from MyClass '" << name_ << "'!\n";
    }
private:
    std::string name_;
};

// --- For demonstrating circular references ---
struct NodeB; // Forward declaration

struct NodeA {
    std::shared_ptr<NodeB> b_ptr;
    NodeA() { std::cout << "  NodeA Constructor\n"; }
    ~NodeA() { std::cout << "  NodeA Destructor\n"; }
};

struct NodeB {
    // Using a weak_ptr breaks the circular reference
    std::weak_ptr<NodeA> a_ptr; 
    NodeB() { std::cout << "  NodeB Constructor\n"; }
    ~NodeB() { std::cout << "  NodeB Destructor\n"; }
};


void smart_pointerEx(void) {
    printLine("Smart Pointers Example");

    // --- 1. std::unique_ptr ---
    // Exclusive ownership. Lightweight and fast.
    std::cout << "--- 1. std::unique_ptr ---\n";
    {
        // Use std::make_unique to create the object and the smart pointer.
        // This is safer and more efficient than `new MyClass(...)`.
        std::unique_ptr<MyClass> u_ptr1 = std::make_unique<MyClass>("UniquePtr-1");
        u_ptr1->greet();

        // You cannot copy a unique_ptr:
        // std::unique_ptr<MyClass> u_ptr2 = u_ptr1; // COMPILE ERROR!

        // You can only move it, which transfers ownership.
        std::unique_ptr<MyClass> u_ptr2 = std::move(u_ptr1);
        std::cout << "  Ownership transferred to UniquePtr-2.\n";

        if (!u_ptr1) {
            std::cout << "  u_ptr1 is now empty (null).\n";
        }

        u_ptr2->greet();

        // The MyClass object is automatically deleted when u_ptr2 goes out of scope.
        std::cout << "  unique_ptr scope is ending...\n";
    } // Destructor for "UniquePtr-1" is called here.
    std::cout << std::endl;


    // --- 2. std::shared_ptr ---
    // Shared ownership with reference counting.
    std::cout << "--- 2. std::shared_ptr ---\n";
    {
        std::shared_ptr<MyClass> s_ptr2; // Will hold a reference later
        {
            // Use std::make_shared for safety and efficiency.
            std::shared_ptr<MyClass> s_ptr1 = std::make_shared<MyClass>("SharedPtr");
            std::cout << "  Reference count: " << s_ptr1.use_count() << std::endl;
    
            // Create another shared_ptr pointing to the same object.
            s_ptr2 = s_ptr1;
            std::cout << "  Copied shared_ptr. Reference count: " << s_ptr1.use_count() << std::endl;
    
            s_ptr1->greet();
            s_ptr2->greet();
    
            std::cout << "  s_ptr1 scope is ending...\n";
        } // s_ptr1 goes out of scope, but the object is NOT deleted yet.
        std::cout << "  s_ptr1 scope has ended. Reference count: " << s_ptr2.use_count() << std::endl;
        std::cout << "  s_ptr2 scope is ending...\n";
        // The MyClass object is automatically deleted when s_ptr2 goes out of scope.
        // (i.e., when the reference count drops to 0).
    }


    // --- 3. std::weak_ptr ---
    // Breaking circular references.
    std::cout << "\n--- 3. std::weak_ptr (for circular references) ---\n";
    {
        std::shared_ptr<NodeA> a = std::make_shared<NodeA>();
        std::shared_ptr<NodeB> b = std::make_shared<NodeB>();

        // Create a cycle: A points to B, and B points to A
        a->b_ptr = b;
        b->a_ptr = a; // a_ptr is a weak_ptr, so it does NOT increase the reference count for 'a'.

        std::cout << "  Reference count for NodeA: " << a.use_count() << std::endl;
        std::cout << "  Reference count for NodeB: " << b.use_count() << std::endl;

        // To access the object from a weak_ptr, you must "lock" it to get a temporary shared_ptr.
        if (auto locked_a = b->a_ptr.lock()) {
            std::cout << "  Successfully accessed NodeA from NodeB.\n";
        } else {
            std::cout << "  Could not access NodeA from NodeB (it was deleted).\n";
        }

        std::cout << "  Cycle created. Scopes are ending...\n";
    } // Because b->a_ptr is weak, NodeA's ref count goes to 0 and it's deleted.
      // This in turn allows NodeB's ref count to go to 0, and it is also deleted.
      // If b->a_ptr were a shared_ptr, neither would be deleted, causing a memory leak.

    printLine("Smart Pointers Example Completed");
}