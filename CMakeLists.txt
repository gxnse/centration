cmake_minimum_required(VERSION 3.10)

project(centration)

# Using C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Python
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

# Project's source files
set(PROJECT_SOURCES
    ../src/main.cpp
	../src/configReader.h
    ../src/configReader.cpp
    ../src/dataCentration.h
    ../src/dataCentration.cpp
	../src/graphHandler.h
	../src/graphHandler.cpp
)

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})


# Include directories for Python
include_directories(${PYTHON_INCLUDE_DIRS})

# Link against Python
target_link_libraries(centration PRIVATE ${PYTHON_LIBRARIES})