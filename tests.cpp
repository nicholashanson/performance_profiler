#include "performance_profile.hpp"

struct f : profiler::fixture<1,1> {

    f() = default;
};

PROFILE_AVG( use_macro, count_to_1000, f, {

    START_TIMER
    size_t counter{};
    for ( size_t i = 0; i < 1000; ++i )
        counter++;
    END_TIMER
})

const bool profile_initialized = profiler::profile_avg<f>(
    "use_function_template",
    "count_to_100",
    [](auto& fx, auto& start_time, auto& end_time) {
        START_TIMER
        size_t counter{};
        for ( size_t i = 0; i < 1000; ++i )
            counter++;
        END_TIMER
    }
);