#pragma once

#ifdef ENABLE_RUNTIME_ALGORITHM

#define RUNTIME_CONSTEXPR
#define RUNTIME_STATIC_CONSTEXPR

#else

#define RUNTIME_CONSTEXPR constexpr
#define RUNTIME_STATIC_CONSTEXPR static constexpr

#endif
