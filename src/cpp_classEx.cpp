#include <iostream>
#include <string>
#include "helloEx.h" // Note: This file uses C-style printf
#include "cpp_classEx.h"

// 1. Base Class Definition
// A class is a blueprint for creating objects. It bundles data (attributes)
// and functions (methods) that work on the data.
class Car {
private:
    // Private members are encapsulated. They can only be accessed by
    // member functions of this class. This protects the data from
    // accidental modification.
    std::string make;
    std::string model;
    int year;
    int speed;

public:
    // Public members form the interface of the class. They can be
    // accessed from outside the class.

    // Constructor: A special method called when a Car object is created.
    // It's used to initialize the object's state using a member initializer list.
    Car(const std::string& carMake, const std::string& carModel, int carYear)
        : make(carMake), model(carModel), year(carYear), speed(0) {
        std::cout << "  A new car '" << year << " " << make << " " << model << "' has been created.\n";
    }

    // Destructor: A special method called when the object is destroyed.
    // It's useful for cleanup, like freeing allocated memory.
    ~Car() {
        std::cout << "  The car '" << make << " " << model << "' is being destroyed.\n";
    }

    // A public member function (method) to accelerate the car.
    void accelerate(int amount) {
        speed += amount;
        std::cout << "  Accelerating... Current speed: " << speed << " km/h\n";
    }

    // A public member function to apply the brakes.
    void brake(int amount) {
        speed -= amount;
        if (speed < 0) {
            speed = 0;
        }
        std::cout << "  Braking... Current speed: " << speed << " km/h\n";
    }

    // A public member function to display the car's information.
    void displayInfo() const { // 'const' means this method doesn't modify the object's state.
        std::cout << "  Car Info: " << year << " " << make << " " << model
                  << ", Current Speed: " << speed << " km/h\n";
    }
};

// 5. Derived Class Definition (Inheritance)
// SuperCar inherits publicly from Car. This means SuperCar has all public and
// protected members of Car, and can access them.
class SuperCar : public Car {
private:
    int nitroLevel; // SuperCar's unique attribute

public:
    // Constructor for SuperCar. It calls the base class (Car) constructor
    // using an initializer list.
    SuperCar(const std::string& carMake, const std::string& carModel, int carYear, int initialNitro)
        : Car(carMake, carModel, carYear), nitroLevel(initialNitro) {
        std::cout << "  A new SuperCar has been created with " << nitroLevel << " nitro.\n";
    }

    // Destructor for SuperCar. Base class destructor is called automatically.
    ~SuperCar() {
        std::cout << "  The SuperCar is being destroyed.\n";
    }

    // SuperCar's unique method
    void activateNitro() {
        if (nitroLevel > 0) {
            std::cout << "  NITRO BOOST ACTIVATED! Speed increased significantly!\n";
            accelerate(100); // Use base class method
            nitroLevel -= 10;
            std::cout << "  Nitro remaining: " << nitroLevel << "\n";
        } else {
            std::cout << "  No nitro left!\n";
        }
    }

    // Override/Extend base class method
    // We use 'override' keyword (C++11) to explicitly state that this method
    // is intended to override a virtual function in the base class.
    // (Note: For this simple example, Car's displayInfo doesn't need to be virtual,
    // but if you wanted polymorphic behavior, it would be).
    void displayInfo() const {
        // Call the base class's displayInfo to reuse its logic
        Car::displayInfo();
        std::cout << "  (SuperCar specific: Nitro Level: " << nitroLevel << ")\n";
    }

    // If you wanted to make displayInfo polymorphic, you'd add 'virtual' to Car's displayInfo:
    // virtual void displayInfo() const { ... }
    // And then in SuperCar:
    // void displayInfo() const override { ... }
    // This allows calling the correct displayInfo based on the actual object type, even through a base class pointer/reference.
};

void cpp_classEx(void) {
    printLine("C++ Class Example");


    {
        // 2. Object Instantiation
        // Create an instance (object) of the Car class.
        // The constructor is called automatically here.
        std::cout << "Creating a Car object...\n";
        Car myCar("Honda", "Civic", 2023);
        std::cout << "Car object created.\n\n";
    
        // 3. Interacting with the Object
        // We can only call the public methods to interact with the object.
        myCar.displayInfo();
        myCar.accelerate(50);
        myCar.brake(20);
        myCar.displayInfo();
    
        // 4. Encapsulation in action
        // The following line would cause a COMPILE ERROR because 'speed' is private.
        // This protects the object's state from being corrupted.
        // myCar.speed = -100; // <-- This is not allowed!
        std::cout << "\n(Note: Direct access to private members like 'myCar.speed' is prevented by the compiler.)\n";
    
        std::cout << "\nThe 'cpp_classEx' function is about to end. The Car object will be destroyed.\n";
    }

    // The 'myCar' object goes out of scope here, and its destructor is automatically called.
    printLine("SuperCar Class Example");

    // Create an instance of SuperCar
    std::cout << "Creating a SuperCar object...\n";
    SuperCar mySuperCar("Bugatti", "Chiron", 2024, 50);
    std::cout << "SuperCar object created.\n\n";

    // Use inherited methods
    mySuperCar.displayInfo();
    mySuperCar.accelerate(80);

    // Use SuperCar's unique method
    mySuperCar.activateNitro();
    mySuperCar.displayInfo();

    std::cout << "\nThe 'cpp_classEx' function is about to end. The SuperCar object will be destroyed.\n";
} // The 'mySuperCar' object goes out of scope here, and its destructor is automatically called.