#include "promon/platform/linux/procfs/reader.hpp"

#include <cctype>
#include <fstream>
#include <sstream>

namespace promon::linux_backend::procfs {

std::optional<std::string> read_file(const std::filesystem::path& path) {
    std::ifstream file(path);

    if (!file) {
        return std::nullopt;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<std::string> read_lines(const std::filesystem::path& path) {
    std::vector<std::string> lines;
    std::ifstream file(path);

    if (!file) {
        return lines;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::vector<int> list_pids(const std::filesystem::path& proc_root) {
    std::vector<int> pids;

    std::error_code ec;
    for (const auto& entry : std::filesystem::directory_iterator(proc_root, ec)) {
        if (ec || !entry.is_directory()) {
            continue;
        }

        const auto name = entry.path().filename().string();

        bool all_digits = !name.empty();
        for (const char ch : name) {
            if (!std::isdigit(static_cast<unsigned char>(ch))) {
                all_digits = false;
                break;
            }
        }

        if (!all_digits) {
            continue;
        }

        try {
            pids.push_back(std::stoi(name));
        } catch (...) {
            continue;
        }
    }

    return pids;
}

} // namespace promon::linux_backend::procfs
