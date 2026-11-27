#include <assert.h>
#include <cstdint>
#include <iostream>

class MemoryAllocator
{
    size_t size; // in bytes
    size_t freeSpace;
    size_t offset;
    std::byte* memory; // C++ doesn't allow arithmetic on *void or void pointer so memory + offset won't work

public:

    explicit MemoryAllocator(const int64_t requestedSize) : size(requestedSize),offset(0)
    {
        if (requestedSize <= 0)
        {
            throw std::invalid_argument("Required size must be positive");
        }

        memory = static_cast<std::byte*>(std::malloc(size));

        if (memory==nullptr)
        {
            throw std::runtime_error("Not enough memory allocated by OS");
        }

        offset = 0;
        freeSpace = requestedSize;
    }
    ~MemoryAllocator()
    {
        std::free(memory);
    }

    template<typename T>
    T* Allocate(const size_t count)
    {
        if (count <= 0)
            return nullptr;

        size_t alignment = alignof(T);
        size_t requestedSize = count * sizeof(T);

        // Convert current position address into integer so we know we are starting at aligned address
        // static cast can't convert from pointer to value(int,float)[Except bool] or pointer(int* or float*) to another pointer(byte* or int* or float*) types so use reinterpret cast which will just tell compiler that see it as just a number and not pointer
        // static cast can be used for void* here for all types but that doesn't allow pointer arithmetic like memory + offset + padding
        uintptr_t currentAddress = reinterpret_cast<uintptr_t>(memory) + offset;

        uintptr_t alignedAddress = 0;

        if ( (alignment & (alignment - 1) ) == 0) // if alignment is power of 2(1,2,4,8)
            alignedAddress = (currentAddress + alignment - 1) & ~(alignment - 1);
        else
            alignedAddress = ( (currentAddress + alignment - 1) / alignment ) * alignment;


        size_t padding = alignedAddress - currentAddress;

        if ( padding > freeSpace || requestedSize  > (freeSpace - padding) )
            return nullptr;

        std::byte* address = memory + offset + padding;

        offset = offset + padding + requestedSize;
        freeSpace = size - offset;

        return reinterpret_cast<T*>(address);
    }

    /*
    std::byte* Allocate(const size_t requestedSize,const size_t alignment = alignof(std::max_align_t))
    {


        // Convert current position address into integer so we know we are starting at aligned address
        // static cast can't convert from pointer to value(int,float)[Except bool] or pointer(int* or float*) to another pointer(byte* or int* or float*) types so use reinterpret cast which will just tell compiler that see it as just a number and not pointer
        // static cast can be used for void* here for all types but that doesn't allow pointer arithmetic like memory + offset + padding
        uintptr_t currentAddress = reinterpret_cast<uintptr_t>(memory) + offset;

        uintptr_t alignedAddress = 0;

        if ( (alignment & (alignment - 1) ) == 0) // if alignment is power of 2(1,2,4,8)
             alignedAddress = (currentAddress + alignment - 1) & ~(alignment - 1);
        else
            alignedAddress = ( (currentAddress + alignment - 1) / alignment ) * alignment;


        size_t padding = alignedAddress - currentAddress;

        if ( padding > freeSpace || requestedSize  > (freeSpace - padding) )
            return nullptr;

        std::byte* address = memory + offset + padding;

        offset = offset + padding + requestedSize;
        freeSpace = size - offset;

        return address;
    }

    */


    void Reset()
    {
        offset = 0;
        freeSpace = size;
    }
    // delete copy constructors to avoid double free crash
    MemoryAllocator(const MemoryAllocator&) = delete;
    MemoryAllocator& operator=(const MemoryAllocator&) = delete;

};

int main()
{
    MemoryAllocator memoryAllocator(1024LL * 1024LL * 1024LL); // Create memory pool of 1GB
    int count = 10;
    int* intArray = memoryAllocator.Allocate<int>(count);

    if (intArray!= nullptr)
    {
        for (int i = 0;i<count;i++)
        {
            intArray[i] = i;
        }
    }

    if (intArray!= nullptr)
    {
        for (int i = 0;i<count;i++)
        {
            std::cout << intArray[i] << "\n";
        }
    }
    return 0;
}