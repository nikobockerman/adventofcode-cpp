#pragma once

#ifdef ENABLE_RUNTIME_ALGORITHM

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

void enableDebugLogging() { spdlog::set_level(spdlog::level::debug); }

#define logd(...) spdlog::debug(__VA_ARGS__)

#else

constexpr void enableDebugLogging() {}
#define logd(...)

#endif
