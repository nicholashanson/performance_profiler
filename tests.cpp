#include "performance_profile.hpp"

struct f : profiler::base_fixture<1,1> {

    f() : counter(0) {
    }

    size_t counter;
};

PROFILE_AVG( use_macro, count_to_1000, f, {

    START_TIMER
    for ( size_t i = 0; i < 1000; ++i )
        fx.counter++;
    END_TIMER
})

const bool profile_initialized = profiler::profile_avg<f>(
    "use_function_template",
    "count_to_100",
    []( auto& fx, auto& start_time, auto& end_time ) {
        size_t c{};
        START_TIMER
        for ( size_t i = 0; i < 1000; ++i )
            fx.counter;
        END_TIMER
    }
);