#ifndef PERFORMANCE_PROFILE_HPP
#define PERFORMANCE_PROFILE_HPP

#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <ranges>
#include <fstream>
#include <cstdlib>
#include <numeric>

#include "fixture.hpp"
#include "profile_manager.hpp"
#include "average_time_profiler.hpp"
#include "profiler.hpp"
#include "generate_graph.hpp"

#define START_TIMER start_time = std::chrono::high_resolution_clock::now();
#define END_TIMER end_time = std::chrono::high_resolution_clock::now();

namespace profiler {

    template<typename Fixture, typename Callable>
    bool profile_avg( const std::string& profile_name, const std::string& group_name, Callable&& ca ) {

        handle_profile_avg<Fixture>( profile_name, group_name, std::forward<Callable>( ca ) );
        return true;
    }

}

#define PROFILE_AVG( profile_name, group_name, fixture, lambda_body )           \
const bool profile_name##_##group_name##_profile_init = []() {                  \
    profiler::handle_profile_avg<fixture>( #profile_name, #group_name,          \
        []( auto& fx, auto& start_time, auto& end_time ) lambda_body );         \
    return true;                                                                \
}();

#define PROFILE( profile_name, group_name, fixture, lambda_body )               \
const bool profile_name##_profile_init = []() {                                 \
    profiler::handle_profile<fixture>( #profile_name, #group_name,              \
        []( auto& fx, auto& start_time, auto& end_time ) lambda_body );         \
    return true;                                                                \
}();

#define PROFILE_BASE( profile_name, group_name, fixture, lambda_body )          \
const bool profile_name##_profile_init = []() {                                 \
    profiler::handle_profile_base<fixture>( #profile_name, #group_name,         \
        []( auto& fx, auto& start_time, auto& end_time ) lambda_body );         \
    return true;                                                                \
}();

#define PROFILE_SU( profile_name, group_name, fixture, lambda_body )            \
const bool profile_name##_profile_init = []() {                                 \
    profiler::handle_profile_su<fixture>( #profile_name, #group_name,           \
        []( auto& fx, auto& start_time, auto& end_time ) lambda_body );         \
    return true;                                                                \
}();

#define GENERATE_GRAPH( group_name )                                            \
const bool group_name##_graph_init = []() {                                     \
    profiler::generate_graph( #group_name );                                    \
    return true;                                                                \
}();

#define GENERATE_GRAPH_SU( group_name )                                         \
const bool group_name##_graph_init = []() {                                     \
    profiler::generate_graph_su( #group_name );                                 \
    return true;                                                                \
}();

#ifdef PERFORMANCE_PROFILE_MAIN

int main() {
    profiler::profile_manager::instance().print_results();

    return 0;
}

#endif

#endif
