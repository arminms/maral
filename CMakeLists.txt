CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition and dump it in the cache along with proper documentation,
# otherwise set CMAKE_BUILD_TYPE to Release prior to calling PROJECT()
#
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
        "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or
         CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ELSE()
    SET(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or
         CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
ENDIF()

PROJECT(maral CXX)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#IF(WIN32)
#    SET(USERLIB_PREFIX_DEFAULT "c:/local")
#ELSE(WIN32)
#    SET(USERLIB_PREFIX_DEFAULT "/usr")
#ENDIF(WIN32)

IF(MSVC)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa /bigobj")
ELSE(MSVC)
    INCLUDE(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    IF(COMPILER_SUPPORTS_CXX11)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ELSEIF(COMPILER_SUPPORTS_CXX0X)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    ELSE()
            MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    ENDIF()
ENDIF()

#INSTALL(DIRECTORY src/maral DESTINATION include)

ADD_SUBDIRECTORY(src)

OPTION(BUILD_TESTS "Build and install unit tests ?" ON)
IF(BUILD_TESTS)
    ADD_SUBDIRECTORY(test)
ENDIF(BUILD_TESTS)
