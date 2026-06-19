#include "promon/app/application.hpp"

#include "cli_renderer.hpp"
#include "promon/core/rate.hpp"
#include "promon/core/snapshot.hpp"
#include "promon/ui/render_model.hpp"
#include "promon/ui/snapshot_presenter.hpp"

#if defined(__APPLE__)
#include "promon/platform/macos/mach_memory.hpp"
#include "promon/platform/macos/vmstat.hpp"
#elif defined(__linux__)
#include "promon/platform/linux/memory.hpp"
#include "promon/platform/linux/vmstat.hpp"
#endif

#include <chrono>
#include <iostream>
#include <optional>
#include <thread>
#include <utility>

namespace promon::app {

Application::Application(Options options)
    : options_(std::move(options)) {}

namespace {

Snapshot collect_snapshot() {
    Snapshot snapshot;
    snapshot.timestamp = std::chrono::steady_clock::now();

#if defined(__APPLE__)
    snapshot.memory = macos_backend::read_system_memory();
    snapshot.vmstat = macos_backend::read_vmstat();
#elif defined(__linux__)
    snapshot.memory = linux_backend::read_system_memory();
    snapshot.vmstat = linux_backend::read_vmstat();
#endif

    return snapshot;
}

double elapsed_seconds_between(const Snapshot& previous, const Snapshot& current) {
    const auto elapsed = current.timestamp - previous.timestamp;
    return std::chrono::duration<double>(elapsed).count();
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

    promon::ui::RenderOptions render_options;
    render_options.verbose = options_.verbose;
    render_options.raw_values = options_.raw_values;
    render_options.color = options_.color;

    promon::ui::cli::CliRenderer renderer;

    if (options_.once) {
        const auto snapshot = collect_snapshot();
        const auto document = promon::ui::present_snapshot(snapshot);
        renderer.render(document, render_options);
        return 0;
    }

    const int interval = options_.watch_interval_seconds > 0
        ? options_.watch_interval_seconds
        : 1;

    std::optional<Snapshot> previous_snapshot;

    while (true) {
        auto current_snapshot = collect_snapshot();

        if (previous_snapshot) {
            const double elapsed_seconds = elapsed_seconds_between(*previous_snapshot, current_snapshot);
            current_snapshot.vmstat_rate = compute_vmstat_rate(
                previous_snapshot->vmstat,
                current_snapshot.vmstat,
                elapsed_seconds
            );
        }

        if (options_.clear_screen) {
            std::cout << "\033[2J\033[H";
        }

        const auto document = promon::ui::present_snapshot(current_snapshot);
        renderer.render(document, render_options);

        previous_snapshot = current_snapshot;

        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }

    return 0;
}

} // namespace promon::app
