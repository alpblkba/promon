#pragma once

#include <string>
#include <vector>

namespace promon::app {

enum class Frontend {
    Cli,
    Tui,
    Qt
};

enum class OutputFormat {
    Human,
    Json,
    Markdown
};

enum class Section {
    System,
    Memory,
    Cpu,
    Vm,
    Process,
    Thread,
    Scheduler,
    Diagnostics
};

struct Options {
    Frontend frontend = Frontend::Cli;
    OutputFormat output_format = OutputFormat::Human;

    bool once = true;
    bool verbose = false;
    bool raw_values = false;
    bool color = true;
    bool clear_screen = true;
    int watch_interval_seconds = 0;

    std::vector<Section> sections = {
        Section::System,
        Section::Memory
    };
};

Options parse_options(int argc, char** argv);

} // namespace promon::app
