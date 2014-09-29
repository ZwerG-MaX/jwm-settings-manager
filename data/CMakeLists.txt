set(HOME "$ENV{HOME}")
#substitute variables in the desktop file
set(DESKTOP_FILE "${CMAKE_PROJECT_NAME}.desktop")
configure_file(${DESKTOP_FILE}.in ${DESKTOP_FILE})
FILE(GLOB APPS "*.desktop")

#install menu 
install (FILES toriOSmenu DESTINATION /etc/menu-methods)
install (DIRECTORY desktop-directories DESTINATION /usr/share/)
#install themes 
install (DIRECTORY themes DESTINATION share/jwm-settings-manager)
#default rox file
install (FILES pb_JWM DESTINATION share/jwm-settings-manager)
#touchpad scripts
install (FILES touchpad_status DESTINATION /usr/bin)
install (FILES touchpad_toggle DESTINATION /usr/bin)
#torios/JSM logos
install(FILES distributor-logo.png jwm-settings-manager.png jwm-settings-manager.xpm DESTINATION share/pixmaps)
install(FILES jwm-settings-manager.png DESTINATION icons)
install(FILES jwm-settings-manager.svg DESTINATION icons)
#desktop file installer
#install(FILES ${DESKTOP_FILE} DESTINATION share/applications)
install(FILES ${APPS} DESTINATION share/applications)
#install Buttons
install(DIRECTORY Buttons DESTINATION share/jwm-settings-manager)

