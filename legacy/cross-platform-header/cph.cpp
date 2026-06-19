//
// Created by Alp Bolukbasi on 17.12.25.
//
#ifdef __APPLE__
#include "cph.h"

#include <mach/mach.h>

double System::getMemoryUsage() {
    vm_statistics64_data_t vm_stats;
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;

    // This is a direct kernel trap
    if (host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info64_t)&vm_stats, &count) == KERN_SUCCESS) {
        // Calculations using page sizes (very low level!)
        return (double)vm_stats.active_count * PAGE_SIZE;
    }
    return -1;
}
#endif