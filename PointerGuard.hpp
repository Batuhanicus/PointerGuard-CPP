#ifndef POINTER_GUARD_HPP
#define POINTER_GUARD_HPP

#include <iostream>
#include <map>

class PointerGuard
{
private:
    // Tracks address -> size of allocated memory block
    std::map<void *, size_t> activeAllocations;
    size_t totalAllocatedMemory;

public:
    PointerGuard() : totalAllocatedMemory(0) {}

    // Disable copy/move to prevent tracker duplication or invalid transfer of ownership
    PointerGuard(const PointerGuard &) = delete;
    PointerGuard &operator=(const PointerGuard &) = delete;
    PointerGuard(PointerGuard &&) = delete;
    PointerGuard &operator=(PointerGuard &&) = delete;

    // Destructor automatically runs at program end to report leaks
    ~PointerGuard() noexcept
    {
        std::cout << "\n--- POINTERGUARD MEMORY REPORT ---\n";
        if (activeAllocations.empty())
        {
            std::cout << "SUCCESS: Zero memory leaks detected. All heap memory freed cleanly!\n";
        }
        else
        {
            std::cout << "WARNING: Memory leaks detected!\n";
            for (const auto &pair : activeAllocations)
            {
                std::cout << "-> Leaked block at address: " << pair.first
                          << " (" << pair.second << " bytes)\n";
            }
        }
        std::cout << "Total unreleased memory: " << totalAllocatedMemory << " bytes.\n";
        std::cout << "----------------------------------\n";
    }

    // Custom allocation wrapper
    template <typename T>
    T *allocate(size_t count = 1)
    {
        size_t bytes = sizeof(T) * count;
        T *ptr = new T[count]; // Allocate raw memory

        void *address = static_cast<void *>(ptr);
        activeAllocations[address] = bytes;
        totalAllocatedMemory += bytes;

        std::cout << "[ALLOCATED] " << bytes << " bytes at address: " << address << "\n";
        return ptr;
    }

    // Custom deallocation wrapper that takes a reference to a pointer
    template <typename T>
    void deallocate(T *&ptr)
    {
        if (ptr == nullptr)
            return;

        void *address = static_cast<void *>(ptr);
        auto it = activeAllocations.find(address);

        if (it != activeAllocations.end())
        {
            totalAllocatedMemory -= it->second;
            activeAllocations.erase(it);

            std::cout << "[FREED] Clearing memory block at address: " << address << "\n";
            delete[] ptr;  // Release raw memory
            ptr = nullptr; // Safety rule: eliminate dangling pointers
        }
        else
        {
            std::cout << "[ERROR] Attempted to free unregistered memory address: " << address << "\n";
        }
    }
};

#endif
 