#include "promon/app/options.hpp"

#include <cstdlib>
#include <string_view>

namespace promon::app {

namespace {

Section parse_section(std::string_view value) {
    if (value == "system") {
        return Section::System;
    }
    if (value == "memory") {
        return Section::Memory;
    }
    if (value == "cpu") {
        return Section::Cpu;
    }
    if (value == "vm") {
        return Section::Vm;
    }
    if (value == "process") {
        return Section::Process;
    }
    if (value == "thread") {
        return Section::Thread;
    }
    if (value == "scheduler") {
        return Section::Scheduler;
    }
    if (value == "diagnostics") {
        return Section::Diagnostics;
    }

    return Section::System;
}

} // namespace

Options parse_options(int argc, char** argv) {
    Options options;

    for (int i = 1; i < argc; ++i) {
        const std::string_view arg(argv[i]);

        if (arg == "--once") {
            options.once = true;
            options.watch_interval_seconds = 0;
            continue;
        }

        if (arg == "--watch" && i + 1 < argc) {
            options.once = false;
            options.watch_interval_seconds = std::atoi(argv[++i]);
            continue;
        }

        if (arg == "--tui") {
            options.frontend = Frontend::Tui;
            continue;
        }

        if (arg == "--cli") {
            options.frontend = Frontend::Cli;
            continue;
        }

        if (arg == "--qt") {
            options.frontend = Frontend::Qt;
            continue;
        }

        if (arg == "--json") {
            options.output_format = OutputFormat::Json;
            continue;
        }

        if (arg == "--markdown") {
            options.output_format = OutputFormat::Markdown;
            continue;
        }

        if (arg == "--verbose" || arg == "-v") {
            options.verbose = true;
            continue;
        }

        if (arg == "--raw") {
            options.raw_values = true;
            continue;
        }

        if (arg == "--no-color") {
            options.color = false;
            continue;
        }

        if (arg == "--no-clear") {
            options.clear_screen = false;
            continue;
        }

        if (arg == "--section" && i + 1 < argc) {
            options.sections.clear();
            options.sections.push_back(parse_section(argv[++i]));
            continue;
        }
    }

    return options;
}

} // namespace promon::app
