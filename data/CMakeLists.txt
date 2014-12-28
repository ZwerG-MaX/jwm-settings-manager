set(HOME "$ENV{HOME}")
#substitute variables in the desktop file
set(DESKTOP_FILE "${CMAKE_PROJECT_NAME}.desktop")
set(CLOCK "xclock")
set(SCREENIE "screenie")
set(VOLUME "volumeicon")
set(WIFI "nm-applet")
set(BG "/usr/share/backgrounds/default.png")
set(FONT "ubuntu-12:antialias=true:encoding=utf8")
set(DEFAULT_THEME "themes/Default/Default")
set(Ambiance_THEME "themes/Ambiance/Ambiance")
set(DARK_GNOME_THEME "themes/DarkGnome2/DarkGnome2")
set(GNOME_THEME "themes/LightGnome2/LightGnome2")
set(Bassem_THEME "themes/Bassem/Bassem")
configure_file(${Bassem_THEME}.in ${Bassem_THEME})
configure_file(${Ambiance_THEME}.in ${Ambiance_THEME})
configure_file(${GNOME_THEME}.in ${GNOME_THEME})
configure_file(${DARK_GNOME_THEME}.in ${DARK_GNOME_THEME})
configure_file(${DEFAULT_THEME}.in ${DEFAULT_THEME})
configure_file(${DESKTOP_FILE}.in ${DESKTOP_FILE})
FILE(GLOB APPS "*.desktop")
FILE(GLOB ICONS "icons/*.svg")
FILE(GLOB ICONS_PNG "icons/*.png")

#install menu 
install (FILES toriOSmenu DESTINATION /etc/menu-methods)
install (FILES places DESTINATION /etc/menu-methods)
install (DIRECTORY desktop-directories DESTINATION /usr/share/)
#install themes 
install (DIRECTORY themes DESTINATION share/jwm-settings-manager)
#default rox file
install (FILES pb_JWM DESTINATION share/jwm-settings-manager)
#touchpad scripts
install (FILES touchpad_status DESTINATION /usr/bin)
install (FILES touchpad_toggle DESTINATION /usr/bin)
#torios/JSM logos
install(FILES icons/jwm-settings-manager.png icons/jwm-settings-manager.xpm DESTINATION share/pixmaps)
install(FILES ${ICONS} DESTINATION usr/share/icons/jsm)
install(FILES ${ICONS_PNG} DESTINATION usr/share/icons/jsm)
#desktop file installer
#install(FILES ${DESKTOP_FILE} DESTINATION share/applications)
install(FILES ${APPS} DESTINATION share/applications)
#install Buttons
install(DIRECTORY Buttons DESTINATION share/jwm-settings-manager)

