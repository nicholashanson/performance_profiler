#ifndef GENERATE_GRAPH_HPP
#define GENERATE_GRAPH_HPP

#include <string>
#include <vector>
#include <fstream>

#include "profile_manager.hpp"

namespace profiler {

    inline void generate_python_script( const std::vector<std::tuple<std::string, std::string, std::vector<double>>>& results ) {

        std::ofstream python_script( "temp_script.py" );

        python_script << "import seaborn as sns" << std::endl;

        python_script << "sns.set( style = 'whitegrid' )" << std::endl;

        python_script << "import numpy as np" << std::endl;
        python_script << "import matplotlib.pyplot as plt" << std::endl;
        python_script << "import os" << std::endl;

        python_script << "x = np.array( [ x for x in range( 1, " << std::get<2>( results[ 0 ] ).size() + 1 << " ) ] )" << std::endl;

        for ( auto result: results ) {

            const std::string& profile_name = std::get<0>( result );
            const std::string& group_name = std::get<1>( result );
            const std::vector<double>& avg_times = std::get<2>( result );

            python_script << profile_name << "= [ ";

            for ( size_t i = 0; i < avg_times.size() - 1; ++i ) 
                python_script << avg_times[ i ] << ", ";

            python_script << avg_times[ avg_times.size() - 1 ] << " ]" << std::endl;

            python_script << "plt.plot( x, " << profile_name << " , label = '" << profile_name << "' )" << std::endl;
        }

        python_script << "plt.legend()" << std::endl;

        python_script << "os.makedirs( 'performance_profiling/graphs', exist_ok = True )" << std::endl;

        python_script << "plt.savefig( 'performance_profiling/graphs/performance_" << std::get<1>( results[ 0 ] ) << ".png' )";
        python_script.close();

        int result = system("py temp_script.py");
    }

    inline void generate_graph( const std::string& group_name ) {

        std::vector<std::tuple<std::string, std::string, std::vector<double>>> results;

        results = profile_manager::instance().get_avg_times( group_name );

        generate_python_script( results );
    }

} // profiler

#endif