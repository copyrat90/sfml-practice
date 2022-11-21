cmake_minimum_required(VERSION 3.21)
project(SfmlPrac LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(SfmlPrac src/main.cpp)
target_link_libraries(SfmlPrac PRIVATE sfml-graphics)
target_compile_features(SfmlPrac PRIVATE cxx_std_20)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET SfmlPrac POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SfmlPrac> $<TARGET_FILE_DIR:SfmlPrac> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS SfmlPrac)
