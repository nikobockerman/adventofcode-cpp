#include "test.hpp"

#include <spdlog/common.h>
#include <spdlog/spdlog.h>

void enableDebugLogging() { spdlog::set_level(spdlog::level::debug); }
