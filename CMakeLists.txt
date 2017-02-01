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

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -ggdb -std=c++0x -pedantic -Wextra -Wall -D_GLIBCXX_USE_SCHED_YIELD -D__GXX_EXPERIMENTAL_CXX0X__")
FILE (GLOB_RECURSE SOURCES FOLLOW_SYMLINKS source/*.cpp)
FILE (GLOB_RECURSE HEADERS FOLLOW_SYMLINKS include/*.h)

LINK_LIBRARIES(pthread)

INCLUDE_DIRECTORIES ("source" "include")

ADD_LIBRARY (${PROJECT} ${SOURCES})
INSTALL (TARGETS ${PROJECT}
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         COMPONENT library)
INSTALL (FILES ${HEADERS}
        DESTINATION "include/${PROJECT}"
        )