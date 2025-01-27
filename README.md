# Performance Profiler

Easy-to-use library for pofiling C++.

## How to use:

(1) Include the header file:
```cpp
#include <performance_profile.hpp>
```
(2) Define a fixture
```cpp
struct f: profiler::fixture<100, 10> {
  f() : ...

  [ variables ]
}
```
Define a fixutre to use in the profile.

The fixture inherits from the base fixture profiler::fixture.

The template arguments <100, 10> indicates that the profile should be run for a total 10 runs of 100 iterations each.

The constructor of the fixture will be called before each run, so any set-up should be included here.

[ varaibles ] are any variables that need to be accessed by profiled code. They persist for the duration of a run.
They can be accessed inside the profiled code with fx.variable_name.

(3) Define a profile

The basic syntax for a profile:
```cpp
PROFILE( profile_name, group_name, fixture, { code_to_profile })
```
Profiles are divided into groups. A group is a kind of functionality you want to profile.

Use START_TIMER and END_TIMER to indicate the code inside the loop to be timed:
```cpp
PROFILE( profile_name, group_name, fixture, {
  run_first();
  START_TIMER
  code_to_profile();
  END_TIMER
  run_after();
})
```
This will run the profile and store the execution time for each iteration. This data can then be used to generate
a graph:
```cpp
GENERATE_GRAPH( group_name )
```
Alternatively you can use the PROFILE_AVG macro to print the average execution time across all iterations and all runs:
```cpp
PROFILE_AVG( profile_name, group_name, { code_to_profile })
```
This will output to the console:
```
group_name:
{ 0.2 s } unoptimized_func
{ 47 ms } optimized_func
```
