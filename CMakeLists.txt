cmake_minimum_required(VERSION 3.22)

project(listro CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch FTXUI =================================================================
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(ftxui
    GIT_REPOSITORY  https://github.com/arthursonzogni/ftxui.git
    GIT_TAG	    v6.0.0
    GIT_PROGRESS    TRUE
    GIT_SHALLOW	    TRUE
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)
# =============================================================================

# Link sqlite3
add_library(sqlite3 STATIC third_party/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC third_party/sqlite)

set(SOURCES
    src/main.cpp
    src/task.cpp
    src/listro.cpp
)

add_executable(listro ${SOURCES})
target_include_directories(listro PRIVATE src)

target_link_libraries(listro
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE sqlite3
    PRIVATE ftxui::component
)
