## Variables in the configure (*.in) files
#####################################################################################
## CLOCK configuration
set(CLOCK_FORMAT "%a, %e %b %l:%M %p")
set(OLD_CLOCK "zenity --calendar --title=\"Calendar\"")
set(OLD_CLOCK_TAG "<Clock format=\"${CLOCK_FORMAT}\">${OLD_CLOCK}</Clock>")
set(EXTENTION "svg")
set(CLOCK "root:c")
set(CLOCK_TAG "<Clock format=\"${CLOCK_FORMAT}\">${CLOCK}</Clock>")
set(TZ_PROG "xterm -e 'sudo dpkg-reconfigure tzdata'")
set(CLOCK_MENU "<!-- Clock Menu-->
    <RootMenu height=\"0\" onroot=\"c\">
        <Program icon=\"time.@EXTENTION@\" label=\"Clock Settings\">jwm-settings-manager --clock-settings</Program>
         <Separator/>
        <Program icon=\"calendar.@EXTENTION@\" label=\"Calendar\">@OLD_CLOCK@</Program>
        <Program icon=\"time.@EXTENTION@\" label=\"Timezone Settings\">@TZ_PROG@</Program>
    </RootMenu>")
## DEFAULT PROGRAMS
set (WEB_PROG "exec:x-www-browser")
set (MANUAL "${WEB_PROG} /usr/share/doc/ToriOS/html/index.html")
set (STARTPAGE "${WEB_PROG} /usr/share/doc/ToriOS/startpage.html")
set (STARTPAGE_ICON "browser.@EXTENTION@")
set (SYS_MONITOR "exec:xterm htop")
set (SCREEN_SHOT "exec:screenie")
set (RUN_DIALOG "exec:zrun")
set (CALC_PROG "exec:xcalc")
set (TERM_PROG "exec:x-terminal-emulator")
set (VOL_UP "exec:amixer-up")
set (VOL_DOWN "exec:amixer-down")
set (VOL_MUTE "exec:amixer-toggle")
set (HELP_PROG "exec:xman")

################### MENUS ###############################
## MAIN MENU
set(TORI_ROOT "root:5")
set(APPMENU_FILE "/etc/jwm/jwm-menu")
set(REGULAR_MENUS_LIST "<!-- NOTE, if you hand edit this root:5 is the app menu and root:7 is the places menu  you have been duly warned :) -->
    <Include>${APPMENU_FILE}</Include>")
set(MENU_NAME "Apps")
set(MENU_ICON "/usr/share/pixmaps/distributor-logo.png")

## PLACES MENU
set(PLACES_ROOT "root:7")
set(PLACES_NAME "Places")
set(PLACES_ICON "folder.@EXTENTION@")

## SHUTDOWN MENU
set(SHUTDOWN_ROOT "root:9")
set(SHUTDOWN_NAME "Shutdown")
set(SHUTDOWN_ICON "system-shutdown.@EXTENTION@")
set (SHUTDOWN_PROGRAM "jwm-settings-manager --halt")
set(LOGOUT_ICON "system-logout.@EXTENTION@")
set(RESTART_ICON "system-restart.@EXTENTION@")
set(RESTART_PROGRAM "torios-reboot")

## window corners override in individual files
set(CORNER "4")
set(W_HEIGHT "20")
## PANEL CONFIGURATIONS
## THE NORMAL CONFIG used in Default, Ambiance and Live
set (DEFAULT_TRAY "    <Tray x=\"0\" y=\"-1\" height=\"34\" valign=\"top\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">
        <TrayButton label=\"${MENU_NAME}\" icon=\"${MENU_ICON}\" border=\"false\">${TORI_ROOT}</TrayButton>
        <TrayButton label=\"${PLACES_NAME}\" icon=\"${PLACES_ICON}\" border=\"false\">${PLACES_ROOT}</TrayButton>
        <TrayButton icon=\"${STARTPAGE_ICON}\" border=\"false\">${STARTPAGE}</TrayButton>
        <Pager labeled=\"true\"/>
        <TaskList maxwidth=\"256\"/>
        <Dock/>
        <Swallow name=\"xload\" width=\"64\">xload -nolabel -bg DimGrey -fg Grey -hl DarkGrey</Swallow>
        ${CLOCK_TAG}
        <TrayButton label=\"${SHUTDOWN_NAME}\" icon=\"${SHUTDOWN_ICON}\" border=\"false\">${SHUTDOWN_ROOT}</TrayButton>
    </Tray>")
### OLD STYLE 2.2.2 configs
set (OLD_DEFAULT_TRAY "    <Tray x=\"0\" y=\"-1\" height=\"34\" valign=\"top\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">
        <TrayButton label=\"${MENU_NAME}\" icon=\"${MENU_ICON}\" border=\"false\">${TORI_ROOT}</TrayButton>
        <TrayButton label=\"${PLACES_NAME}\" icon=\"${PLACES_ICON}\" border=\"false\">${PLACES_ROOT}</TrayButton>
        <TrayButton icon=\"${STARTPAGE_ICON}\" border=\"false\">${STARTPAGE}</TrayButton>
        <Pager labeled=\"true\"/>
        <TaskList maxwidth=\"256\"/>
        <Dock/>
        <Swallow name=\"xload\" width=\"64\">xload -nolabel -bg DimGrey -fg Grey -hl DarkGrey</Swallow>
        ${OLD_CLOCK_TAG}
        <TrayButton label=\"${SHUTDOWN_NAME}\" icon=\"${SHUTDOWN_ICON}\" border=\"false\">${SHUTDOWN_ROOT}</TrayButton>
    </Tray>")

## 'GNOME' MENUS
set(GNOME_MENUS_LIST "<!-- NOTE, if you hand edit this root:5 is the app menu and root:7 is the places menu  you have been duly warned :) root:9 is the system menu -->
    <Include>$HOME/.config/gnomeapps</Include>
    <Include>$HOME/.config/gnomesystem</Include>")
set (GNOME_SYS_ROOT "root:8")
set (GNOME_SYS_NAME "System")
set (GNOME_SYS_ICON "applications-system.@EXTENTION@")

## GNOME TRAYS ############
set (SHOW_DESK_ICON "preferences-system-hotcorners.png")
set (GNOME_TRAY "    <Tray height=\"34\" autohide=\"false\" valign=\"top\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">
        <TrayButton label=\"${MENU_NAME}\" icon=\"${MENU_ICON}\" border=\"false\">${TORI_ROOT}</TrayButton>
	<TrayButton label=\"${GNOME_SYS_NAME}\" icon=\"${GNOME_SYS_ICON}\" border=\"false\">${GNOME_SYS_ROOT}</TrayButton>
        <TrayButton label=\"${PLACES_NAME}\" icon=\"${PLACES_ICON}\" border=\"false\">${PLACES_ROOT}</TrayButton>
        <TrayButton icon=\"${STARTPAGE_ICON}\" border=\"false\">${STARTPAGE}</TrayButton>
        <Spacer/>
        <Dock/>
         ${CLOCK_TAG}
        <TrayButton label=\"${SHUTDOWN_NAME}\" icon=\"${SHUTDOWN_ICON}\" border=\"false\">${SHUTDOWN_ROOT}</TrayButton>
    </Tray>
    <Tray x=\"0\" y=\"-1\" height=\"34\" autohide=\"false\" valign=\"bottom\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">
	<TrayButton icon=\"${SHOW_DESK_ICON}\" border=\"false\">showdesktop</TrayButton>
        <TaskList maxwidth=\"256\"/>
        <Pager labeled=\"false\"/>
    </Tray>")
set (OLD_GNOME_TRAY "    <Tray height=\"34\" autohide=\"false\" valign=\"top\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">
        <TrayButton label=\"${MENU_NAME}\" icon=\"${MENU_ICON}\" border=\"false\">${TORI_ROOT}</TrayButton>
	<TrayButton label=\"${GNOME_SYS_NAME}\" icon=\"${GNOME_SYS_ICON}\" border=\"false\">${GNOME_SYS_ROOT}</TrayButton>
        <TrayButton label=\"${PLACES_NAME}\" icon=\"${PLACES_ICON}\" border=\"false\">${PLACES_ROOT}</TrayButton>
        <TrayButton icon=\"${STARTPAGE_ICON}\" border=\"false\">${STARTPAGE}</TrayButton>
        <Spacer/>
        <Dock/>
         ${OLD_CLOCK_TAG}
        <TrayButton label=\"${SHUTDOWN_NAME}\" icon=\"${SHUTDOWN_ICON}\" border=\"false\">${SHUTDOWN_ROOT}</TrayButton>
    </Tray>
    <Tray x=\"0\" y=\"-1\" height=\"34\" autohide=\"false\" valign=\"bottom\" width=\"0\" halign=\"fixed\" layout=\"horizontal\">
	<TrayButton icon=\"${SHOW_DESK_ICON}\" border=\"false\">showdesktop</TrayButton>
        <TaskList maxwidth=\"256\"/>
        <Pager labeled=\"false\"/>
    </Tray>")

set(LIVE_MENUS_LIST "<!-- NOTE, if you hand edit this root:5 is the app menu and root:7 is the places menu  you have been duly warned :) -->
    <RootMenu onroot=\"1\"/>
    <!-- Main Menu -->
    <Include>${APPMENU_FILE}</Include>
    <!--Shudown Menu-->
    <RootMenu height=\"0\" onroot=\"9\">
        <Program icon=\"${SHUTDOWN_ICON}\" label=\"Shutdown Menu\">${SHUTDOWN_PROGRAM}</Program>
        <Program icon=\"${RESTART_ICON}\" label=\"Restart Computer\">${RESTART_PROGRAM}</Program>
        <Restart label=\"Reload Desktop\" icon=\"${RESTART_ICON}\"/>
    </RootMenu>
        <!--Places Menu-->
    <Include>$HOME/.config/placesmenu</Include>
    <!-- Mouse Menu-->
    <RootMenu height=\"16\" onroot=\"23\">
        <Program icon=\"folder-home.${EXTENTION}\" label=\"Home\">xdg-open ~/</Program>
        <Program icon=\"jwm-settings-manager.${EXTENTION}\" label=\"Settings\">jwm-settings-manager</Program>
        <Program icon=\"preferences-desktop-wallpaper.${EXTENTION}\" label=\"Change Desktop Background\">jwm-settings-manager --desktop</Program>
    </RootMenu>
    ${CLOCK_MENU}")

set(FONT "ubuntu-12:antialias=true:encoding=utf8")
## see http://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
# I tried to implement everything from GNOME, Windows and OSX in here
set(KEYSHORTCUTS "<Key key=\"Up\">up</Key>
    <Key key=\"Down\">down</Key>
    <Key key=\"Right\">right</Key>
    <Key key=\"Left\">left</Key>
    <Key key=\"a\">left</Key>
    <Key key=\"s\">down</Key>
    <Key key=\"w\">up</Key>
    <Key key=\"d\">right</Key>
    <Key key=\"Return\">select</Key>
    <Key key=\"Escape\">escape</Key>
    <Key key=\"XF86AudioMute\">${VOL_MUTE}</Key>
    <Key key=\"XF86AudioRaiseVolume\">${VOL_UP}</Key>
    <Key key=\"XF86AudioLowerVolume\">${VOL_DOWN}</Key>
    <Key key=\"XF86WWW\">${WEB_PROG}</Key>
    <Key key=\"XF86Calculator\">${CALC_PROG}</Key>
    <Key key=\"XF86MonBrightnessUp\">${CALC_PROG}</Key>
    <Key key=\"XF86MonBrightnessDown\">${CALC_PROG}</Key>
    <Key key=\"Print\">${SCREEN_SHOT}</Key>
    <Key mask=\"CA\" key=\"p\">${SCREEN_SHOT}</Key>
    <Key mask=\"S4\" key=\"3\">${SCREEN_SHOT}</Key>
    <Key mask=\"CA\" key=\"t\">${TERM_PROG}</Key>
    <Key mask=\"CS\" key=\"Escape\">${SYS_MONITOR}</Key>
    <Key mask=\"A4\" key=\"Escape\">${SYS_MONITOR}</Key>
    <Key mask=\"CA\" key=\"Delete\">${SYS_MONITOR}</Key>
    <Key mask=\"C\" key=\"Escape\">${SYS_MONITOR}</Key>
    <Key mask=\"A\" key=\"Tab\">next</Key>
    <Key mask=\"4\" key=\"Tab\">next</Key>
    <Key mask=\"AS\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"S4\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"SA\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"CA\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"C\" key=\"#\">desktop#</Key>
    <Key mask=\"A\" key=\"F1\">${HELP_PROG}</Key>
    <Key mask=\"C\" key=\"Escape\">${TORI_ROOT}</Key>
    <Key mask=\"A\" key=\"F2\">${RUN_DIALOG}</Key>
    <Key mask=\"4\" key=\"F2\">${RUN_DIALOG}</Key>
    <Key mask=\"4\" key=\"space\">${RUN_DIALOG}</Key>
    <Key mask=\"CA\" key=\"Right\">rdesktop</Key>
    <Key mask=\"CA\" key=\"Left\">ldesktop</Key>
    <Key mask=\"CA\" key=\"Up\">udesktop</Key>
    <Key mask=\"CA\" key=\"Down\">ddesktop</Key>
    <Key mask=\"A\" key=\"space\">window</Key>
    <Key mask=\"A\" key=\"F3\">window</Key>
    <Key key=\"F11\">fullscreen</Key>
    <Key mask=\"C\" key=\"F11\">fullscreen</Key>
    <Key mask=\"CS\" key=\"f\">fullscreen</Key>
    <Key mask=\"4C\" key=\"f\">fullscreen</Key>
    <Key mask=\"A\" key=\"F12\">shade</Key>
    <Key mask=\"SC4\" key=\"Up\">maximize</Key>
    <Key mask=\"4\" key=\"L\">maximize</Key>
    <Key mask=\"A\" key=\"F10\">maximize</Key>
    <Key mask=\"4\" key=\"Down\">minimize</Key>
    <Key mask=\"4\" key=\"m\">minimize</Key>
    <Key mask=\"A\" key=\"F9\">minimize</Key>
    <Key mask=\"4\" key=\"w\">close</Key>
    <Key mask=\"A\" key=\"F4\">close</Key>")
set(NEW_KEYSHORTCUTS "${KEYSHORTCUTS}
    <Key mask=\"C4\" key=\"Up\">maxtop</Key>
    <Key mask=\"C4\" key=\"Left\">maxleft</Key>
    <Key mask=\"C4\" key=\"Right\">maxright</Key>
    <Key mask=\"C4\" key=\"Down\">maxbottom</Key>
    <Key mask=\"C4\" key=\"v\">maxv</Key>
    <Key mask=\"4S\" key=\"Up\">maxv</Key>
    <Key mask=\"C4\" key=\"h\">maxh</Key>
    <Key mask=\"4\" key=\"Right\">sendr</Key>
    <Key mask=\"4\" key=\"Left\">sendl</Key>
    <Key mask=\"4\" key=\"Up\">sendu</Key>
    <Key mask=\"4\" key=\"Down\">sendd</Key>
    <Key mask=\"SCA\" key=\"Right\">sendr</Key>
    <Key mask=\"SCA\" key=\"Left\">sendl</Key>
    <Key mask=\"SCA\" key=\"Up\">sendu</Key>
    <Key mask=\"SCA\" key=\"Down\">sendd</Key>")

set(ICONS_LIST "  <IconPath>/usr/share/icons/Numix-Circle/16x16/apps</IconPath>
  <IconPath>/usr/share/icons/Numix-Circle/scalable/apps</IconPath>
  <IconPath>/usr/share/icons/Numix-Circle/16x16/apps</IconPath>
  <IconPath>/usr/share/icons/Numix-Circle/scalable/apps</IconPath>
<!-- Inherited Icons -->
  <IconPath>/usr/share/app-install/icons</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/actions</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/animations</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/categories</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/devices</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/emblems</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/mimetypes</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/places</IconPath>
  <IconPath>/usr/share/icons/Numix/256x256/status</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/actions</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/animations</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/apps</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/categories</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/devices</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/emblems</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/mimetypes</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/places</IconPath>
  <IconPath>/usr/share/icons/Numix/32x32/status</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/actions</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/apps</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/categories</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/devices</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/emblems</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/mimetypes</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/places</IconPath>
  <IconPath>/usr/share/icons/Numix/scalable/status</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/actions</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/apps</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/categories</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/devices</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/emblems</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/mimetypes</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/places</IconPath>
  <IconPath>/usr/share/icons/gnome/256x256/status</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/actions</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/animations</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/apps</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/categories</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/devices</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/emblems</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/mimetypes</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/places</IconPath>
  <IconPath>/usr/share/icons/gnome/32x32/status</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/actions</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/apps</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/categories</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/devices</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/emblems</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/mimetypes</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/places</IconPath>
  <IconPath>/usr/share/icons/gnome/scalable/status</IconPath>
  <IconPath>/usr/share/icons/hicolor/256x256/apps</IconPath>
  <IconPath>/usr/share/icons/hicolor/256x256/mimetypes</IconPath>
  <IconPath>/usr/share/icons/hicolor/32x32/actions</IconPath>
  <IconPath>/usr/share/icons/hicolor/32x32/apps</IconPath>
  <IconPath>/usr/share/icons/hicolor/32x32/categories</IconPath>
  <IconPath>/usr/share/icons/hicolor/32x32/devices</IconPath>
  <IconPath>/usr/share/icons/hicolor/32x32/emblems</IconPath>
  <IconPath>/usr/share/icons/hicolor/32x32/mimetypes</IconPath>
  <IconPath>/usr/share/icons/hicolor/32x32/status</IconPath>
  <IconPath>/usr/share/icons/hicolor/512x512/apps</IconPath>
  <IconPath>/usr/share/icons/hicolor/512x512/mimetypes</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/actions</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/apps</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/categories</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/devices</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/emblems</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/mimetypes</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/places</IconPath>
  <IconPath>/usr/share/icons/hicolor/scalable/status</IconPath>
  <IconPath>/usr/share/icons</IconPath>
  <IconPath>/usr/share/pixmaps</IconPath>")

set(MOUSE "<DoubleClickSpeed>400</DoubleClickSpeed>
    <DoubleClickDelta>2</DoubleClickDelta>")
set (STARTUP "<StartupCommand>pcmanfm --desktop</StartupCommand>
   <StartupCommand>$HOME/.config/jsm-mouse</StartupCommand>
   <StartupCommand>nm-applet</StartupCommand>
   <StartupCommand>/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1</StartupCommand>")
set (GROUPS "<Group>
        <Option>noshade</Option>
    </Group>
    <Group>
        <Class>Pidgin</Class>
        <Option>sticky</Option>
    </Group>
    <Group>
        <Name>gkrellm</Name>
        <Option>nolist</Option>
        <Option>sticky</Option>
    </Group>
    <Group>
        <Name>conky</Name>
        <Option>nolist</Option>
        <Option>sticky</Option>
    </Group>")
set(BUTTONS "<ButtonClose>/usr/share/jwm-settings-manager/Buttons/Default/close.png</ButtonClose>
    <ButtonMax>/usr/share/jwm-settings-manager/Buttons/Default/max.png</ButtonMax>
    <ButtonMaxActive>/usr/share/jwm-settings-manager/Buttons/Default/max-toggle.png</ButtonMaxActive>
    <ButtonMin>/usr/share/jwm-settings-manager/Buttons/Default/min.png</ButtonMin>")
set(BG "/usr/share/backgrounds/default.jpg")
#####################################################################################
### End Variables

#include the cmakelists in each dir for the custom colours
add_subdirectory(Default)
add_subdirectory(Ambiance)
add_subdirectory(DarkGnome2)
add_subdirectory(LightGnome2)
add_subdirectory(Bassem)
add_subdirectory(Numix)
## add your theme below to have it automatically added to the -common.install file
# FORMAT:
# data/themes/YOUR_THEME_NAME/ usr/share/${EXEC}/themes/

set(COMMON_INSTALL "data/themes/old/ usr/share/${EXEC}/themes/
data/themes/Default/ usr/share/${EXEC}/themes/
data/themes/Ambiance/ usr/share/${EXEC}/themes/
data/themes/DarkGnome2/ usr/share/${EXEC}/themes/
data/themes/LightGnome2/ usr/share/${EXEC}/themes/
data/themes/Bassem/ usr/share/${EXEC}/themes/
data/themes/Numix/ usr/share/${EXEC}/themes/")

# configure the file
set(COMMON_FILE "../../debian/${EXEC}-common.install")
configure_file(${COMMON_FILE}.in ${COMMON_FILE})
