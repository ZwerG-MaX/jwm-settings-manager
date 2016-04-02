cmake_minimum_required(VERSION 2.8)
project(jwm-settings-manager CXX C)
set(PROJECT_NAME jwm-settings-manager)
SET(VERSION "1.0.0")
SET(DATE "Nov 05, 2015")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

INCLUDE(AddFileDependencies)
INCLUDE(CheckIncludeFiles)
INCLUDE(FindPkgConfig)

set(ICON "jwm-settings-manager")
set(EXEC "jwm-settings-manager")
set(NAME "JWM Settings Manager")
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

#Configure Man page
configure_file("debian/${PROJECT_NAME}.1.in" "${PROJECT_NAME}.1")

set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CONFIGURATION_TYPE "RELEASE")

## Compiler includes ( FLTK X11 and all my stuff)
INCLUDE_DIRECTORIES("${FLTK_INCLUDE_DIR}"
		    "${X11_INCLUDE_DIR}"
		    "${X11_Xpm_INCLUDE_PATH}"
                    "${CMAKE_SOURCE_DIR}/data/icons"
                    "${CMAKE_SOURCE_DIR}/include"
                    "${CMAKE_SOURCE_DIR}/fltk"
		    "${CMAKE_BINARY_DIR}/fltk"
                    "${CMAKE_BINARY_DIR}/include"
		    "${CMAKE_BINARY_DIR}/data/icons")

## Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Os -finline-small-functions -finline-functions-called-once -fno-unwind-tables -fno-asynchronous-unwind-tables -s")

### ALL the source code
set(JSM_SRCS
	src/Apps.cpp
	src/Config.cpp
	src/flAutostart.cpp
	src/flDesktop.cpp
	src/flFont.cpp
	src/flIcons.cpp
	src/flKeyboard.cpp
	src/flMouse.cpp
	src/flPanel.cpp
	src/flThemes.cpp
	src/flWindow.cpp
	src/ui.cpp
	src/tinyxml2.cpp

	fltk/jwm-autostart.cxx
	fltk/jwm-desktop.cxx
	fltk/jwm-fonts.cxx
	fltk/jwm-icons.cxx
	fltk/jwm-keyboard.cxx
	fltk/jwm-mouse.cxx
	fltk/jwm-menu.cxx
	fltk/jwm-panel.cxx
	fltk/jwm-settings.cxx
	fltk/jwm-themes.cxx
	fltk/jwm-window.cxx
	fltk/jwm-shutdown.cxx
)
## Turn the source code into a library
add_library(JSM STATIC ${JSM_SRCS})

## include the Cmake file in the data directory
add_subdirectory(data)

## make the executable
add_executable(jwm-settings-manager src/jwm.cpp)
## install the man file
INSTALL(FILES jwm-settings-manager.1 DESTINATION share/man/man1/ PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

## Linker settings
TARGET_LINK_LIBRARIES(jwm-settings-manager JSM fltk_SHARED fltk_images_SHARED ${X11_LIBRARIES} ${X11_X11_LIB} ${X11_Xpm_LIB})
## Install the binary to bin and the library to lib :)
install(TARGETS jwm-settings-manager JSM
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib/jwm-settings-manager
)

