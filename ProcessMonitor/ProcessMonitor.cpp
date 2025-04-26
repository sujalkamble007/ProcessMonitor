#include "ProcessMonitor.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <libproc.h>
#include <mach/mach.h>   // Important for task_info

void ProcessMonitor::fetchProcesses() {
    std::vector<pid_t> pids(4096);
    int bytesUsed = proc_listpids(PROC_ALL_PIDS, 0, &pids[0], sizeof(pid_t) * pids.size());
    int numPids = bytesUsed / sizeof(pid_t);

    if (numPids <= 0) {
        std::cout << "Failed to get processes!" << std::endl;
        return;
    }

    std::cout << "PID\t\tName\t\t\tMemory (MB)\tCPU Time (s)\n";
    std::cout << "------------------------------------------------------------------\n";

    for (int i = 0; i < numPids; ++i) {
        if (pids[i] == 0) continue;

        struct proc_bsdinfo procInfo;
        int infoSize = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0, &procInfo, sizeof(procInfo));

        if (infoSize <= 0) {
            continue;
        }

        // Get mach_task
        mach_port_t task;
        kern_return_t kr = task_for_pid(mach_task_self(), pids[i], &task);

        double memoryMB = 0.0;
        double cpuTimeSec = 0.0;

        if (kr == KERN_SUCCESS) {
            struct task_basic_info tinfo;
            mach_msg_type_number_t task_info_count = TASK_BASIC_INFO_COUNT;

            if (task_info(task, TASK_BASIC_INFO, (task_info_t)&tinfo, &task_info_count) == KERN_SUCCESS) {
                memoryMB = tinfo.resident_size / (1024.0 * 1024.0);  // Convert bytes to MB
                cpuTimeSec = tinfo.user_time.seconds + tinfo.system_time.seconds;
            }
        }

        std::cout << pids[i] << "\t\t" 
                  << procInfo.pbi_comm << "\t\t" 
                  << memoryMB << "\t\t" 
                  << cpuTimeSec
                  << std::endl;
    }
}

void ProcessMonitor::displayProcesses() {
    while (true) {
        system("clear");
        fetchProcesses();
        std ::cout<<"-------------------------------------------------------------------------------\n";
        sleep(5);
    }
}
