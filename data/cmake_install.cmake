# Install script for directory: /home/lovejesus/computerstuff/bzr/jwm-settings-manager/data

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/bin" TYPE FILE FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/jwmIconFinder")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE DIRECTORY FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/themes")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE FILE FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/pb_JWM")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pixmaps" TYPE FILE FILES
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jwm-settings-manager.png"
    "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/icons/jwm-settings-manager.xpm"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/share/icons/hicolor/scalable/apps" TYPE FILE FILES
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
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/share/icons/hicolor/48x48/apps" TYPE FILE FILES
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
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/share/pixmaps" TYPE FILE FILES
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
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications" TYPE FILE FILES
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
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE DIRECTORY FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/Buttons")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/jwm-settings-manager" TYPE FILE FILES "/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/time")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/lovejesus/computerstuff/bzr/jwm-settings-manager/data/themes/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

