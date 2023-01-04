#pragma once

#ifdef ENABLE_RUNTIME_ALGORITHM

#define RUNTIME_CONSTEXPR

#else

#define RUNTIME_CONSTEXPR constexpr

#endif