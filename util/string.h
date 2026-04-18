#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace semita::string {
    [[nodiscard]] inline std::vector<std::string_view> split_sv(const std::string& str, const char delimiter) {
        std::vector<std::string_view> parts;
        std::string_view sv = str;
        size_t pos = 0;

        while ((pos = sv.find(delimiter)) != std::string_view::npos) {
            parts.push_back(sv.substr(0, pos));
            sv.remove_prefix(pos + 1);
        }

        parts.push_back(sv.substr(0, sv.size()));
        return parts;
    }

    [[nodiscard]] inline std::vector<std::string> split(const std::string& str, const char delimiter) {
        std::vector<std::string> parts;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != std::string::npos) {
            parts.push_back(str.substr(start, end - start));
            start = end + 1;
            end = str.find(delimiter, start);
        }

        parts.push_back(str.substr(start));
        return parts;
    }

    [[nodiscard]] inline bool iequals(const std::string_view left, const std::string_view right) {
        if (left.size() != right.size()) {
            return false;
        }

        return std::ranges::equal(left, right, [](const char lhs, const char rhs) {
            return std::tolower(static_cast<unsigned char>(lhs)) == std::tolower(static_cast<unsigned char>(rhs));
        });
    }
}
