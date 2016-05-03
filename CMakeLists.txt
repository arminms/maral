CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition and dump it in the cache along with proper documentation,
# otherwise set CMAKE_BUILD_TYPE to Release prior to calling PROJECT()
#
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel")
ELSE()
    SET(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel")
ENDIF()

set(MARAL_VERSION_MAJOR "0")
set(MARAL_VERSION_MINOR "4")
set(MARAL_VERSION_PATCH "1")
set(MARAL_VERSION_TWEAK "0")

PROJECT(maral CXX)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

IF(MSVC)
    ADD_DEFINITIONS(/D_CRT_SECURE_NO_WARNINGS
                    /D_SCL_SECURE_NO_WARNINGS
                    /D_HAS_ITERATOR_DEBUGGING=0)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa /bigobj")
ELSE(MSVC)
    INCLUDE(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    IF(NOT COMPILER_SUPPORTS_CXX11) 
       CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    ENDIF()
    IF(COMPILER_SUPPORTS_CXX11)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ELSEIF(COMPILER_SUPPORTS_CXX0X)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    ELSE()
            MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    ENDIF()
ENDIF()

ADD_SUBDIRECTORY(src)

# testing
OPTION(BUILD_TESTS "Build and install unit tests ?" ON)
IF(BUILD_TESTS)
    ADD_SUBDIRECTORY(test)
    ENABLE_TESTING()
    ADD_TEST(NAME mtl_point COMMAND test_mtl_point
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    ADD_TEST(NAME mtl_vector COMMAND test_mtl_vector
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    ADD_TEST(NAME mtl_matrix COMMAND test_mtl_matrix
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    ADD_TEST(NAME connections COMMAND test_connections
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    ADD_TEST(NAME hierarchical_datamodel COMMAND test_hierarchical_datamodel
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    ADD_TEST(NAME ioformat_tree COMMAND test_ioformat_tree
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    ADD_TEST(NAME io_format_pdb COMMAND test_ioformat_pdb
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
    ADD_TEST(NAME io_format_pdb_multimodel COMMAND test_ioformat_pdb_multimodel
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
ENDIF(BUILD_TESTS)

# build a CPack driven installer package
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_NAME "Maral")
SET(CPACK_PACKAGE_VENDOR "amslab.org")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/readme.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Maral - A header-only template based C++11 molecular API")
SET(CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_SOURCE_DIR}/license.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MARAL_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MARAL_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${MARAL_VERSION_PATCH}")
SET(CPACK_COMPONENTS_ALL headers tests patterns)
SET(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")
SET(CPACK_COMPONENT_TESTS_DISPLAY_NAME "Unit Tests")
SET(CPACK_COMPONENT_PATTERNS_DISPLAY_NAME "Pattern Files")
SET(CPACK_COMPONENT_HEADERS_DESCRIPTION 
    "You need only header files to develop using Maral")
SET(CPACK_COMPONENT_TESTS_DESCRIPTION
    "Binaries for unit testing")
SET(CPACK_COMPONENT_PATTERNS_DESCRIPTION
    "Pattern files required by unit tests")
SET(CPACK_COMPONENT_PATTERNS_DEPENDS tests)
SET(CPACK_COMPONENT_HEADERS_GROUP "Development")
SET(CPACK_COMPONENT_TESTS_GROUP "Runtime")
SET(CPACK_COMPONENT_PATTERNS_GROUP "Runtime")
SET(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
    "All you need to start developing using Maral")
SET(CPACK_COMPONENT_GROUP_RUNTIME_DESCRIPTION
    "Supporting binary files")
INCLUDE(CPack)
