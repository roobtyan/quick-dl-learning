#pragma once

#include <absl/time/time.h>
#include <absl/status/status.h>
#include <string>

namespace roobtyan {
    std::string generate_uuid();

    absl::Status string_to_time(const std::string &str, absl::Time *time);

    absl::Status time_to_string(absl::Time time, std::string *str);

    absl::Time get_current_time();

    absl::Time get_current_time_str_only_day();

    absl::Time get_time_only_day(absl::Time time);

    absl::Time get_time_only_day(const std::string &str);

    std::string get_current_time_str();

    std::string get_time_str_with_offset(int offset);

    absl::Time string_to_time_only_day(const std::string &str);
}