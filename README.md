# Performance Profiler

Easy-to-use library for pofiling C++.

Include the header file:

```cpp
#include <performance_profile.hpp>

Define a fixutre to use in the profile.

```cpp
struct f: profiler::fixture<100, 10> {
  f() : ...

  [ variables ]
}

```cpp
PROFILE( profile_name, group_name, fixture, { code_to_profile })

