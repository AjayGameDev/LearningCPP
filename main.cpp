#include <iostream>

int main()
{
    volatile char a [1024 * 1024 * 1024]; // it will stop compiler from removing it in optimization step
    a[0] = 'a'; // writing to it will force memory allocation

    std::cout << "Stack overflow!";
    return 0;
}