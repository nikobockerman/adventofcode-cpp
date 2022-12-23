#pragma once

#include <istream>
#include <optional>
#include <string>

auto readLine(std::istream &stream) -> std::optional<std::string>;
