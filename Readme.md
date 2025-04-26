# Process Monitor

## Overview
The **Process Monitor** is a C++ application designed to fetch and display information about all running processes on a macOS system. It uses system calls and APIs provided by macOS to retrieve process details such as Process ID (PID), process name, memory usage, and CPU time. The application continuously updates the process list every 5 seconds, providing a real-time view of the system's processes.

## Features
- Fetches all running processes on the system.
- Displays the following details for each process:
  - **PID**: Process ID.
  - **Name**: Name of the process.
  - **Memory Usage**: Resident memory size in MB.
  - **CPU Time**: Total CPU time used by the process in seconds.
- Continuously updates the process list every 5 seconds.
- Uses macOS-specific system calls for process management.

## Files in the Project
1. **`ProcessMonitor.h`**: Header file defining the `ProcessMonitor` class.
2. **`ProcessMonitor.cpp`**: Implementation of the `ProcessMonitor` class.
3. **`main.cpp`**: Entry point of the application.
4. **`README.md`**: Documentation for the project.

---

## OS Theory

### Process Management
A process is an instance of a program in execution. The operating system is responsible for managing processes, which includes:
- Allocating resources (CPU, memory, etc.).
- Scheduling processes for execution.
- Providing mechanisms for inter-process communication (IPC).
- Monitoring and controlling processes.

### System Calls
System calls are the interface between user applications and the operating system. They allow applications to request services from the OS kernel. In this project, we use the following system calls and APIs:
1. **`proc_listpids`**: Retrieves a list of all process IDs (PIDs) on the system.
2. **`proc_pidinfo`**: Fetches detailed information about a specific process.
3. **`task_for_pid`**: Retrieves the Mach task port for a given PID.
4. **`task_info`**: Fetches detailed information about a task, including memory usage and CPU time.
5. **`system`**: Executes shell commands (used to clear the terminal).
6. **`sleep`**: Pauses the program execution for a specified duration.

---

## Explanation of Functions and System Calls

### `fetchProcesses()`
This function retrieves and displays information about all running processes.
- **Steps**:
  1. Allocate a buffer to hold PIDs using a `std::vector`.
  2. Use the `proc_listpids` system call to populate the buffer with all PIDs.
  3. Iterate through the PIDs and use `proc_pidinfo` to fetch details for each process.
  4. Use `task_for_pid` and `task_info` to retrieve memory usage and CPU time for each process.
  5. Print the PID, process name, memory usage, and CPU time to the console.
- **System Calls Used**:
  - `proc_listpids`: Retrieves all process IDs.
  - `proc_pidinfo`: Fetches detailed information about a process.
  - `task_for_pid`: Retrieves the Mach task port for a given PID.
  - `task_info`: Fetches memory usage and CPU time for a task.

### `displayProcesses()`
This function continuously updates the process list every 5 seconds.
- **Steps**:
  1. Clear the terminal using the `system("clear")` command.
  2. Call `fetchProcesses()` to display the current process list.
  3. Print a separator line for better readability.
  4. Pause for 5 seconds using the `sleep` function.
- **System Calls Used**:
  - `system`: Executes the `clear` command to refresh the terminal.
  - `sleep`: Pauses execution for 5 seconds.

### `main()`
The entry point of the application.
- **Steps**:
  1. Create an instance of the `ProcessMonitor` class.
  2. Call the `displayProcesses()` method to start monitoring processes.

---

## How to Build and Run
1. **Build the Project**:
   ```bash
   g++ -o ProcessMonitor main.cpp ProcessMonitor.cpp -framework CoreFoundation -framework IOKit
   ```
2. **Run the Application**:
   ```bash
   sudo ./ProcessMonitor
   ```

   > **Note**: The application requires elevated privileges to access process information.

---

## Notes
- This project is designed specifically for macOS and uses macOS-specific system calls (`proc_listpids`, `proc_pidinfo`, `task_for_pid`, and `task_info`).
- Ensure you have the necessary permissions to access process information.

---

## Future Enhancements
- Add support for filtering processes by name or PID.
- Implement a graphical user interface (GUI) for better visualization.
- Extend support to other operating systems like Linux or Windows.

---

## References
- [Apple Developer Documentation: proc_listpids](https://developer.apple.com/documentation)
- [Apple Developer Documentation: proc_pidinfo](https://developer.apple.com/documentation)
- [Apple Developer Documentation: task_for_pid](https://developer.apple.com/documentation)
- [Apple Developer Documentation: task_info](https://developer.apple.com/documentation)
- [UNIX System Calls](https://en.wikipedia.org/wiki/System_call)