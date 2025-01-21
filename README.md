# Performance Profiler

Easy-to-use library for pofiling C++.

Include the header file:

```cpp
#include <performance_profile.hpp>
```

Define a fixutre to use in the profile.

```cpp
struct f: profiler::fixture<100, 10> {
  f() : ...

  [ variables ]
}
```

The fixture inherits from the base fixture profiler::fixture.

<100, 10> indicates that the profile should be run for a total 10 runs of 100 iterations each.

The constructor of the fixture will be called before each run, so any set-up should be included here.

[ varaibles ] are any variables that need to be accessed by profiled code. They persist for the duration of a run.
They can be accessed inside the profiled code with fx.<variable>.

```cpp
PROFILE( profile_name, group_name, fixture, { code_to_profile })
```

