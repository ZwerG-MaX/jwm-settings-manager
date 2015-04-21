## Variables in the configure (*.in) files
#####################################################################################
set(CLOCK "zenity --calendar --title=\"Calendar\"")
set(ICONS_LIST "<IconPath>/usr/share/pixmaps/</IconPath>
    <IconPath>/usr/share/icons/jsm/</IconPath>
    <IconPath>/usr/share/icons/</IconPath>
    <IconPath>/usr/share/icons/Numix/48x48/actions/</IconPath>
    <IconPath>/usr/share/icons/Numix/48x48/categories/</IconPath>
    <IconPath>/usr/share/icons/Numix/48x48/places/</IconPath>
    <IconPath>/usr/share/icons/Numix/48x48/status/</IconPath>
    <IconPath>/usr/share/icons/Numix-Circle/48x48/apps</IconPath>")
set(MENUS_LIST "<!-- NOTE, if you hand edit this root:5 is the app menu and root:7 is the places menu  you have been duly warned :) -->
    <RootMenu onroot=\"1\"/>
    <!-- Main Menu -->
    <Include>$HOME/.config/torimenu</Include>
    <!--Shudown Menu-->
    <RootMenu height=\"0\" onroot=\"9\">
        <Program icon=\"preferences-system-session.svg\" label=\"Shutdown Menu\">jwm-settings-manager --halt</Program>
        <Program icon=\"system-restart.svg\" label=\"Restart Computer\">dbus-send --system --print-reply --dest=org.freedesktop.ConsoleKit /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Restart</Program>
        <Restart label=\"Reload Desktop\" icon=\"system-restart.svg\"/>
        <Exit label=\"Logout\" confirm=\"true\" icon=\"system-logout.svg\"/>
    </RootMenu>
        <!--Places Menu-->
    <Include>$HOME/.config/placesmenu</Include>
    <!-- Mouse Menu-->
    <RootMenu height=\"16\" onroot=\"23\">
        <Program icon=\"application-default-icon.svg\" label=\"Applications\">xdg-open /usr/share/applications</Program>
        <Program icon=\"folder-home.svg\" label=\"Home\">xdg-open ~/</Program>
        <Program icon=\"jwm-settings-manager.svg\" label=\"Settings\">jwm-settings-manager</Program>
        <Program icon=\"preferences-desktop-wallpaper.svg\" label=\"Change Desktop Background\">jwm-settings-manager --desktop</Program>
    </RootMenu>")
set(LIVE_MENUS_LIST "<!-- NOTE, if you hand edit this root:5 is the app menu and root:7 is the places menu  you have been duly warned :) -->
    <RootMenu onroot=\"1\"/>
    <!-- Main Menu -->
    <Include>$HOME/.config/torimenu</Include>
    <!--Shudown Menu-->
    <RootMenu height=\"0\" onroot=\"9\">
        <Program icon=\"preferences-system-session.svg\" label=\"Shutdown NOW\">shutdown -h now</Program>
        <Program icon=\"system-restart.svg\" label=\"Restart Computer\">shutdown -r now</Program>
        <Restart label=\"Reload Desktop\" icon=\"system-restart.svg\"/>
        <Exit label=\"Logout\" confirm=\"true\" icon=\"system-logout.svg\"/>
    </RootMenu>
        <!--Places Menu-->
    <Include>$HOME/.config/placesmenu</Include>
    <!-- Mouse Menu-->
    <RootMenu height=\"16\" onroot=\"23\">
        <Program icon=\"application-default-icon.svg\" label=\"Applications\">xdg-open /usr/share/applications</Program>
        <Program icon=\"folder-home.svg\" label=\"Home\">xdg-open ~/</Program>
        <Program icon=\"jwm-settings-manager.svg\" label=\"Settings\">jwm-settings-manager</Program>
        <Program icon=\"preferences-desktop-wallpaper.svg\" label=\"Change Desktop Background\">jwm-settings-manager --desktop</Program>
    </RootMenu>")
set(GNOME_MENUS_LIST "<!-- NOTE, if you hand edit this root:5 is the app menu and root:7 is the places menu  you have been duly warned :) -->
    <RootMenu onroot=\"1\"/>
    <!-- Main Menu -->
    <Include>$HOME/.config/gnomeapps</Include>
    <Include>$HOME/.config/gnomesystem</Include>
    <!--Shudown Menu-->
    <RootMenu height=\"0\" onroot=\"9\">
        <Program icon=\"preferences-system-session.svg\" label=\"Shutdown Menu\">jwm-settings-manager --halt</Program>
        <Program icon=\"system-restart.svg\" label=\"Restart Computer\">dbus-send --system --print-reply --dest=org.freedesktop.ConsoleKit /org/freedesktop/ConsoleKit/Manager org.freedesktop.ConsoleKit.Manager.Restart</Program>
        <Restart label=\"Reload Desktop\" icon=\"system-restart.svg\"/>
        <Exit label=\"Logout\" confirm=\"true\" icon=\"system-logout.svg\"/>
    </RootMenu>
        <!--Places Menu-->
    <Include>$HOME/.config/placesmenu</Include>
    <!-- Mouse Menu-->
    <RootMenu height=\"16\" onroot=\"23\">
        <Program icon=\"application-default-icon.svg\" label=\"Applications\">xdg-open /usr/share/applications</Program>
        <Program icon=\"folder-home.svg\" label=\"Home\">xdg-open ~/</Program>
        <Program icon=\"jwm-settings-manager.svg\" label=\"Settings\">jwm-settings-manager</Program>
        <Program icon=\"preferences-desktop-wallpaper.svg\" label=\"Change Desktop Background\">jwm-settings-manager --desktop</Program>
    </RootMenu>")
## see http://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts
# I tried to implement everything from Windows and OSX in here

set(NEW_KEYSHORTCUTS "<Key key=\"Up\">up</Key>
    <Key key=\"Down\">down</Key>
    <Key key=\"Right\">right</Key>
    <Key key=\"Left\">left</Key>
    <Key key=\"a\">left</Key>
    <Key key=\"s\">down</Key>
    <Key key=\"w\">up</Key>
    <Key key=\"d\">right</Key>
    <Key key=\"Return\">select</Key>
    <Key key=\"Escape\">escape</Key>
    <Key key=\"XF86AudioMute\">exec:amixer -q sset Master toggle</Key>
    <Key key=\"XF86AudioRaiseVolume\">exec:amixer -q sset Master 3%+ unmute</Key>
    <Key key=\"XF86AudioLowerVolume\">exec:amixer -q sset Master 3%- unmute</Key>
    <Key key=\"XF86WWW\">exec:sensible-browser</Key>
    <Key key=\"XF86Calculator\">exec:xcalc</Key>
    <Key key=\"XF86MonBrightnessUp\">exec:xcalc</Key>
    <Key key=\"XF86MonBrightnessDown\">exec:xcalc</Key>
    <Key key=\"Print\">exec:screenie</Key>
    <Key mask=\"CA\" key=\"p\">exec:screenie</Key>
    <Key mask=\"S4\" key=\"3\">exec:screenie</Key>
    <Key mask=\"CA\" key=\"t\">exec:x-terminal-emulator</Key>
    <Key mask=\"CS\" key=\"Escape\">exec:xterm htop</Key>
    <Key mask=\"A4\" key=\"Escape\">exec:xterm htop</Key>
    <Key mask=\"CA\" key=\"Delete\">exec:xterm htop</Key>
    <Key mask=\"C\" key=\"Escape\">exec:xterm htop</Key>
    <Key mask=\"A\" key=\"Tab\">next</Key>
    <Key mask=\"4\" key=\"Tab\">next</Key>
    <Key mask=\"AS\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"S4\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"SA\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"CA\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"C\" key=\"#\">desktop#</Key>
    <Key mask=\"A\" key=\"F1\">root:1</Key>
    <Key mask=\"C\" key=\"Escape\">root:5</Key>
    <Key mask=\"A\" key=\"F2\">exec:zrun</Key>
    <Key mask=\"4\" key=\"F2\">exec:zrun</Key>
    <Key mask=\"4\" key=\"R\">exec:zrun</Key>
    <Key mask=\"4\" key=\"space\">exec:zrun</Key>
    <Key mask=\"CA\" key=\"Right\">rdesktop</Key>
    <Key mask=\"CA\" key=\"Left\">ldesktop</Key>
    <Key mask=\"CA\" key=\"Up\">udesktop</Key>
    <Key mask=\"CA\" key=\"Down\">ddesktop</Key>
    <Key mask=\"A\" key=\"space\">window</Key>
    <Key mask=\"A\" key=\"F3\">window</Key>
    <Key key=\"F11\">fullscreen</Key>
    <Key mask=\"C\" key=\"F11\">fullscreen</Key>
    <Key mask=\"CS\" key=\"f\">fullscreen</Key>
    <Key mask=\"4S\" key=\"f\">fullscreen</Key>
    <Key mask=\"A\" key=\"F12\">shade</Key>
    <Key mask=\"4\" key=\"Up\">maximize</Key>
    <Key mask=\"4\" key=\"L\">maximize</Key>
    <Key mask=\"A\" key=\"F10\">maximize</Key>
    <Key mask=\"S4\" key=\"Down\">minimize</Key>
    <Key mask=\"4\" key=\"m\">minimize</Key>
    <Key mask=\"A\" key=\"F9\">minimize</Key>
    <Key mask=\"4\" key=\"w\">close</Key>
    <Key mask=\"A\" key=\"F4\">close</Key>
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
    <Key key=\"XF86AudioMute\">exec:amixer -q sset Master toggle</Key>
    <Key key=\"XF86AudioRaiseVolume\">exec:amixer -q sset Master 3%+ unmute</Key>
    <Key key=\"XF86AudioLowerVolume\">exec:amixer -q sset Master 3%- unmute</Key>
    <Key key=\"XF86WWW\">exec:sensible-browser</Key>
    <Key key=\"XF86Calculator\">exec:xcalc</Key>
    <Key key=\"XF86MonBrightnessUp\">exec:xcalc</Key>
    <Key key=\"XF86MonBrightnessDown\">exec:xcalc</Key>
    <Key key=\"Print\">exec:screenie</Key>
    <Key mask=\"CA\" key=\"p\">exec:screenie</Key>
    <Key mask=\"S4\" key=\"3\">exec:screenie</Key>
    <Key mask=\"CA\" key=\"t\">exec:x-terminal-emulator</Key>
    <Key mask=\"CS\" key=\"Escape\">exec:xterm htop</Key>
    <Key mask=\"A4\" key=\"Escape\">exec:xterm htop</Key>
    <Key mask=\"CA\" key=\"Delete\">exec:xterm htop</Key>
    <Key mask=\"C\" key=\"Escape\">exec:xterm htop</Key>
    <Key mask=\"A\" key=\"Tab\">next</Key>
    <Key mask=\"4\" key=\"Tab\">next</Key>
    <Key mask=\"AS\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"S4\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"SA\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"CA\" key=\"Tab\">nextstacked</Key>
    <Key mask=\"C\" key=\"#\">desktop#</Key>
    <Key mask=\"A\" key=\"F1\">root:1</Key>
    <Key mask=\"C\" key=\"Escape\">root:5</Key>
    <Key mask=\"A\" key=\"F2\">exec:zrun</Key>
    <Key mask=\"4\" key=\"F2\">exec:zrun</Key>
    <Key mask=\"4\" key=\"space\">exec:zrun</Key>
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
    <Key mask=\"4\" key=\"Up\">maximize</Key>
    <Key mask=\"4\" key=\"L\">maximize</Key>
    <Key mask=\"A\" key=\"F10\">maximize</Key>
    <Key mask=\"4\" key=\"Down\">minimize</Key>
    <Key mask=\"4\" key=\"m\">minimize</Key>
    <Key mask=\"A\" key=\"F9\">minimize</Key>
    <Key mask=\"4\" key=\"w\">close</Key>
    <Key mask=\"A\" key=\"F4\">close</Key>")
set(MOUSE "<DoubleClickSpeed>400</DoubleClickSpeed>
    <DoubleClickDelta>2</DoubleClickDelta>")
set (STARTUP "<StartupCommand>pcmanfm --desktop</StartupCommand>
   <StartupCommand>$HOME/.config/jsm-mouse</StartupCommand>
   <StartupCommand>nm-applet</StartupCommand>
   <StartupCommand>/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1</StartupCommand>")
set (GROUPS "<Group>
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
    </Group>
    <Group>
        <Name>jwm-settings-manager</Name>
        <Option>icon:jwm-settings-manager.svg</Option>
    </Group>")
set(DEFAULT_BUTTONS "<ButtonClose>/usr/share/jwm-settings-manager/Buttons/Default/close.png</ButtonClose>
    <ButtonMax>/usr/share/jwm-settings-manager/Buttons/Default/max.png</ButtonMax>
    <ButtonMaxActive>/usr/share/jwm-settings-manager/Buttons/Default/max-toggle.png</ButtonMaxActive>
    <ButtonMin>/usr/share/jwm-settings-manager/Buttons/Default/min.png</ButtonMin>")
set (MANUAL "exec:x-www-browser /usr/share/doc/ToriOS/html/index.html")
set (STARTPAGE "exec:x-www-browser /usr/share/doc/ToriOS/startpage.html")
set(BG "/usr/share/backgrounds/default.jpg")
set(FONT "ubuntu-12:antialias=true:encoding=utf8")
#####################################################################################
### End Variables


### SETUP THEME NAMES
#set(BASE_THEME "base-theme.in") #eventually use this to configure all themes
set(LIVE_THEME "../live.jwmrc")
set(DEFAULT_THEME "Default/Default")
set(Ambiance_THEME "Ambiance/Ambiance")
set(DARK_GNOME_THEME "DarkGnome2/DarkGnome2")
set(GNOME_THEME "LightGnome2/LightGnome2")
set(Bassem_THEME "Bassem/Bassem")

### CONFIGURE THEMES
configure_file(${LIVE_THEME}.in ${LIVE_THEME})
configure_file(${Bassem_THEME}.in ${Bassem_THEME})
configure_file(${Ambiance_THEME}.in ${Ambiance_THEME})
configure_file(${GNOME_THEME}.in ${GNOME_THEME})
configure_file(${DARK_GNOME_THEME}.in ${DARK_GNOME_THEME})
configure_file(${DEFAULT_THEME}.in ${DEFAULT_THEME})

### SETUP OLD THEME NAMES
set(OLD_DEFAULT_THEME "old/Default/Default")
set(OLD_Ambiance_THEME "old/Ambiance/Ambiance")
set(OLD_DARK_GNOME_THEME "old/DarkGnome2/DarkGnome2")
set(OLD_GNOME_THEME "old/LightGnome2/LightGnome2")
set(OLD_Bassem_THEME "old/Bassem/Bassem")
### CONFIGURE OLD THEMES
configure_file(${OLD_Bassem_THEME}.in ${OLD_Bassem_THEME})
configure_file(${OLD_Ambiance_THEME}.in ${OLD_Ambiance_THEME})
configure_file(${OLD_GNOME_THEME}.in ${OLD_GNOME_THEME})
configure_file(${OLD_DARK_GNOME_THEME}.in ${OLD_DARK_GNOME_THEME})
configure_file(${OLD_DEFAULT_THEME}.in ${OLD_DEFAULT_THEME})
