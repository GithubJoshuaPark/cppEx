#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr
#include "helloEx.h" // for printLine
#include "polymorphismEx.h"

// 1. The "Interface" (Abstract Base Class)
// A class with at least one pure virtual function is an abstract class.
// It defines a contract that derived classes must follow.
class Drivable {
public:
    // Pure virtual functions are declared with '= 0'.
    // They have no implementation in the base class.
    virtual void startEngine() = 0;
    virtual void drive() = 0;
    virtual void stopEngine() = 0;

    // It's crucial for a base class to have a virtual destructor.
    // This ensures that the correct destructor (e.g., ~Motorcycle) is called
    // when deleting a derived object through a base class pointer.
    virtual ~Drivable() { std::cout << "  Drivable object destroyed.\n"; }
};

// 2. A Concrete Class implementing the Drivable interface
class Motorcycle : public Drivable {
public:
    Motorcycle() { std::cout << "  Motorcycle created.\n"; }
    ~Motorcycle() { std::cout << "  Motorcycle destroyed.\n"; }

    // The derived class MUST provide an implementation for all pure virtual functions.
    void startEngine() override {
        std::cout << "  Motorcycle engine roars to life! Vroom!\n";
    }
    void drive() override {
        std::cout << "  Riding the motorcycle on the open road.\n";
    }
    void stopEngine() override {
        std::cout << "  Motorcycle engine sputters to a stop.\n";
    }
};

// 3. Another Concrete Class implementing the Drivable interface
class Sedan : public Drivable {
public:
    Sedan() { std::cout << "  Sedan created.\n"; }
    ~Sedan() { std::cout << "  Sedan destroyed.\n"; }

    void startEngine() override {
        std::cout << "  Sedan engine starts quietly.\n";
    }
    void drive() override {
        std::cout << "  Cruising smoothly in the sedan.\n";
    }
    void stopEngine() override {
        std::cout << "  Sedan engine shuts off.\n";
    }
};

void polymorphismEx(void) {
    printLine("Polymorphism and Interfaces Example");

    // 4. Polymorphism in action
    // We create a vector of smart pointers to the BASE class (Drivable).
    // This allows us to store different types of objects (Motorcycle, Sedan)
    // that share the same interface.
    std::vector<std::unique_ptr<Drivable>> vehicles;

    std::cout << "Adding vehicles to the garage...\n";
    vehicles.push_back(std::make_unique<Sedan>());
    vehicles.push_back(std::make_unique<Motorcycle>());
    std::cout << std::endl;

    // We can now treat all vehicles the same way, calling methods from the
    // Drivable interface. The correct 'drive()' method for each object's
    // actual type will be called automatically at runtime. This is polymorphism.
    std::cout << "Driving all vehicles...\n";
    for (const auto& vehicle : vehicles) {
        vehicle->startEngine();
        vehicle->drive();
        vehicle->stopEngine();
        std::cout << "  ---\n";
    }

    std::cout << "\nExample function is ending. All vehicles will be automatically destroyed.\n";
} // As 'vehicles' vector goes out of scope, the unique_ptrs are destroyed,
  // which in turn calls the correct destructors for Sedan and Motorcycle.