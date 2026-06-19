#include "promon/app/application.hpp"

#include "cli_renderer.hpp"
#include "promon/core/snapshot.hpp"

#if defined(__APPLE__)
#include "promon/platform/macos/mach_memory.hpp"
#elif defined(__linux__)
#include "promon/platform/linux/memory.hpp"
#endif

#include <chrono>
#include <thread>

namespace promon::app {

Application::Application(Options options)
    : options_(std::move(options)) {}

namespace {

Snapshot collect_snapshot() {
    Snapshot snapshot;
    snapshot.timestamp = std::chrono::steady_clock::now();

#if defined(__APPLE__)
    snapshot.memory = macos_backend::read_system_memory();
#elif defined(__linux__)
    snapshot.memory = linux_backend::read_system_memory();
#endif

    return snapshot;
}

} // namespace

int Application::run() {
    if (options_.frontend == Frontend::Qt) {
        return 1;
    }

    if (options_.frontend == Frontend::Tui) {
        // Future: start TUI frontend here.
        // For v0, fall back to CLI renderer.
    }

    promon::ui::cli::CliRenderer renderer;

    if (options_.once) {
        const auto snapshot = collect_snapshot();
        renderer.render(snapshot);
        return 0;
    }

    const int interval = options_.watch_interval_seconds > 0
        ? options_.watch_interval_seconds
        : 1;

    while (true) {
        const auto snapshot = collect_snapshot();
        renderer.render(snapshot);
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }

    return 0;
}

} // namespace promon::app
