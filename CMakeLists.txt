cmake_minimum_required(VERSION 3.14.2)

project(DomainPowerModeling VERSION 1.0.0 DESCRIPTION "This demo is meant to showcase ...") #TODO: complete description

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


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

# Set the desired versions of SystemC and spdlog
set(SYSTEMC_VERSION "2.3.4")
set(SPDLOG_VERSION "1.11.0")


# Try finding systemC and spdlog package
find_package(SystemCLanguage ${SYSTEMC_VERSION} CONFIG QUIET PATHS ${CMAKE_CURRENT_LIST_DIR}/imported/systemc-${SYSTEMC_VERSION})
find_package(spdlog ${SPDLOG_VERSION} CONFIG QUIET PATHS ${CMAKE_CURRENT_LIST_DIR}/imported/spdlog-${SPDLOG_VERSION})

include(ExternalProject)
if (NOT SystemCLanguage_FOUND)
   message(STATUS "systemC package not found. Will download from repo...")
   set(SYSTEMC_INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/imported/systemc-${SYSTEMC_VERSION})

   ExternalProject_Add ( 
    systemc_download
    PREFIX ${SYSTEMC_INSTALL_DIR}
    GIT_REPOSITORY https://github.com/accellera-official/systemc.git
    GIT_TAG ${SYSTEMC_VERSION}
    # GIT_SHALLOW ON
    GIT_PROGRESS ON
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SYSTEMC_INSTALL_DIR} -DCMAKE_CXX_STANDARD=11 -DDISABLE_COPYRIGHT_MESSAGE=ON
    # trick to make both make and ninja work
    BUILD_BYPRODUCTS ${SYSTEMC_INSTALL_DIR}/lib/libsystemc.so
    BUILD_ALWAYS 1
   )

  if(NOT spdlog_FOUND)
   message(STATUS "spdlog package not found. Will download from repo...")
   set(SPDLOG_INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/imported/spdlog-${SPDLOG_VERSION})

   ExternalProject_Add ( 
    spdlog_download
    PREFIX ${SPDLOG_INSTALL_DIR}
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG "v${SPDLOG_VERSION}"
    # GIT_SHALLOW ON
    GIT_PROGRESS ON
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SPDLOG_INSTALL_DIR} -DCMAKE_CXX_STANDARD=11 -DSPDLOG_BUILD_TESTS=OFF -DSPDLOG_BUILD_EXAMPLE=OFF -DSPDLOG_BUILD_SHARED=ON
    BUILD_BYPRODUCTS ${SPDLOG_INSTALL_DIR}/lib/libspdlog.so
    BUILD_ALWAYS 1
   )

  endif()

   # Set SystemC and spdlog paths
   set(SPDLOG_INCLUDE_DIR ${SPDLOG_INSTALL_DIR}/include)
   set(SPDLOG_LIBRARY_DIR ${SPDLOG_INSTALL_DIR}/lib)
   set(SYSTEMC_INCLUDE_DIR ${SYSTEMC_INSTALL_DIR}/include)
   set(SYSTEMC_LIBRARY_DIR ${SYSTEMC_INSTALL_DIR}/lib)
   # Specify the include directories and link directories
   include_directories(
     ${SYSTEMC_INCLUDE_DIR}
     ${SPDLOG_INCLUDE_DIR}
     ${CMAKE_CURRENT_LIST_DIR}/inc
     )
   link_directories(
     ${SYSTEMC_LIBRARY_DIR}
     ${SPDLOG_LIBRARY_DIR}
     )
   add_library(SystemC::systemc SHARED IMPORTED)
   add_dependencies(SystemC::systemc systemc_download)
   set_target_properties(SystemC::systemc PROPERTIES IMPORTED_LOCATION ${SYSTEMC_LIBRARY_DIR}/libsystemc.so)
   add_library(spdlog::spdlog SHARED IMPORTED)
   add_dependencies(spdlog::spdlog spdlog_download)
   set_target_properties(spdlog::spdlog PROPERTIES IMPORTED_LOCATION ${SPDLOG_LIBRARY_DIR}/libspdlog.so)
   add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
   add_dependencies(${PROJECT_NAME} systemc_download spdlog_download)
else()
   message(STATUS "systemC package found")
   include_directories(
     ${CMAKE_CURRENT_LIST_DIR}/inc
     )

   add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
endif()
   target_link_libraries(${PROJECT_NAME} PUBLIC SystemC::systemc spdlog::spdlog)
