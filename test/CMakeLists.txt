project(test)
project(type)
project(iterator)
project(exception_safety)
add_executable(test main.cpp "utils /none_default_constructible.cpp" "utils /none_default_constructible.h" "utils /throwing_default_constructor.cpp" "utils /throwing_default_constructor.h")
add_executable(type type/main.cpp)
add_executable(iterator iterator/main.cpp)
add_executable(exception_safety exception_safety/main.cpp)
enable_testing()
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${GTEST_LIBRARIES})
target_link_libraries(type PRIVATE ${GTEST_LIBRARIES})
target_link_libraries(iterator PRIVATE ${GTEST_LIBRARIES})
target_link_libraries(exception_safety PRIVATE ${GTEST_LIBRARIES})
ADD_TEST(test1 test)
ADD_TEST(test2 type)
ADD_TEST(test3 iterator)
ADD_TEST(test4 exception_safety)