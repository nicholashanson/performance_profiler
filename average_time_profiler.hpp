#ifndef PROFILE_AVG_HPP
#define PROFILE_AVG_HPP

#include <string>

namespace profiler {
    
    template<typename Fixture, typename Callable>
    double run_profile( Fixture& fx, Callable ca ) {

        using clock = std::chrono::high_resolution_clock;

        double total_time{};

        for ( size_t j = 0; j < Fixture::iterations_; ++j ) {

            clock::time_point start_time;
            clock::time_point end_time;

            ca( fx, start_time, end_time );

            total_time += std::chrono::duration<double, std::micro>( end_time - start_time ).count();
        }

        double avg_time = total_time / Fixture::iterations_;

        return avg_time;
    }

    template<typename Fixture, typename Callable>
    double execute_profile( Callable ca ) {
        double total_time{};

        for ( size_t i = 0; i < Fixture::runs_; ++i ) {

            std::cout << "Executing run " << i << "..." << std::endl;

            Fixture fx;
            total_time += run_profile( fx, ca );
        }

        double avg_time = total_time / Fixture::runs_;

        return avg_time;
    }

    template<typename Fixture, typename Callable>
    void handle_profile_avg( const std::string& profile_name, const std::string& group_name, Callable ca ) {

        std::cout << "Running " << profile_name << "..." << std::endl;

        double avg_time = execute_profile<Fixture>( ca );

        profile_manager::instance().add_result( profile_name, group_name, avg_time );
    }

} // profiler

#endif