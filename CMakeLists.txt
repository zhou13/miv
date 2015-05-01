cmake_minimum_required(VERSION 3.0)
project(miv)

INCLUDE(CheckLibraryExists)
CHECK_LIBRARY_EXISTS(tinfo setupterm "" HAVE_TERMINFO)
if (HAVE_TERMINFO)
    set(TERMINFO_LIBRARIES "tinfo")
endif()

option(WITH_NCURSES_UI "Compile the ncurses interface" ON)
option(WITH_QT_UI "Compile the QT interface" OFF)
option(WITH_PRINTF_UI "Compile the printf interface" OFF)

if(WITH_NCURSES_UI)
  add_definitions(-DWITH_NCURSES_UI)
endif()
if(WITH_QT_UI)
  add_definitions(-DWITH_QT_UI)
endif()
if(WITH_PRINTF_UI)
  add_definitions(-DWITH_PRINTF_UI)
endif()

set(GCC_PARAMETERS "-Wall -Wextra -std=c++1y")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_PARAMETERS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_PARAMETERS} -g3 -DDEBUG -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${GCC_PARAMETERS} -O2")

find_package(Boost COMPONENTS program_options system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(src)


set(
    miv_SRC
    src/action/action.hpp
    src/action/common.cpp
    src/file/file.cpp
    src/frame/frame.cpp
    src/frame/mode.hpp
    src/main.cpp
    src/miv/controller.cpp
    src/miv/input.cpp
    src/miv/miv.cpp
    src/miv/screen.hpp
    src/ui/ncurses.cpp
    src/ui/ui.cpp
    src/utils/utils.hpp
    src/utils/logger.hpp
    src/xarray/xarray.cpp
    src/xarray/splitlist.cpp
    src/config/config.cpp
)

add_subdirectory(src/utils/libtermkey)

add_executable(
    miv
    ${miv_SRC}
)

target_link_libraries(
    miv
    termkey
    ${CURSES_LIBRARIES}
    ${TERMINFO_LIBRARIES}
    ${Boost_LIBRARIES}
)
