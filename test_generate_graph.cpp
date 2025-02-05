#include "performance_profile.hpp"

#include <vector>

struct gg_fixture : profiler::base_fixture<100,10> {
    gg_fixture() 
        : data( 100, 1 ) {
    } 

    std::vector<int> data;
};

PROFILE( increment, gg, gg_fixture, { 

    START_TIMER

    for ( auto x : fx.data ) {

        x++;
    }
    END_TIMER
})

PROFILE( triple, gg, gg_fixture, { 

    START_TIMER

    for ( auto x : fx.data ) {

        x *= 3;
    }
    END_TIMER
}) 

GENERATE_GRAPH( gg )