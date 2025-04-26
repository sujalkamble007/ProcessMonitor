#include "ProcessMonitor.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <libproc.h>

void ProcessMonitor::fetchProcesses() {
    // Step 1: Allocate a big enough array to hold all PIDs
    std::vector<pid_t> pids(4096);  // Allocate space for 4096 PIDs
    int bytesUsed = proc_listpids(PROC_ALL_PIDS, 0, &pids[0], sizeof(pid_t) * pids.size());
    int numPids = bytesUsed / sizeof(pid_t);

    if (numPids <= 0) {
        std::cout << "Failed to get processes!" << std::endl;
        return;
    }

    // Step 2: For each PID, fetch process information
    for (int i = 0; i < numPids; ++i) {
        if (pids[i] == 0) continue; // Skip empty entries

        struct proc_bsdinfo procInfo;
        int infoSize = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0, &procInfo, sizeof(procInfo));

        if (infoSize <= 0) {
            continue; // Failed to get info for this PID
        }

        // Step 3: Display PID and Name
        std::cout << "PID: " << procInfo.pbi_pid
                  << " | Name: " << procInfo.pbi_comm
                  << std::endl;
                  <<"-------------------------";
    }
}

void ProcessMonitor::displayProcesses() {
    while (true) {
        system("clear");  // Clear the terminal for fresh output
        fetchProcesses();
        sleep(5);         // Wait 5 seconds
    }
}
