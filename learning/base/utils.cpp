#include <utils.h>
#include <random>

namespace roobtyan {
std::string generate_uuid() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 9);

  return std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) +
         std::to_string(dis(gen));
}

absl::Status string_to_time(const std::string& str, absl::Time* time) {
  std::string err;
  const bool success = absl::ParseTime(absl::RFC3339_sec, str, time, &err);
  return success ? absl::OkStatus() : absl::InvalidArgumentError(err);
}

absl::Status time_to_string(const absl::Time time, std::string* str) {
  absl::TimeZone local;
  absl::LoadTimeZone("Asia/Shanghai", &local);
  *str = absl::FormatTime(absl::RFC3339_sec, time, local);
  return absl::OkStatus();
}

absl::Time get_current_time() { return absl::Now(); }

absl::Time get_current_time_str_only_day() {
  // 仅获取今天的日期
  absl::TimeZone local;
  absl::LoadTimeZone("Asia/Shanghai", &local);
  const auto now = absl::Now();
  const auto today = absl::ToCivilDay(now, local);
  return absl::FromCivil(today, local);
}

absl::Time get_time_only_day(const absl::Time time) {
  absl::TimeZone local;
  absl::LoadTimeZone("Asia/Shanghai", &local);
  const auto today = absl::ToCivilDay(time, local);
  return absl::FromCivil(today, local);
}

absl::Time get_time_only_day(const std::string& str) {
  absl::Time time;
  std::string err;
  if (const auto status = string_to_time(str, &time); !status.ok()) {
    return {};
  }
  return get_time_only_day(time);
}

std::string get_current_time_str() {
  absl::TimeZone local;
  absl::LoadTimeZone("Asia/Shanghai", &local);
  return absl::FormatTime(absl::RFC3339_sec, absl::Now(), local);
}

std::string get_time_str_with_offset(const int offset) {
  absl::TimeZone local;
  absl::LoadTimeZone("Asia/Shanghai", &local);
  return absl::FormatTime(absl::RFC3339_sec, absl::Now() + absl::Hours(offset * 24), local);
}

absl::Time string_to_time_only_day(const std::string& str) {
  absl::Time time;
  std::string err;
  absl::ParseTime("%Y-%m-%d%", str, &time, &err);
  return time;
}
}