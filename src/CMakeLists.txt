project(antares)
cmake_minimum_required(VERSION 3.0)

# Version
set(ANTARES_VERSION_HI	      7)
set(ANTARES_VERSION_LO	      2)
set(ANTARES_VERSION_REVISION  0)
set(ANTARES_VERSION_YEAR      2019)

set(ANTARES_PUBLISHER	   "RTE France")
set(ANTARES_WEBSITE	   "https://antares.rte-france.com")

# Beta release
set(ANTARES_BETA 0)
set(ANTARES_RC 2)

# CMAKE - Suppress useless features
set(CMAKE_SKIP_PREPROCESSED_SOURCE_RULES true)
set(CMAKE_SKIP_ASSEMBLY_SOURCE_RULES true)

include(CheckCXXSourceCompiles)
include(CheckIncludeFiles)
include(CheckIncludeFileCXX)
include(CheckCXXCompilerFlag)


#CMake function to build dependancy from git
include("cmake/utils.cmake")

#CMake Macro to display message
include("cmake/messages.cmake")

if(${ANTARES_BETA})
	set(ANTARES_VERSION_TAG "-beta${ANTARES_BETA}")
else()
	set(ANTARES_VERSION_TAG "")
endif()

if(${ANTARES_RC})
	set (ANTARES_VERSION_TAG "${ANTARES_VERSION_TAG}-rc${ANTARES_RC}")
else()
	set (ANTARES_RC 0)
endif()

# Build Configuration
if("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "tuning")
	set(ANTARES_TARGET "${CMAKE_BUILD_TYPE}")
else()
	#Define CMAKE_BUILD_TYPE as Debug for external library use
	set(CMAKE_BUILD_TYPE "Debug")

	#TODO : Antares Target is debug instead of Debug YUNI and Antares CMakeLists.txt to be reviewed to change debug to Debug
	set(ANTARES_TARGET  "debug")
endif()

OMESSAGE("")
OMESSAGE_TITLE("Antares " "v${ANTARES_VERSION_HI}.${ANTARES_VERSION_LO}.${ANTARES_VERSION_REVISION}${ANTARES_VERSION_TAG}-${ANTARES_TARGET}")
OMESSAGE("A New Tool for Adequacy Reporting of Electric Systems (RTE France)")
OMESSAGE_BOLD("Configuring...")
OMESSAGE("")

# Making gatherings of several projects under a project folder in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Copy changelog
include("cmake/changelog.cmake")

#Check compiler version
include("cmake/checks.cmake")


if (ANTARES_LICENSE)
	OMESSAGE("{antares}  License : ${ANTARES_LICENSE}")
endif()

set(ANTARES_PRG_VERSION  "${ANTARES_VERSION_HI}.${ANTARES_VERSION_LO}")

#TODO : define if MSVC is used (check if can be removed)
if ((WIN32 OR WIN64) AND (NOT MINGW AND NOT MSVC AND NOT CYGWIN AND NOT MSYS))
	set(MSVC 1)
	set(ICC 1)
endif()

#Define which version is compiled (32bits or 64bits)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	OMESSAGE(" Enabled 64bits instructions sets")
	set(ANTARES_x86_64 			true)
	set(ANTARES_INSTALLER_ARCH 		"64bits")
	set(ANTARES_INSTALLER_REDIST_ARCH 	"x64")
	set(ANTARES_MANIFEST_ARCH 		"ia64")
else()
	set(ANTARES_INSTALLER_ARCH 		"32bits")
	set(ANTARES_INSTALLER_REDIST_ARCH 	"x86")
	set(ANTARES_MANIFEST_ARCH 		"x86")
endif()


#TODO : should not defined compiler name with a global variable
if (WIN32)
	if(MSVC)
		set(COMPILER_NAME "vc14")
		set(COMPILER_LIB_INCLUDE "vc")
	else(MSVC)
		set(COMPILER_NAME "gcc4.x")
		set(COMPILER_LIB_INCLUDE "gcc")
	endif(MSVC)
endif(WIN32)

#
# Beta
#
if(NOT ANTARES_BETA EQUAL 0)
	set(ANTARES_INSTALLER_BETA "-beta${ANTARES_BETA}")
else()
	set(ANTARES_INSTALLER_BETA "")
endif()

if(${ANTARES_RC})
	set(ANTARES_INSTALLER_RC "-rc${ANTARES_RC}")
else()
	set(ANTARES_INSTALLER_RC "")
endif()

OMESSAGE("")
OMESSAGE("")

#Display Build Configuration (debug or release)
if("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "tuning")
	OMESSAGE("{antares} Build Configuration: RELEASE")
else()
	OMESSAGE("{antares} Build Configuration: DEBUG")
endif()

#
# Yuni Framework
#
if("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "tuning")
	set(YUNI_TARGET_MODE "release")
	set(ANTARES_VERSION_TARGET  "release")
else()
	set(YUNI_TARGET_MODE "debug")
	set(ANTARES_VERSION_TARGET  "debug")
endif()

# TODO : removed to be confirmed : old fashion CMake All libraries will be stored in /bin directory
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin/${YUNI_TARGET_MODE})

option(BUILD_UI "Build antares ui simulator" ON)
message(STATUS "Build antares ui simulator: ${BUILD_UI}")

option(BUILD_DEPS "Build all dependencies" OFF)
message(STATUS "Build all dependencies: ${BUILD_DEPS}")

# IF BUILD_DEPS=ON THEN Force all BUILD_*=ON
include(CMakeDependentOption)

CMAKE_DEPENDENT_OPTION(BUILD_wxWidgets "Build wxWidgets dependency Library" OFF
  "NOT BUILD_DEPS" ON)
message(STATUS "Build wxWidgets: ${BUILD_wxWidgets}")

CMAKE_DEPENDENT_OPTION(BUILD_OPENSSL "Build OpenSSL dependency Library" OFF
  "NOT BUILD_DEPS" ON)
message(STATUS "Build BUILD_OPENSSL: ${BUILD_OPENSSL}")

CMAKE_DEPENDENT_OPTION(BUILD_curl "Build curl dependency Library" OFF
  "NOT BUILD_DEPS" ON)
message(STATUS "Build BUILD_curl: ${BUILD_curl}")

CMAKE_DEPENDENT_OPTION(BUILD_zlib "Build zlib dependency Library" OFF
  "NOT BUILD_DEPS" ON)
message(STATUS "Build BUILD_zlib: ${BUILD_zlib}")

# Build Needed dependencies
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build_deps/install)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build_deps/install/libs/pkgconfig)

