INCLUDE_DIRECTORIES(
    "."
    ../src
)

IF(WIN32)
    SET(BOOST_ROOT C:/local/boost_1_59_0)
ENDIF(WIN32)
FIND_PACKAGE(Boost 1.50.0)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    ADD_EXECUTABLE(test_connections test_connections.cpp)
    ADD_EXECUTABLE(test_hierarchical_datamodel test_hierarchical_datamodel.cpp)
    ADD_EXECUTABLE(test_ioformat_pdb test_ioformat_pdb.cpp)
    ADD_EXECUTABLE(test_ioformat_tree test_ioformat_tree.cpp)
    ADD_EXECUTABLE(test_mtl_matrix test_mtl_matrix.cpp)
    ADD_EXECUTABLE(test_mtl_point test_mtl_point.cpp)
    ADD_EXECUTABLE(test_mtl_vector test_mtl_vector.cpp)
    INSTALL(DIRECTORY patterns DESTINATION share/maral/test)
    INSTALL(TARGETS
               test_connections
	       test_hierarchical_datamodel
	       test_ioformat_pdb
	       test_ioformat_tree
	       test_mtl_matrix
	       test_mtl_point
	       test_mtl_vector
            RUNTIME DESTINATION share/maral/test)
ENDIF()
