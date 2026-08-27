cmake_minimum_required(VERSION 3.16)

project(silly_tests LANGUAGES CXX)

include(CTest)
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.16.0
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

file(
    GLOB_RECURSE TEST_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp"
)

add_executable(
    game_tests
    ${TEST_SOURCES}
)

file(
    GLOB_RECURSE GAME_RULE_SOURCES
    CONFIGURE_DEPENDS
    "../main/src/game/*_game.cpp"
)

add_library(
    game_rules
    ../main/src/game/game.cpp
    ${GAME_RULE_SOURCES}
)

target_compile_features(game_rules PUBLIC cxx_std_20)

target_include_directories(
    game_rules
    PUBLIC ../main/src
)

target_link_libraries(
    game_tests
    PRIVATE
        game_rules
        Catch2::Catch2WithMain
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(game_rules PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(game_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

catch_discover_tests(
    game_tests
    DISCOVERY_MODE PRE_TEST
)
