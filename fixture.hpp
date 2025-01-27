#ifndef FIXTURE_HPP
#define FIXTURE_HPP

namespace profiler {    
    
    template<size_t iterations = 1, size_t runs = 1>
    struct fixture {

        static size_t iterations_;
        static size_t runs_;
    };

    template<size_t iterations, size_t runs>
    size_t fixture<iterations, runs>::iterations_ = iterations;

    template<size_t iterations, size_t runs>
    size_t fixture<iterations, runs>::runs_ = runs;

} // profiler

#endif