#pragma once

#include <fmt/format.h>

#ifdef ENABLE_RUNTIME_ALGORITHM

#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

void enableDebugLogging() { spdlog::set_level(spdlog::level::debug); }

#define logd(...) spdlog::debug(__VA_ARGS__)
#define logi(...) spdlog::info(__VA_ARGS__)

#else

constexpr void enableDebugLogging() {}
#define logd(...)
#define logi(...)

#endif
