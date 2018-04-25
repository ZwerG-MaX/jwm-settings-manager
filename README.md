[![Build Status](https://travis-ci.org/Israel-D/jwm-settings-manager.svg?branch=master)](https://travis-ci.org/Israel-D/jwm-settings-manager)

# JWM Settings Manager
Build Depends on Debian/Ubuntu
- cmake
- gcc-multilib [amd64]
- g++-multilib [amd64]
- libc6
- libfltk-images1.3
- libfltk1.3
- libfltk1.3-dev
- libfltk1.3-compat-headers
- libgcc1
- libstdc++6
- libx11-dev
- libxpm-dev
- fluid
- pkg-config

This program requires an out of source build, so create a build directory, for example:
`mkdir -p bin/Release`
then enter the directory and configure it with cmake
```
cd bin/Release
cmake ../..
```
Then once it configures run make
You can then run
`sudo make install`
to install all the common things (themes, etc...)
You may also view the functions and variable status by using the `--debug` option
This can be used to document any issues you encounter.
For example
`./jwm-settings-manager --debug > jwm-settings-manager.log`
will save all the output to a file.

### Command Line Options
jwm-settings-manager will open the Main settings screen if no options are supplied
configure JWM easily

Options:
```
 -a --autostart   show autostart settings
 -d --desktop     show desktop settings
 -f --font        show font settings
 -h --help        show this listing
 -i --icons       show icon settings
 -k --keyboard    show keyboard settings
 -m --mouse       show mouse settings
 -p --panel       show panel settings
 -t --themes      show theme settings
 -w --window      show window settings
 --popups        show popups window
 -v --version     show current version
 -c --copyright   show copyright information
 --debug        show debugging output
 SHORTCUTS FOR USE IN THE PANELS AND MENUS
 --shutdown --halt   show shutdown menu
 -u --menu        show menu editor
 -l --clock        show clock settings
 -s --shortcuts         show shortcut editor
```
## Panel
![Alt text](/screenshots/panel.png?raw=true "Panel Window") ![Alt text](/screenshots/panel-appearance.png?raw=true "Panel Appearance") ![Alt text](/screenshots/panel-size.png?raw=true "Panel Size")

This portion allows you to configure the Menus, Application launchers, indicators, pager, appearance, sizing and position, etc..

## Desktop
![Alt text](/screenshots/desktop.png?raw=true "Desktop Window")

This allows you to change the background, and amount of virtual desktops.
It also supports filemanagers creating the desktop background (pcmanfm and gsettings... i.e. thunar/nautilus/etc..)

## Windows
![Alt text](/screenshots/windows.png?raw=true "Windows Window") ![Alt text](/screenshots/windows-settings.png?raw=true "Windows Settings") ![Alt text](/screenshots/windows-actions.png?raw=true "Window Actions") ![Alt text](/screenshots/windows-groups.png?raw=true "Windows Groups") ![Alt text](/screenshots/windows-advanced.png?raw=true "Windows Advanced")

This allows you to change the window buttons, appearance, and configure window groups
You can also change the GTK widget theme.  The newest version also allow configuring Mouse context actions for the window buttons

## Keyboard
![Alt text](/screenshots/keyboard.png?raw=true "Keyboard Window")

This allows you to change keyboard shortcuts.
There is a 'key grabber' for combinations, as well as a drop down for XF86 keys
![Alt text](/screenshots/keyboard-grabber.png?raw=true "Keyboard Grabber")
There is also a preliminary effort to configure keyboard layout.

## Touchpad
![Alt text](/screenshots/touchpad.png?raw=true "Touchpad Window")

This allows you to configure your touchpad.
It also configures the JWM options, and if no touchpad exists only JWM options will be shown

## Themes
![Alt text](/screenshots/themes.png?raw=true "Themes Window")

Switch between a few premade themes, with support for user themes in
~/.themes

## Icons
![Alt text](/screenshots/icons.png?raw=true "Icons Window")

Change JWM icons.  You can manually edit the lines, or simply change GTK icon theme

## Fonts
![Alt text](/screenshots/fonts.png?raw=true "Fonts Window")

Configure all fonts (and font colors) used in JWM through a graphical font manager.  You can also choose the GTK interior window fonts.

![Alt text](/screenshots/fonts-subwin.png?raw=true "Fonts Chooser Window")

You may control many aspects of the font using the advanced options (many Xft font options are supported)

![Alt text](/screenshots/fonts-subwin-advanced.png?raw=true "Fonts Chooser Window - Advanced")

## Autostart
![Alt text](/screenshots/autostart.png?raw=true "Autostart Window")

Configure and edit all JWM Startup commands, as well as handle XDG autostart through the desktop-file-editor (via pkexec, for system files)

## Desktop File Editor
![Alt text](/screenshots/desktop-file-editor.png?raw=true "Desktop File Editor Window")

A very full featured desktop file editor offering the ability to edit almost everything possible in a desktop file.

## Menus
![Alt text](/screenshots/menus.png?raw=true "Menus Window")

Edit menus, and configure menu items easily

## Clock Settings
![Alt text](/screenshots/clock.png?raw=true "Clock Settings Window")

Edit the clock display easily, and modify timezone settings quickly

## Shutdown window
![Alt text](/screenshots/shutdown.png?raw=true "Shutdown Window")

This launches a variety of programs to control shutdown/suspend/logout from a JWM/ToriOS session

## Popups window
![Alt text](/screenshots/popups.png?raw=true "Popups Window")

Edit the JWM tooltip popups, as well as dunst Notifications (if dunst is installed)
