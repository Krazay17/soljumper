cmake_minimum_required(VERSION 3.16)
project(SolJumper)

# Use C++17 or C++20 for your Vec2 and string logic
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Force DLLs and EXE into the same folder (bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# 2. Add SDL3 as a subproject
# EXCLUDE_FROM_ALL means it won't build SDL demos/tests, just the library
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# 3. Add SDL_ttf
set(SDLTTF_VENDORED ON)
set(SDLTTF_SAMPLES OFF)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

# 4. Find all your source files automatically
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
)

# 5. Create the Executable
add_executable(soljumper ${SOURCES})
# 6. Link Everything
# Notice we don't need paths! CMake knows where the subprojects are.
target_link_libraries(soljumper PRIVATE 
    SDL3::SDL3 
    SDL3_ttf::SDL3_ttf
    curl
)

# 7. Include your own 'src' folder so #include "math/Vec2.h" works
target_include_directories(soljumper PRIVATE src)

# This creates a folder link (shortcut) so the EXE can see the assets
if(WIN32)
    # On Windows, we create a directory junction
    add_custom_command(TARGET soljumper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:soljumper>/assets"
    )
endif()
