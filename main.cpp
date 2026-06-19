#include <iostream>
#include "PointerGuard.hpp"

int main()
{
    PointerGuard guard;

    std::cout << "--- Starting Dynamic Memory Simulation ---\n\n";

    // Scenario 1: Clean allocation and safe deallocation
    std::cout << "Scenario 1: Allocating an array of 5 integers...\n";
    int *myNumbers = guard.allocate<int>(5);

    std::cout << "Deallocating array securely...\n";
    guard.deallocate(myNumbers);

    if (myNumbers == nullptr)
    {
        std::cout << "Verification: Pointer was successfully grounded to nullptr!\n\n";
    }

    // Scenario 2: Preventing dangling pointer access
    std::cout << "Scenario 2: Double-free protection test...\n";
    guard.deallocate(myNumbers); // Safe; ignores null pointer instead of crashing

    // Scenario 3: Simulating a forgotten memory leak
    std::cout << "\nScenario 3: Simulating an unreleased heap allocation...\n";
    double *leakedPrice = guard.allocate<double>(1);
    *leakedPrice = 99.99;

    std::cout << "\nExiting main() execution scope without releasing leakedPrice...\n";
    // The destructor for 'guard' will now automatically run and flag the leak!
    return 0;
}
