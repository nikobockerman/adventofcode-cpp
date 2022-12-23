#pragma once

#include <functional>
#include <istream>

enum class Type { Rock, Paper, Scissors };

auto sumScore(std::istream &input,
              const std::function<Type(Type, char)> &parseMe) -> unsigned;
