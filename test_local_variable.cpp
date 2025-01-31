#include "performance_profile.hpp"

struct lv_fixture : profiler::base_fixture<1,1> {

    lv_fixture() : counter(0) {
    }

    size_t counter;
};

PROFILE_AVG( use_macro, count_to_1000, lv_fixture, {

    START_TIMER
    for ( size_t i = 0; i < 1000; ++i )
        fx.counter++;
    END_TIMER
})

const bool profile_initialized = profiler::profile_avg<lv_fixture>(
    "use_function_template",
    "count_to_1000",
    []( auto& fx, auto& start_time, auto& end_time ) {
        START_TIMER
        for ( size_t i = 0; i < 1000; ++i )
            fx.counter;
        END_TIMER
    }
);