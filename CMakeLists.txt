cmake_minimum_required(VERSION 2.8)
project(jwm-settings-manager CXX C)
set(PROJECT_NAME jwm-settings-manager)
SET(VERSION "0.043")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

INCLUDE(AddFileDependencies)
INCLUDE(CheckIncludeFiles)
INCLUDE(FindPkgConfig)

set(ICON "jwm-settings-manager")
set(EXEC "jwm-settings-manager")

#compiler and linker
FIND_PACKAGE(FLTK REQUIRED NO_MODULE)
FIND_PACKAGE(X11 REQUIRED)
set(FLTK_SKIP_OPENGL True)
set(FLTK_SKIP_FLUID True)
set(CMAKE_INSTALL_PREFIX "/usr")
#add_compile_options($<CONFIGURATION> "Unix Makefile")
FILE(RELATIVE_PATH LIB_DIR_RELATIVE "/${BIN_DIR}" "/${LIB_DIR}")

set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CONFIGURATION_TYPE "RELEASE")

INCLUDE_DIRECTORIES("${FLTK_INCLUDE_DIR}"
		    "${X11_INCLUDE_DIR}"
                    "${CMAKE_SOURCE_DIR}/include"
                    "${CMAKE_SOURCE_DIR}/fltk"
		    "${CMAKE_BINARY_DIR}/fltk"
                    "${CMAKE_BINARY_DIR}/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(
	JSM_SRCS
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
	fltk/jwm-panel.cxx
	fltk/jwm-settings.cxx
	fltk/jwm-themes.cxx
	fltk/jwm-window.cxx
	fltk/jwm-shutdown.cxx
)
add_library(JSM STATIC ${JSM_SRCS})
add_subdirectory(data)
add_executable(jwm-settings-manager src/jwm.cpp)
TARGET_LINK_LIBRARIES(jwm-settings-manager JSM fltk_SHARED fltk_images_SHARED ${X11_LIBRARIES})
install(TARGETS jwm-settings-manager JSM
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib/jwm-settings-manager
)

