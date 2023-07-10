# Install script for directory: /home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/systemc" TYPE FILE FILES
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download/AUTHORS.md"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download/INSTALL.md"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download/cmake/INSTALL_USING_CMAKE"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download/LICENSE"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download/NOTICE"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download/README.md"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download/RELEASENOTES"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCLanguage/SystemCLanguageTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCLanguage/SystemCLanguageTargets.cmake"
         "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/CMakeFiles/Export/lib/cmake/SystemCLanguage/SystemCLanguageTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCLanguage/SystemCLanguageTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCLanguage/SystemCLanguageTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCLanguage" TYPE FILE FILES "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/CMakeFiles/Export/lib/cmake/SystemCLanguage/SystemCLanguageTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCLanguage" TYPE FILE FILES "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/CMakeFiles/Export/lib/cmake/SystemCLanguage/SystemCLanguageTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCLanguage" TYPE FILE FILES
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/SystemCLanguageConfig.cmake"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/SystemCLanguageConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SystemCTLM" TYPE FILE FILES
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/SystemCTLMConfig.cmake"
    "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/SystemCTLMConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/src/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/lopeztel/nordic/DomainPowerModeling/imported/systemc-2.3.4/src/systemc_download-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
