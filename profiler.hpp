#include <string>

namespace profiler {    
    
    template<typename Fixture, typename Callable>
    double iterate_once( Fixture& fx, Callable ca ) {

        using clock = std::chrono::high_resolution_clock;

        double time{};

        clock::time_point start_time;
        clock::time_point end_time;
        
        ca( fx, start_time, end_time );

        time = std::chrono::duration<double, std::micro>( end_time - start_time ).count();

        return time;
    }

    template<typename Fixture, typename Callable>
    void handle_profile( const std::string& profile_name, const std::string& group_name, Callable ca ) {

        std::vector<std::vector<double>> results;
        results.resize( Fixture::runs_ );

        for ( auto& run: results ) {

            run.reserve( Fixture::iterations_ );

            Fixture fx;
        
            for ( size_t i = 0; i < Fixture::iterations_; ++i ) {
                double time = iterate_once( fx, ca );
                std::cout << time << std::endl;
                run.push_back( time );
            }
        }

        std::vector<double> average_times;
        average_times.reserve( Fixture::iterations_ );

        for ( size_t i = 0; i < Fixture::iterations_; ++i ) {

            std::cout << "calculating average times" << std::endl;
        
            average_times.push_back(
                std::accumulate( results.begin(), results.end(), 0.0,
                    [i]( double sum, const std::vector<double>& vec ) {
                        return sum + vec[ i ];
                    }) / results.size()
            );

            std::cout << average_times[ i ] << std::endl;
        }

        profile_manager::instance().add_result( profile_name, group_name, average_times );

        std::cout << "finished handling profile" << std::endl;
    }

} // profiler