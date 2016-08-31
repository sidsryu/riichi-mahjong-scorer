// CppUTest: Confilicts with operator new macros (STL!)
// https://cpputest.github.io/manual.html#memory_leak_detection

// include stl
#include <set>
#include <map>
#include <array>
#include <memory>
#include <functional>

// cpputest MemoryLeakDetectorNewMacros
#include "CppUTest/MemoryLeakDetectorNewMacros.h"
