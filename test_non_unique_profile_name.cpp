#include "performance_profile.hpp"

struct nupn_fixture : profiler::base_fixture<1,1> {

    nupn_fixture() : counter(0) {
    }

    size_t counter;
};

PROFILE_AVG( use_macro, count_to_200, nupn_fixture, {

    START_TIMER
    for ( size_t i = 0; i < 200; ++i )
        fx.counter++;
    END_TIMER
})

PROFILE_AVG( use_macro, count_to_500, nupn_fixture, {

    START_TIMER
    for ( size_t i = 0; i < 500; ++i )
        fx.counter++;
    END_TIMER
})