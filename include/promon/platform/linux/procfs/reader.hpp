#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace promon::linux_backend::procfs {

std::optional<std::string> read_file(const std::filesystem::path& path);
std::vector<std::string> read_lines(const std::filesystem::path& path);
std::vector<int> list_pids(const std::filesystem::path& proc_root = "/proc");

} // namespace promon::linux_backend::procfs
