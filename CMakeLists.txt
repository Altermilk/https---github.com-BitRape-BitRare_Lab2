# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories for GoogleTest and GoogleMock (update with correct paths if needed)
# You can either use find_package() or link directly to the directories.
include_directories(
    ${CMAKE_SOURCE_DIR}/googletest/include
    ${CMAKE_SOURCE_DIR}/googlemock/include
)

# Add GoogleTest and GoogleMock as subdirectories if you have them inside the project
add_subdirectory(googletest)
add_subdirectory(googlemock)

# Add your executable (replace source_file with actual source files of your project)
add_executable(my_test_exe
    src/main.cpp   # Example source files
    src/test.cpp
)

# Link the executable with GoogleTest and GoogleMock
target_link_libraries(my_test_exe
    gtest
    gmock
    gtest_main
    gmock_main
)

# If you need to add unit tests
enable_testing()

# Add tests (example for GoogleTest)
add_test(NAME MyTest COMMAND my_test_exe)
