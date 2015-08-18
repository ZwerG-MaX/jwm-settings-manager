# Install script for directory: /home/lovejesus/computerstuff/bzr/jwm-settings-manager/data

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/bin" TYPE FILE FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwmIconFinder")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE DIRECTORY FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/themes")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE FILE FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/pb_JWM")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pixmaps" TYPE FILE FILES
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jwm-settings-manager.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jwm-settings-manager.xpm"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/share/icons/hicolor/scalable/apps" TYPE FILE FILES
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-fonts.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-icons.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-windows.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-keyboard.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-panel.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-autostart.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jwm-settings-manager.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-mouse.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-desktop.svg"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-theme.svg"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/share/icons/hicolor/48x48/apps" TYPE FILE FILES
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-desktop.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-windows.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-keyboard.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-autostart.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-fonts.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-icons.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-mouse.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-panel.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jwm-settings-manager.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-theme.png"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/share/pixmaps" TYPE FILE FILES
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-fonts.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-desktop.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jwm-settings-manager.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-autostart.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-theme.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-icons.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-windows.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-panel.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-mouse.xpm"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jsm-keyboard.xpm"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications" TYPE FILE FILES
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-autostart.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-icons.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-fonts.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-desktop.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-themes.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-mouse.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-keyboard.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-window.desktop"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwm-settings-manager-panel.desktop"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE DIRECTORY FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/Buttons")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE FILE FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/time")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/themes/cmake_install.cmake")

endif()

