#include "utils.hpp"

auto split(std::string_view str, char separator)
    -> std::vector<std::string_view> {
  std::vector<std::string_view> parts;
  auto remaining{str};
  while (!remaining.empty()) {
    auto index = remaining.find(separator);
    parts.emplace_back(remaining.substr(0, index));
    if (index == std::string_view::npos) {
      break;
    }
    remaining = remaining.substr(index + 1);
  }

  return parts;
}

auto split(const std::vector<std::string_view>& container,
           const std::function<bool(std::string_view)>& isSeparator)
    -> std::vector<std::vector<std::string_view>> {
  std::vector<std::vector<std::string_view>> result{};
  std::vector<std::string_view> current{};
  for (auto item : container) {
    if (isSeparator(item)) {
      result.emplace_back(std::move(current));
      current = std::vector<std::string_view>{};
      continue;
    }
    current.emplace_back(item);
  }
  result.emplace_back(std::move(current));
  return result;
}

auto group(const std::vector<std::string_view>& container,
           std::size_t groupSize)
    -> std::vector<std::vector<std::string_view>> {
  std::vector<std::vector<std::string_view>> result{};
  std::vector<std::string_view> current{};
  std::size_t count{};

  for (auto item : container) {
    if (count >= groupSize) {
      result.emplace_back(std::move(current));
      current = std::vector<std::string_view>{};
      count = 0;
    }
    current.emplace_back(item);
    ++count;
  }
  result.emplace_back(std::move(current));
  return result;
}
