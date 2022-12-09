cmake_minimum_required(VERSION 3.21)
project(SfmlPrac LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
if(WIN32)
    set(BUILD_SHARED_LIBS FALSE)
endif()

find_package(SFML 2 COMPONENTS audio graphics window system network)

if(NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif()

add_subdirectory(third_party/boxer)

add_executable(SfmlPrac
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
)
target_link_libraries(SfmlPrac PRIVATE sfml-graphics sfml-audio Boxer)
target_compile_features(SfmlPrac PRIVATE cxx_std_20)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET SfmlPrac POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:SfmlPrac> $<TARGET_FILE_DIR:SfmlPrac> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS SfmlPrac)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
