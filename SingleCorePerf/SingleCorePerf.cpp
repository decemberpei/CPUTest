// SingleCorePerf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <Windows.h>
#include <string>
#include <processthreadsapi.h>
#include <thread> 
#include <intrin.h>
#include <exception>

static int target_core = 0;
static int workload_x = 1;
static float cpu_x_base = 0;

static LONGLONG get_time_ms() {
    FILETIME ft_now;
    GetSystemTimeAsFileTime(&ft_now);
    return ((LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL)) / 10000;
}
#ifdef _M_X64
int avx2() {
    __m256d a = _mm256_set_pd(1.0, 2.0, 3.0, 4.0);
    __m256d b = a;
    __m256d c = _mm256_add_pd(a, b);
    __declspec(align(32)) double output[4];
    _mm256_store_pd(output, c);
    return 0;
}

int avx512() {
    __m512d a = _mm512_set_pd(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    __m512d b = a;
    __m512d c = _mm512_add_pd(a, b);
    __declspec(align(32)) double output[8];
    _mm512_store_pd(output, c);
    return 0;
}
#endif

static void worker() {
    if (target_core == -1) {
        std::cout << "Do not set thread affinity for core id -1." << std::endl;
    }
    else {
        if (0 == SetThreadAffinityMask(GetCurrentThread(), 1 << target_core)) {
            std::cout << "Failed to set thread affinity: " << GetLastError() << std::endl;
            return;
        }
        std::cout << "Set thread affinity for core id " << target_core << "." << std::endl;
    }
#ifdef _M_X64
    try {
        avx2();
        std::cout << "AVX2 instruction supported." << "\n";
    }
    catch (...) {
        std::cout << "AVX2 instruction not supported!" << "\n";
    }

    try {
        avx512();
        std::cout << "AVX512 instruction supported." << "\n";
    }
    catch (...) {
        std::cout << "AVX512 instruction not supported!" << "\n";
    }
#endif

    DOUBLE ft = 0.0f;
    float cpu_x = cpu_x_base;
    LONGLONG start_time_ms = get_time_ms();
    for (int workloadx = 0; workloadx < workload_x; workloadx++) {
        if (cpu_x_base > 1) {
            cpu_x = cpu_x * cpu_x_base;
            std::cout << "Round " << workloadx << " with cpu usage x " << cpu_x << ".\n";
            for (INT32 i = 0; i < 128; i++) {
                for (int l = 0; l < ((int)cpu_x) * 128; l++) {
                    ft = ft * rand();
                }
                if (cpu_x_base > 1) {
                    Sleep(1);
                }
            }
        }
        else {
            std::cout << "Round " << workloadx << ".\n";
            for (INT32 i = 0; i < 4 * 1024 * 1024; i++) {
                ft = ft * rand();
            }
        }
    }
    LONGLONG duration_ms = get_time_ms() - start_time_ms;
    std::cout << "Test done. Total time elapsed: " << duration_ms << " ms.\n";
}

void showUsage() {
    std::cout << "===\n";
    std::cout << "Usage: SingleCorePerf [core_id], [workload_number], [cpu_x]" << "\n";
    std::cout << "  [core_id]: which core to bound, -1 means no bounding. " << "\n";
    std::cout << "  [rounds]: rounds of workload to run," << "\n";
    std::cout << "  [cpu_x]: if > 1 then *x cpu usage in next round." << "\n";
    std::cout << "===\n";
}

int main(int argc, char* argv[]) {
    // parse params;
    if (argc != 4) {
        showUsage();
        return -1;
    }
    try {
        target_core = std::stoi(argv[1]);
        workload_x = std::stoi(argv[2]);
        cpu_x_base = std::stof(argv[3]);
    }
    catch (...) {
        showUsage();
        return -1;
    }

    if (target_core == -1) {
        worker();
    }
    else {
        std::thread t = std::thread(worker);
        t.join();
    }
    return 0;
}