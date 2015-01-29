CMAKE_MINIMUM_REQUIRED (VERSION 2.6 FATAL_ERROR)

SET (PROJECT "FSM")
PROJECT (${PROJECT})

if(CMAKE_COMPILER_IS_GNUCXX)
    exec_program (${CMAKE_CXX_COMPILER} ARGS --version OUTPUT_VARIABLE _compiler_output)
    string(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1" gcc_compiler_version ${_compiler_output})
    message(STATUS "C++ compiler version: ${gcc_compiler_version} [${CMAKE_CXX_COMPILER}]")

    if(NOT gcc_compiler_version MATCHES "[0-9]\\.[0-9]\\.[0-9]")
        message(FATAL_ERROR "Can not recognize compiler version")
    endif()
    if(NOT gcc_compiler_version VERSION_GREATER "4.7")
        message(FATAL_ERROR "gcc version should be 4.7 or greater")
    endif()
endif()

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++0x -pedantic -Wextra -Wall -D_GLIBCXX_USE_SCHED_YIELD -D__GXX_EXPERIMENTAL_CXX0X__")
FILE (GLOB_RECURSE SOURCES FOLLOW_SYMLINKS source/*.cpp)

LINK_LIBRARIES(pthread)

INCLUDE_DIRECTORIES ("source" "include")

macro (ADD_PROJECT BUILD_TYPE)
    #ADD_EXECUTABLE (${PROJECT}.${BUILD_TYPE} ${SOURCES})
    FILE(MAKE_DIRECTORY install/${BUILD_TYPE})
    ADD_LIBRARY (${PROJECT}.${BUILD_TYPE} ${SOURCES})
    IF ("${BUILD_TYPE}" STREQUAL "debug")
        SET_TARGET_PROPERTIES (${PROJECT}.${BUILD_TYPE} PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS_DEBUG} -O0")
    ELSEIF ("${BUILD_TYPE}" STREQUAL "release")
        SET_TARGET_PROPERTIES (${PROJECT}.${BUILD_TYPE} PROPERTIES COMPILE_FLAGS "${CMAKE_C_FLAGS_RELEASE} -O2")
    ENDIF()
endmacro()

ADD_PROJECT("debug")
ADD_PROJECT("release")
