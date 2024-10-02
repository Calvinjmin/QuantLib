# --- Project Overview --- #
cmake_minimum_required(VERSION 3.10)
project(QuantLib)

# --- Warnings --- #
cmake_policy(SET CMP0167 NEW)

# --- Libraries --- #
set(QUANTLIB_INCLUDE_DIR "/Users/calvinjmin/local/include")
set(QUANTLIB_LIBRARY_DIR "/Users/calvinjmin/local/lib")
set(BOOST_INCLUDE_DIR "/opt/homebrew/opt/boost/include")
set(BOOST_LIBRARY_DIR "/opt/homebrew/opt/boost/lib")

# --- C++ Standards --- #
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Packages --- #
include_directories(${QUANTLIB_INCLUDE_DIR} ${BOOST_INCLUDE_DIR})
find_library(QUANTLIB_LIBRARY QuantLib HINTS ${QUANTLIB_LIBRARY_DIR})
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# --- Executables --- #
add_executable(main src/main.cpp)
target_link_libraries(main ${QUANTLIB_LIBRARY} ${Boost_LIBRARIES}) 
