// CppUTest: Confilicts with operator new macros (STL!)
// https://cpputest.github.io/manual.html#memory_leak_detection

// include stl
#include <utility>
#include <algorithm>
#include <functional>
#include <set>
#include <vector>
#include <array>
#include <memory>

// cpputest MemoryLeakDetectorNewMacros
#include "CppUTest/MemoryLeakDetectorNewMacros.h"
