// CPU100.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>
#include <Windows.h>
#include <float.h>
#include <thread>  
#include <string>  
#include<iomanip>
#pragma comment(lib, "Winmm.lib")

const int DURATION_DEBUG = -65536;
static bool done = false;

LONGLONG get_time_ms() {
    FILETIME ft_now;
    GetSystemTimeAsFileTime(&ft_now);
    return ((LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL)) / 10000;
}

int get_cpu_core_count() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}

void worker() {
    double i = 0.0f;
    while (!done) {
        i++;
        i--;
    }
}

void set_process_qos(bool high) {
    PROCESS_POWER_THROTTLING_STATE PowerThrottling;
    RtlZeroMemory(&PowerThrottling, sizeof(PowerThrottling));
    PowerThrottling.Version = PROCESS_POWER_THROTTLING_CURRENT_VERSION;
    PowerThrottling.ControlMask = PROCESS_POWER_THROTTLING_EXECUTION_SPEED;
    PowerThrottling.StateMask = high ? 0 : PROCESS_POWER_THROTTLING_EXECUTION_SPEED;

    SetProcessInformation(GetCurrentProcess(),
        ProcessPowerThrottling,
        &PowerThrottling,
        sizeof(PowerThrottling));
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "usage CPU100 [seconds] " << "\n";
        return -1;
    }
    int target_s = std::stoi(argv[1]);
    if (target_s == DURATION_DEBUG) {
        target_s = get_time_ms() % 8; // random value 0s ~ 8s;
    }
    std::cout << "Hoding 100% CPU usage for " << target_s << " seconds.\n";

    int cpu_acount = get_cpu_core_count();
    if (argc == 3) {
        std::cout << "manual cpu count: " << std::stoi(argv[2]) << "\n";
        cpu_acount = std::stoi(argv[2]);
    }
    std::thread t[129];
    if (cpu_acount >= 129 || cpu_acount < 1) {
        std::cout << "We don't support this platform. " << std::endl;
        return -1;
    }
    LONGLONG start_time_ms = get_time_ms();
    for (int i = 0; i < cpu_acount - 1; i++) {
        t[i] = std::thread(worker);
        t[i].detach();
    }

    LONGLONG time_elapsed_ms = -1;
    int target_ms = target_s * 1000;
    //mciSendString(L"open \"Ð¡±ø²Ù.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
    //mciSendString(L"play mp3", NULL, 0, NULL);

    set_process_qos(true);
    while (true) {
        time_elapsed_ms = get_time_ms() - start_time_ms;
        if (time_elapsed_ms >= target_ms) {
            done = true;
            std::cout << "Actually we hold 100% CPU for " << std::setiosflags(std::cout.fixed) << std::setprecision(3) << (time_elapsed_ms / 1000.0f) << " s." << std::endl;
            break;
        }
        DWORD pid = 0;
        GetWindowThreadProcessId(GetConsoleWindow(), &pid);
        if (pid != GetCurrentProcessId()) {
            std::cout << "GetConsoleWindow: " << pid << " GetCurrentProcessId: " << GetCurrentProcessId() << std::endl;
        }
    }
    return 0;
}