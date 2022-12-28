#pragma once

#include <functional>
#include <string_view>

enum class Type { Rock, Paper, Scissors };

auto sumScore(std::string_view input,
              const std::function<Type(Type, char)> &parseMe) -> unsigned;