add_subdirectory(cmake/dependencies ${CMAKE_CURRENT_SOURCE_DIR}/build_deps)

if(BUILD_wxWidgets)
	# Define wxWidgets_ROOT_DIR
	set(wxWidgets_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build_deps/install)  
endif()

# Define needed external library

#libcurl
find_package(CURL REQUIRED)

#openssl	
find_package(OpenSSL REQUIRED)


#TODO : Add ZLIB if  VCPKG used why is this needed
if (VCPKG_TOOLCHAIN) 
    #zlib
    find_package(ZLIB REQUIRED)
endif()


#Add specific definition in case of dependencies build

if(BUILD_curl)

	# ADD CURL_STATICLIB definition 
	add_definitions(-DCURL_STATICLIB) 
	
	if(WIN32 OR WIN64)
	
		#Linking not working on windows need to add several system dependency
		SET(CURL_LIBRARIES ${CURL_LIBRARIES} "Ws2_32.Lib" "Wldap32.Lib" "Crypt32.Lib")
    else()
		
		#zlib
		find_package(ZLIB REQUIRED)
	
		#find_package(CURL) doesn't indicate ZLIB and idn2 dependencies (idn2 used even with --without-libidn option in configure)
		SET(CURL_LIBRARIES ${CURL_LIBRARIES} ${ZLIB_LIBRARIES} idn2)    
	endif()	 
endif()

if(BUILD_OPENSSL)
	
	if(WIN32 OR WIN64)
    	else()
		#find_package(OpenSSL doesn't indicate -ldl option
		SET(OPENSSL_LIBRARIES ${OPENSSL_LIBRARIES} "dl")    
	endif()	 
endif()

#wxWidget not needed for all library find is done in ui CMakeLists.txt
if (VCPKG_TOOLCHAIN AND NOT BUILD_wxWidgets) 
    #Add cmake directory to CMAKE_MODULE_PATH to use specific FindwxWidgets package needed for vcpkg
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/wxWidgets")
endif()

# TODO : review Standard Settings
include(cmake/common-settings.cmake)

# Configure config.h with current ANTARES version
configure_file("config.h.cmake" "${CMAKE_CURRENT_BINARY_DIR}/config.h")
configure_file("config.h.cmake" "${CMAKE_CURRENT_SOURCE_DIR}/config.h")

# Yuni Framework
configure_file("cmake/ProfileBuild.template.cmake" "ext/yuni/src/ProfileBuild.cmake")
add_subdirectory("ext/yuni/src")

#Sirius solver
add_subdirectory("ext/Sirius_Solver" "ext/Sirius_Solver")

OMESSAGE("") # empty line

# Sub Directories
add_subdirectory(libs) 		#antares-core fswalker
add_subdirectory(internet) 	#libantares-license base64 keys

if(BUILD_UI)
	add_subdirectory(ui)		#all antares ui libs + antares simulator
endif()

add_subdirectory(solver)	#antares solver and all associated libs
add_subdirectory(analyzer)	#antares analyser

# Tools
add_subdirectory(tools)	#All antares tools

