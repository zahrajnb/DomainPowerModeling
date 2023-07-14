cmake_minimum_required(VERSION 3.14.2)

project(DomainPowerModeling VERSION 1.0.0 DESCRIPTION "This demo is meant to showcase ...") #TODO: complete description

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(imported/Fused_ps)

option(BUILD_DOC "Build Doxygen document" OFF)
option(INSTALL_DEPS "Build Doxygen document" OFF)

#Build document
if (BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_LIST_DIR}/doc/Doxyfile)
    
        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message(STATUS "Doxygen build started")
    
        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
      message(STATUS "Doxygen needs to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif (BUILD_DOC)

file (GLOB HEADERS "${CMAKE_CURRENT_LIST_DIR}/inc/*.h")
file (GLOB SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")


include_directories(${CMAKE_CURRENT_LIST_DIR}/inc
${CMAKE_CURRENT_LIST_DIR}/imported/Fused_ps/ps
${CMAKE_CURRENT_LIST_DIR}/imported/Fused_ps/imported/include
)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC Fused_ps)
