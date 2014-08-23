#ifndef XGS_TIME_HPP
#define XGS_TIME_HPP

#include <chrono>

// One second in nanoseconds
#define ONE_SECOND (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)))

namespace xgs {
    
    // std::chrono typedefs
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> HiResTime;
    typedef std::chrono::nanoseconds HiResDuration;
    typedef std::chrono::high_resolution_clock HiResClock;
    
} // namespace xgs

#endif // XGS_TIME_HPP
