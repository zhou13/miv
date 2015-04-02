cmake_minimum_required(VERSION 3.0)
project(miv)

find_package(Boost COMPONENTS program_options system filesystem REQUIRED)
find_package(Curses REQUIRED)

INCLUDE(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(tinfo setupterm "" HAVE_TERMINFO)
if (HAVE_TERMINFO)
    set(TERMINFO_LIBRARIES "tinfo")
endif()

set(GCC_PARAMETERS "-Wall -Wextra -std=c++1y")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_PARAMETERS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_PARAMETERS} -g3 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${GCC_PARAMETERS} -O2")

include_directories(src)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CURSES_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(
    miv_SRC
    src/action/action.hpp
    src/action/common.cpp
    src/file/file.cpp
    src/frame/frame.cpp
    src/frame/mode.hpp
    src/main.cpp
    src/miv/controller.cpp
    src/miv/input.hpp
    src/miv/miv.cpp
    src/miv/screen.hpp
    src/ui/ncurses.cpp
    src/ui/ui.cpp
    src/utils/common.hpp
    src/xarray/xarray.cpp
)

add_executable(
    miv
    ${miv_SRC}
)

target_link_libraries(
    miv
    ${CURSES_LIBRARIES}
    ${TERMINFO_LIBRARIES}
    ${Boost_LIBRARIES}
)
