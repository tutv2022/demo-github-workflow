# Core library (shared modules used by the app and optional tests)
add_library(demo_core
    config_loader.cpp
    crash_bugs.cpp
    string_utils.cpp
    user_manager.cpp
)

target_include_directories(demo_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(demo_core
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# Main application
add_executable(demo_app main.cpp)

target_link_libraries(demo_app
    PRIVATE
        demo_core
)

# Install rules (optional, useful for packaging demos)
install(TARGETS demo_app RUNTIME DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/config/settings.conf DESTINATION etc/demo_app)
