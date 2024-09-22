#pragma once

#include <fmt/format.h>

#ifdef ENABLE_RUNTIME_ALGORITHM

#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#define logd(...) spdlog::debug(__VA_ARGS__)
#define logi(...) spdlog::info(__VA_ARGS__)

#else

#define logd(...)
#define logi(...)

#endif
