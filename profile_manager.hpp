#ifndef PROFILE_MANAGER_HPP
#define PROFILE_MANAGER_HPP

#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

namespace profiler {

    class profile_manager {
    public:
        static profile_manager& instance() {
            static profile_manager instance;
            return instance;
        }

        void add_result( const std::string& profile_name, const std::string& group_name, double avg_time_ ) {
            avg_time.emplace_back( profile_name, group_name, avg_time_ );
            group_names.insert( group_name );
        }

        void add_result( const std::string& profile_name, const std::string& group_name, std::vector<double> avg_times_ ) {
            avg_times.emplace_back( profile_name, group_name, avg_times_ );
            group_names.insert( group_name );
        }

        void print_results() const {

            for (const auto& group_name_ : group_names) {
                std::cout << group_name_ << ":\n";

                for (const auto& [ profile_name, group_name, avg_time_ ] : avg_time | std::views::filter([ & ]( const auto& result ) {
                        return std::get<1>( result ) == group_name_;
                    })) {

                        std::string unit = "us";

                        double scaled_time = avg_time_;

                        if ( avg_time_ >= 100'000 ) {       // more than 100 milliseconds
                            unit = "s";
                            scaled_time /= 1'000'000.0;     // convert to seconds
                        } else if ( avg_time_ >= 100 ) {    // more than 100 microseconds but less than 100 milliseconds
                            unit = "ms";
                            scaled_time /= 1'000.0;         // convert to milliseconds
                        }

                        std::cout << "{ " << std::fixed << std::setprecision(2) << scaled_time <<  " " << unit << " } " << profile_name << "\n";
                }

                std::cout << std::endl;
            }
        }

        std::vector<std::tuple<std::string, std::string, double>> get_avg_time( const std::string& group_name ) {

            std::vector<std::tuple<std::string, std::string, double>> group_results;
            
            for ( auto result: avg_time ) {

                if ( std::get<1>( result ) == group_name )
                    group_results.push_back( result );
            }

            return group_results;
        } 

        std::vector<std::tuple<std::string, std::string, std::vector<double>>> get_avg_times( const std::string& group_name ) {

            std::vector<std::tuple<std::string, std::string, std::vector<double>>> group_results;

            for ( auto result: avg_times ) {

                if ( std::get<1>( result ) == group_name )
                    group_results.push_back( result );
            }

            return group_results;
        }

    private:
        std::vector<std::tuple<std::string, std::string, double>> avg_time;
        std::vector<std::tuple<std::string, std::string, std::vector<double>>> avg_times;
        std::set<std::string> group_names;
    };

} // profiler

#endif