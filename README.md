# CPUTest - a set of tools to test CPU

- **CPU100DotNet**
  - DotNet version of CPU100 to observe hyper arch scheduling with Apps that have GUI on Windows 11
  
- **CPU100 [seconds]**
  - grab 100% CPU usage for certain seconds

- **SingleCorePerf [core_id], [rounds], [cpu_x]**
  - parameters
    - [core_id]: which core to bound, -1 means no bounding.
    - [rounds]: rounds of workload to run.
    - [cpu_x]: if > 1 then *x cpu usage in next round.
  - The aim of this utility is to observe OS scheduler behavior for single threaded workload, and compare single core perf on big-little arch platforms. 
  - with this utility, we can know:
    - which core will be used by default;
    - whether/when OS scheduler will switch the workload to other core;
    - performances of different cores;
