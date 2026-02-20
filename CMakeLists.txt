cmake_minimum_required(VERSION 3.16)
project(SolJumper)

# --- 1. PROJECT & COMPILER CONFIG ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
# --- 2. VENDORED DEPENDENCIES (Build from source) ---
# We add these first so their targets (SDL3::SDL3, etc.) are available later
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

set(SDLTTF_VENDORED ON)
set(SDLTTF_SAMPLES OFF)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

# Ensure SDL_image uses the vendored setup if available

set(SDLIMG_VENDORED ON)
set(SDLIMG_SAMPLES OFF)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# --- 3. SOURCE DISCOVERY ---
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- 4. CREATE EXECUTABLE ---
# CRITICAL: This must happen BEFORE any target_... commands
add_executable(soljumper ${SOURCES})

# --- 5. TARGET INCLUDES ---
# Point to your source code and external header-only libs
target_include_directories(soljumper PRIVATE 
    "src" 
    "external/asio/include"
)

# --- 6. TARGET DEFINITIONS & OPTIONS ---
target_compile_definitions(soljumper PRIVATE ASIO_STANDALONE)

# Hide console ONLY on Windows
if(WIN32)
    target_link_options(soljumper PRIVATE -mwindows)
endif()

# --- 7. LINKING ---
# Shared libraries for all platforms
target_link_libraries(soljumper PRIVATE 
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
)

# Platform-specific "System" Libraries
if(WIN32)
    target_link_libraries(soljumper PRIVATE 
        -Wl,-Bstatic 
        -lssl -lcrypto
        -static-libgcc -static-libstdc++
        
        -Wl,-Bdynamic 
        -lwinpthread
        ws2_32 crypt32 secur32 iphlpapi user32 gdi32 shell32 kernel32
    )
else()
    # Linux setup (Standard)
    # Most Linux distros handle SSL/Crypto via the system, 
    # but we can try to link them as targets or flags.
    find_package(OpenSSL REQUIRED)
    find_package(Threads REQUIRED)
    
    target_link_libraries(soljumper PRIVATE 
        OpenSSL::SSL
        OpenSSL::Crypto
        Threads::Threads
        m # The math library
        dl # The dynamic linking library
    )
endif()

# --- 8. POST-BUILD STEPS ---
# Assets are needed on both, but DLLs are Windows-only
add_custom_command(TARGET soljumper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:soljumper>/assets"
)

if(WIN32)
    add_custom_command(TARGET soljumper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/mingw64/bin/libwinpthread-1.dll"
        "$<TARGET_FILE_DIR:soljumper>/"
    )
endif()