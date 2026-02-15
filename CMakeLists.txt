cmake_minimum_required(VERSION 3.16)
project(SolJumper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# 2. Add SDL3 & SDL_ttf (These will still produce DLLs)
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
set(SDLTTF_VENDORED ON)
set(SDLTTF_SAMPLES OFF)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# 3. Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# 4. Create Executable
add_executable(soljumper ${SOURCES})

# 5. Tell the code we are using Static Curl
target_compile_definitions(soljumper PRIVATE CURL_STATICLIB)

# 6. Link Everything (Order is Critical)
target_link_libraries(soljumper PRIVATE 
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    
    -Wl,-Bstatic 
    -lcurl 
    -lnghttp2 
    -lssl 
    -lcrypto 
    -lssh2
    # --- ADD THESE TWO ---
    -lzstd
    -lpsl
    # ---------------------
    -lz 
    -lbrotlidec 
    -lbrotlicommon 
    -lidn2 
    -lunistring 
    -liconv
    -lstdc++ 
    -lpthread 
    -lwinpthread
    -lgcc
    -lgcc_eh
    
    -Wl,-Bdynamic 
    ws2_32 
    wldap32 
    crypt32 
    normaliz
    bcrypt
    shlwapi
    gdi32
    user32
    kernel32
)

#target_link_options(soljumper PRIVATE -mwindows)
target_include_directories(soljumper PRIVATE src)
target_include_directories(soljumper PRIVATE /mingw64/include)

if(WIN32)
    add_custom_command(TARGET soljumper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:soljumper>/assets"
    )
endif()