cmake_minimum_required (VERSION 2.6)
project (Team_1_project)

if(NOT CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/local/include/")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
option(test "Build tests." ON)

#set(CMAKE_CXX_FLAGS "-W -Wall -O3 -pedantic -std=c++11 -I/usr/local/include/")
#add_executable (main main.cpp src/Population.cpp src/multiBinomial.cpp src/Simulation.cpp)

SET(SOURCE_FILES src/Population.cpp src/multiBinomial.cpp src/Simulation.cpp) 

include_directories(${CMAKE_SOURCE_DIR}/extra/include)
add_executable(main main.cpp ${SOURCE_FILES})

########## Google Test ######### 


if(test)
 enable_testing()
 find_package(GTest)
 if(NOT GTEST_FOUND)
  link_directories(${CMAKE_SOURCE_DIR}/extra/lib)
  SET(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/extra/include)
  SET(GTEST_BOTH_LIBRARIES libgtest.a libgtest_main.a)
 endif(NOT GTEST_FOUND)
 include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)
 add_executable(unittest test/unittest.cpp ${SOURCE_FILES})
 target_link_libraries(unittest ${GTEST_BOTH_LIBRARIES} pthread)
 add_test(Team_1_project unittest)
endif(test)

###### Doxygen generation ######

# We first check if Doxygen is present.
find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxygen.in configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
         - Generate one in the project folder with doxygen -g Doxyfile.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc #ALL
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)
