#include <iostream>

int main()
{
    char a [1024 * 1024 * 1024]; // it will cause stackflow in debug mode as it is asking for 1GB memory while stack has ~1MB(depends on the platform)
                                //  in release mode compile will optimize it by removing it as we didn't use this memory
    std::cout << "Stack overflow!";
    return 0;
}