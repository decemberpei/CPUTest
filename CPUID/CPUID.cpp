#include <iostream>
#include <intrin.h>
#include <iomanip>

int main() {
    int cpuInfo[4] = { 0 };
    __cpuid(cpuInfo, 1);
    std::cout << "CPUID: " << std::hex << cpuInfo[0] << std::endl;
    std::cout << "Press enter to exit."<< std::endl;
    std::cin.get();
    return 0;
}