# Tests
# 	Not setting BUILD_TESTING as a command line argument is equivalent to use -DBUILD_TESTING=OFF
# 	To build tests, use -DBUILD_TESTING=ON
option(BUILD_TESTING "Activates unit tests building" OFF)
if(BUILD_TESTING)
	# include(CTest) # calls enable_testing() and turns BUILD_TESTING to ON by default (among other useful things)
	enable_testing()
	
	CMAKE_DEPENDENT_OPTION(BUILD_BOOST_TEST "Download and build boost.test" OFF "NOT BUILD_DEPS" ON)
	
	if(BUILD_BOOST_TEST)
		# Setting CMAKE_PREFIX_PATH so that find_package(boost.test...) finds "${FizzBuzz current path}/ext" boost.test
		list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests/ext")
	endif()
		
	add_subdirectory(tests)
endif()

OMESSAGE("")

# Informations for NSIS
if(WIN32 OR WIN64)
	if(MSVC)
		if("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "tuning")
			set(NSIS_TARGET "Release")
		else("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "tuning")
			set(NSIS_TARGET "Debug")
		endif("${CMAKE_BUILD_TYPE}" STREQUAL "release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "tuning")
		set(COMPILER_MARK "v")
		#set(COMPILER_INCLUDE "vs9")
	else(MSVC)
		set(NSIS_TARGET "")
		set(COMPILER_MARK "m")
		set(COMPILER_INCLUDE "mingw")
	endif(MSVC)
	
	set(CPACK_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR}/distrib/win32 ${CPACK_MODULE_PATH})

	# Configure file with custom definitions for NSIS.
	configure_file(
		${PROJECT_SOURCE_DIR}/distrib/win32/version.cmake
		${CMAKE_CURRENT_BINARY_DIR}/distrib/win32/version.nsh
	)
	
	configure_file(
		${PROJECT_SOURCE_DIR}/distrib/win32/build.template.cmake
		${CMAKE_CURRENT_BINARY_DIR}/distrib/win32/build.nsh
	)
	
	configure_file(
		${PROJECT_SOURCE_DIR}/distrib/win32/make-zip-from-installer.cmake
		${CMAKE_CURRENT_BINARY_DIR}/distrib/win32/make-zip-from-installer.bat
	)
	
	SET(ANTARES_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
	
	# Define system libraries so NSIS can package these files
	include (InstallRequiredSystemLibraries)
	
	#Convert to native and add double quote to be used in NSIS package
	foreach(SYSTEM_RUNTIME_LIB ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
		file(TO_NATIVE_PATH ${SYSTEM_RUNTIME_LIB} SYSTEM_RUNTIME_LIB_NATIVE)
		
		list(APPEND SYSTEM_RUNTIME_LIBS_NATIVE \"${SYSTEM_RUNTIME_LIB_NATIVE}\")
	endforeach()
	
	#Replace ; by space so SYSTEM_RUNTIME_LIBS_STR can be used in File function in NSIS file
	string (REPLACE ";" " " SYSTEM_RUNTIME_LIBS_STR "${SYSTEM_RUNTIME_LIBS_NATIVE}")
	
	configure_file(
		${PROJECT_SOURCE_DIR}/distrib/win32/NSIS.template.in
		${CMAKE_CURRENT_BINARY_DIR}/distrib/win32/NSIS.template.in
		@ONLY
	)
	
	#Define cpack install script to checkout examples
	configure_file(
		${PROJECT_SOURCE_DIR}/distrib/CMakeLists.txt.in
		${CMAKE_CURRENT_BINARY_DIR}/distrib/CMakeLists.txt
		@ONLY
	)
	
	set(CPACK_INSTALL_SCRIPT ${CMAKE_CURRENT_BINARY_DIR}/distrib/CMakeLists.txt)
  
	#Set package name from CMake and antares variables
	set(CPACK_PACKAGE_FILE_NAME "rte-antares-${ANTARES_VERSION_HI}.${ANTARES_VERSION_LO}.${ANTARES_VERSION_REVISION}${ANTARES_VERSION_TAG}-installer-${ANTARES_INSTALLER_ARCH}")


else()

	#For now only test deb, need to define several CPACK variable
	set(CPACK_PROJECT_NAME "antares-deb-test")
	set(CPACK_DEBIAN_PACKAGE_MAINTAINER "RTE")
	set(CPACK_DEBIAN_PACKAGE_NAME "antares")
	set(CPACK_PACKAGE_VERSION_MAJOR ${ANTARES_VERSION_HI})
	set(CPACK_PACKAGE_VERSION_MINOR ${ANTARES_VERSION_LO})
	set(CPACK_PACKAGE_VERSION_PATCH ${ANTARES_VERSION_REVISION})

	set(CPACK_DEBIAN_PACKAGE_DEPENDS "libuuid1, libcurl4, libwxgtk3.0")

	configure_file("distrib/unix/packages.cmake" "distrib/unix/packages.sh")

	
endif()

# Load packaging facilities.
include(CPack)

