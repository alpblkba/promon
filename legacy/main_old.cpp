#include <iostream>
#include <unistd.h>

#ifdef __APPLE__
    #include <mach/mach.h>
#elif __linux__
    #include <fstream>
    #include <string>
    #include <sstream>
#endif

class SystemMonitor {
public:
    double getMemoryUsage() {
        // mac
        #ifdef __APPLE__
            vm_statistics64_data_t vm_stats;
            mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;

            if (host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info64_t)&vm_stats, &count) == KERN_SUCCESS) {
                // PAGE_SIZE is a built-in constant in mac headers
                return (double)vm_stats.active_count * PAGE_SIZE;
            }
        #endif

        // linux
        #ifdef __linux__
            std::ifstream file("/proc/meminfo");
            std::string line;
            double memTotal = 0;
            double memAvailable = 0;

            if (!file.is_open()) return 0.0;

            while (std::getline(file, line)) {
                if (line.compare(0, 8, "MemTotal") == 0) {
                    std::stringstream ss(line);›
                    std::string label;
                    ss >> label >> memTotal; 
                }
                if (line.compare(0, 12, "MemAvailable") == 0) {
                    std::stringstream ss(line);
                    std::string label;
                    ss >> label >> memAvailable;
                }
            }
            // (Total - Available) * 1024 because /proc/meminfo is in kB
            return (memTotal - memAvailable) * 1024.0;
        #endif

        return 0.0; // Fallback for other OS
    }
};

int main() {
    SystemMonitor monitor;

    std::cout << "--- Starting Low-Level Monitor ---" << std::endl;

    for(int i = 0; i < 10; i++) {
        double bytes = monitor.getMemoryUsage();
        double megabytes = bytes / (1024.0 * 1024.0);
        
        std::cout << "Memory In Use: " << megabytes << " MB" << std::endl;
        
        sleep(1); 
    }

    return 0;
}