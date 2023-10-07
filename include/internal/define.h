#ifndef VEC_DEFINE_H
#define VEC_DEFINE_H
#ifndef NO_UNIQUE_ADDRESS

#if _MSC_VER && !__INTEL_COMPILER
    #define NO_UNIQUE_ADDRESS  [[msvc::no_unique_address]]
#else
    #define NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif
#endif
#endif
