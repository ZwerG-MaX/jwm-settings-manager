cmake_minimum_required(VERSION 2.8)
project(jwm-settings-manager CXX C)
set(PROJECT_NAME jwm-settings-manager)
set(VERMAJ "2")
set(VERMIN "0")
set(VERREV "0")
SET(VERSION "${VERMAJ}.${VERMIN}.${VERREV}")
set(YEAR "2016")
set(TOOLKITS "nanosvg, pugixml and FLTK")
SET(DATE "Nov 17, ${YEAR}")
INCLUDE(AddFileDependencies)
INCLUDE(CheckIncludeFiles)
INCLUDE(FindPkgConfig)
set(SHORT_DESC "  A tool to easily configure JWM.  Built using ${TOOLKITS},
  ${EXEC} is fast, and light, but doesn't sacrifice aesthetics.")
set(SHORT_DESC_ONE_LINE "  A tool to easily configure JWM.  Built using ${TOOLKITS},\n${EXEC} is fast, and light, but doesn't sacrifice aesthetics.")
#Needs double \\n to work in cpp file
set(SHORT_DESC_ONE_LINE_CPP "  A tool to easily configure JWM.  Built using ${TOOLKITS},\\n${EXEC} is fast, and light, but doesn't sacrifice aesthetics.")
set(ONE_LINER "configure JWM easily")
set(WEBsite "http://torios.top")
set(ICON "jwm-settings-manager")
set(EXEC "jwm-settings-manager")
set(NAME "JWM Settings Manager")
## configure usage/copyright/man pages
set(EMAIL "israeldahl@gmail.com")
set(AUTHOR "Israel Dahl")
set(ARGicons "--icons")
set(ARGautostart "--autostart")
set(ARGdesktop "--desktop")
set(ARGshutdown "--shutdown")
set(ARGwindow "--window")
set(ARGclock "--clock")
set(ARGpanel "--panel")
set(ARGmouse "--mouse")
set(ARGkeyboard "--keyboard")
set(ARGfont "--font")
set(ARGmenu "--menu")
set(ARGthemes "--themes")
set(ARGhalt "--halt")
set(ARGhelp "--help")
set(ARGshortcuts "--shortcuts")
set(ARGcopyright "--copyright")
set(ARGversion "--version")
set(ARGrecover "--recover")
set(MISCDEPS "\${misc:Depends}")
set(DEBDEPS "\${source:Version}) , \${shlibs:Depends}, ${MISCDEPS}")
set(ARGdebug "--debug")
# Packages we need
FIND_PACKAGE(FLTK REQUIRED NO_MODULE)
FIND_PACKAGE(X11 REQUIRED)
IF(NOT EXISTS ${FLTK_FLUID_EXECUTABLE})
    # Try to detect full path anyway
    EXECUTE_PROCESS(COMMAND which fluid OUTPUT_VARIABLE FLTK_FLUID_EXECUTABLE OUTPUT_STRIP_TRAILING_WHITESPACE)
    IF(NOT EXISTS ${FLTK_FLUID_EXECUTABLE})
        MESSAGE(FATAL_ERROR "Please install the fluid binary which is part of FLTK.")
    ENDIF()
ENDIF()
IF(NOT EXISTS ${FLTK_INCLUDE_DIR})
    # Try to detect full path anyway
    set(FLTK_INCLUDE_DIR "/usr/include")
    IF(NOT EXISTS ${FLTK_INCLUDE_DIR})
        MESSAGE(FATAL_ERROR "Please install the fluid binary which is part of FLTK.")
    ENDIF()
ENDIF()
# Don't need OpenGL or the Fluid plugin, since I export the source from FLUID
set(FLTK_SKIP_OPENGL True)
set(FLTK_SKIP_FLUID True)

## install things in /usr
set(CMAKE_INSTALL_PREFIX "/usr")

FILE(RELATIVE_PATH LIB_DIR_RELATIVE "/${BIN_DIR}" "/${LIB_DIR}")
add_definitions("-DCOMPILER_ARGS=\"${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG=true\"")
#Configure Man page
configure_file("debian/${PROJECT_NAME}.1.in" "${PROJECT_NAME}.1")
configure_file("debian/control.in" "debian/control")
configure_file("src/jsm.cpp.in" "src/jsm.cpp")
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
     message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -fvar-tracking -DDEBUG=true")
#set(CMAKE_BUILD_TYPE "RELEASE")
#set(CMAKE_CONFIGURATION_TYPE "RELEASE")

## Compiler includes ( FLTK X11 and all my stuff)
INCLUDE_DIRECTORIES("${FLTK_INCLUDE_DIR}"
		    "${X11_INCLUDE_DIR}"
		    "${X11_Xpm_INCLUDE_PATH}"
            "${CMAKE_SOURCE_DIR}/include"
            "${CMAKE_SOURCE_DIR}/fltk"
		    "${CMAKE_BINARY_DIR}/fltk"
            "${CMAKE_BINARY_DIR}/include")

## Compiler flags

#set(SVG_DEFINES "-DNANOSVG_IMPLEMENTATION=true -DNANOSVG_ALL_COLOR_KEYWORDS=true -DNANOSVGRAST_IMPLEMENTATION=true")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SVG_DEFINES}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Os -finline-small-functions -finline-functions-called-once -fno-unwind-tables -fno-asynchronous-unwind-tables -s")
if(EXISTS ${X11_INCLUDE_DIR})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX_COMMON_HAS_X=true")
endif()
set(XML_HEADERS include/pugixml.hpp)
set(XML_SOURCES ${HEADERS} src/pugixml.cpp)
set( FLTK_SRCS2
	fltk/jwm-autostart.cxx
	fltk/jwm-desktop.cxx
	fltk/jwm-fonts.cxx
	fltk/jwm-icons.cxx
	fltk/jwm-keyboard.cxx
	fltk/jwm-panel.cxx
	fltk/jwm-shutdown.cxx
	fltk/jwm-settings.cxx
	fltk/jwm-themes.cxx
	fltk/jwm-window.cxx
	fltk/jwm-menu.cxx
)
### ALL the source code
set(JSM_SRCS
    src/menu.cpp
	src/autostart.cpp
	src/common.cpp
	src/desktop.cpp
	src/fonts.cpp
	src/jwmrc.cpp
	src/keyboard.cpp
	src/icons.cpp
	src/fltkfunctions.cpp
	src/panel.cpp
	src/themes.cpp
	src/ui.cpp
	src/window.cpp
	${XML_SOURCES}
	${FLTK_SRCS2}
)
## Turn the source code into a library
add_library(JSM STATIC ${JSM_SRCS})
## make the executable
add_executable(jwm-settings-manager src/jsm.cpp)
add_executable(fltk-mouse fltk/jwm-mouse.cxx)
add_executable(desktop-file-editor fltk/desktop-file-editor.cxx)
## Linker settings
set(ALL_LIBS JSM fltk_SHARED fltk_images_SHARED ${X11_LIBRARIES} ${X11_X11_LIB} ${X11_Xpm_LIB})
TARGET_LINK_LIBRARIES(jwm-settings-manager ${ALL_LIBS})
TARGET_LINK_LIBRARIES(fltk-mouse ${ALL_LIBS})
TARGET_LINK_LIBRARIES(desktop-file-editor ${ALL_LIBS})
## Install the binary to bin and the library to lib :)
install(TARGETS jwm-settings-manager fltk-mouse desktop-file-editor JSM
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
)

