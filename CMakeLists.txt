cmake_minimum_required(VERSION 3.20)

project(promon
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(promon
    src/main.cpp

    src/core/snapshot.cpp
    src/core/format.cpp

    src/app/options.cpp
    src/app/application.cpp

    src/diagnostics/memory_pressure.cpp
    src/diagnostics/scheduler_pressure.cpp
    src/diagnostics/io_pressure.cpp

    ui/cli/cli_renderer.cpp
)

target_include_directories(promon PRIVATE
    include
    ui/cli
)

if(APPLE)
    target_sources(promon PRIVATE
        src/platform/macos/mach_memory.cpp
        src/platform/macos/process.cpp
        src/platform/macos/thread.cpp

        src/platform/macos/mach/host_memory.cpp
        src/platform/macos/mach/cpu_load.cpp
        src/platform/macos/mach/thread_info.cpp

        src/platform/macos/sysctl/hw_memsize.cpp
        src/platform/macos/sysctl/loadavg.cpp
        src/platform/macos/sysctl/uptime.cpp
        src/platform/macos/sysctl/procargs.cpp

        src/platform/macos/libproc/process_list.cpp
        src/platform/macos/libproc/process_info.cpp
        src/platform/macos/libproc/process_io.cpp
    )

    target_link_libraries(promon PRIVATE
        "-framework CoreFoundation"
    )
elseif(UNIX)
    target_sources(promon PRIVATE
        src/platform/linux/memory.cpp
        src/platform/linux/vmstat.cpp
        src/platform/linux/cpu.cpp
        src/platform/linux/process.cpp
        src/platform/linux/thread.cpp
        src/platform/linux/scheduler.cpp

        src/platform/linux/procfs/reader.cpp
        src/platform/linux/procfs/meminfo.cpp
        src/platform/linux/procfs/vmstat.cpp
        src/platform/linux/procfs/stat.cpp
        src/platform/linux/procfs/loadavg.cpp
        src/platform/linux/procfs/uptime.cpp
        src/platform/linux/procfs/pid_status.cpp
        src/platform/linux/procfs/pid_stat.cpp
        src/platform/linux/procfs/pid_io.cpp
        src/platform/linux/procfs/pid_cmdline.cpp
        src/platform/linux/procfs/task.cpp
        src/platform/linux/procfs/sched.cpp
        src/platform/linux/procfs/pressure.cpp
    )
endif()

target_compile_options(promon PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
