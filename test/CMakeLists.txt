INCLUDE_DIRECTORIES(
    "."
    ../src
)

SET(Boost_NO_BOOST_CMAKE ON)

#
# because of automatic linking to corresponding Boost libraries on
# Visual Studio we must handle it differently
#
IF(MSVC)
    IF("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
        SET(_LIB_BEG "lib64")
    ELSE("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
        SET(_LIB_BEG "lib")
    ENDIF()

    IF(MSVC14)
        SET(_boost_LIB_PATH "${_LIB_BEG}-msvc-14.0")
    ELSEIF(MSVC12)
        SET(_boost_LIB_PATH "${_LIB_BEG}-msvc-12.0")
    ELSEIF(MSVC11)
        SET(_boost_LIB_PATH "${_LIB_BEG}-msvc-11.0")
    ELSEIF(MSVC10)
        SET(_boost_LIB_PATH "${_LIB_BEG}-msvc-10.0")
    ELSEIF(MSVC90)
        SET(_boost_LIB_PATH "${_LIB_BEG}-msvc-9.0")
    ELSEIF(MSVC80)
        SET(_boost_LIB_PATH "${_LIB_BEG}-msvc-8.0")
    ELSE(MSVC14)
        SET(_boost_LIB_PATH ${_LIB_BEG})
    ENDIF(MSVC14)

    SET(BOOST_ROOT C:/local/boost_1_59_0)
    SET(BOOST_LIBRARYDIR "${BOOST_ROOT}/${_boost_LIB_PATH}")
#    ADD_DEFINITIONS("-DBOOST_ALL_NO_LIB")
#    SET(Boost_USE_STATIC_LIBS           ON)
#    SET(Boost_USE_MULTITHREADED         ON)
#    SET(Boost_DETAILED_FAILURE_MSG      ON)
#    ADD_DEFINITIONS(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
ENDIF(MSVC)

FIND_PACKAGE(Boost 1.55.0 COMPONENTS iostreams)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    ADD_EXECUTABLE(test_connections test_connections.cpp)
    ADD_EXECUTABLE(test_hierarchical_datamodel test_hierarchical_datamodel.cpp)
    ADD_EXECUTABLE(test_ioformat_tree test_ioformat_tree.cpp)
    ADD_EXECUTABLE(test_mtl_matrix test_mtl_matrix.cpp)
    ADD_EXECUTABLE(test_mtl_point test_mtl_point.cpp)
    ADD_EXECUTABLE(test_mtl_vector test_mtl_vector.cpp)
    IF(MSVC)
        LINK_DIRECTORIES("${Boost_INCLUDE_DIR}/${_boost_LIB_PATH}")
        ADD_EXECUTABLE(test_ioformat_pdb test_ioformat_pdb.cpp)
        ADD_EXECUTABLE(test_ioformat_pdb_multimodel test_ioformat_pdb_multimodel.cpp)
        INSTALL(DIRECTORY patterns DESTINATION test)
        INSTALL(TARGETS
                test_connections
                test_hierarchical_datamodel
                test_ioformat_tree
                test_mtl_matrix
                test_mtl_point
                test_mtl_vector
                test_ioformat_pdb
                test_ioformat_pdb_multimodel
                RUNTIME DESTINATION test)
    ELSE()
        ADD_EXECUTABLE(test_ioformat_pdb test_ioformat_pdb.cpp)
        ADD_EXECUTABLE(test_ioformat_pdb_multimodel test_ioformat_pdb_multimodel.cpp)
        TARGET_LINK_LIBRARIES(test_ioformat_pdb ${Boost_LIBRARIES})
        INSTALL(DIRECTORY patterns DESTINATION share/maral/test)
        INSTALL(TARGETS
                test_connections
                test_hierarchical_datamodel
                test_ioformat_tree
                test_mtl_matrix
                test_mtl_point
                test_mtl_vector
                test_ioformat_pdb
                test_ioformat_pdb_multimodel
                RUNTIME DESTINATION share/maral/test)
    ENDIF()
#    FILE(COPY patterns DESTINATION test)
ENDIF(Boost_FOUND)
