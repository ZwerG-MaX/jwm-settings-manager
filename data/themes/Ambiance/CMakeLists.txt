## Variables in the configure (*.in) files
#####################################################################################
set(THIS_THEME "Ambiance")
#####################################################################################
### End Variables
set(TRAY "${DEFAULT_TRAY}")
set (OLD_TRAY "${OLD_DEFAULT_TRAY}")
set(MENUS_LIST "${REGULAR_MENUS_LIST}")
set(BUTTONS "<ButtonClose>/usr/share/jwm-settings-manager/Buttons/Ambiance/close.png</ButtonClose>
    <ButtonMax>/usr/share/jwm-settings-manager/Buttons/Ambiance/max.png</ButtonMax>
    <ButtonMaxActive>/usr/share/jwm-settings-manager/Buttons/Ambiance/max_toggled.png</ButtonMaxActive>
    <ButtonMin>/usr/share/jwm-settings-manager/Buttons/Ambiance/iconify.png</ButtonMin>")

set(TASK_ACTIVE_FOREGROUND "#ffffff" )
set(TASK_ACTIVE_BACKGROUND "#484741" )
set(TASK_BACKGROUND "#484741" )
set(TASK_FOREGROUND "#ffffff")

set(TRAY_FOREGROUND "#ffffff")
set(TRAY_BACKGROUND "#484741" )
set(TRAY_OPACITY "0.75")

set(TRAY_BUTTON_FOREGROUND "#ffffff")
set(TRAY_BUTTON_BACKGROUND "#484741" )

set(PAGER_OUTLINE "#000000" )
set(PAGER_FOREGROUND "#808080" )
set(PAGER_BACKGROUND "#383838" )
set(PAGER_ACTIVE_FOREGROUND "#ffffff")
set(PAGER_ACTIVE_BACKGROUND "#E45C2D")

set(MENU_FOREGROUND "#ffffff")
set(MENU_BACKGROUND "#383838" )
set(MENU_ACTIVE_FOREGROUND "#ffffff")
set(MENU_ACTIVE_BACKGROUND "#E45C2D")
set(MENU_OPACITY "0.85")

set(WINDOW_ACTIVE_FOREGROUND "#ffffff")
set(WINDOW_ACTIVE_BACKGROUND "#5A584F:#484741")
set(WINDOW_ACTIVE_OUTLINE "#484741")
set(WINDOW_ACTIVE_OPACITY "1.0")
set(WINDOW_FOREGROUND "#ffffff")
set(WINDOW_BACKGROUND "#5A584F:#484741")
set(WINDOW_OUTLINE "#000000")
set(WINDOW_OPACITY "0.7")

set(POPUP_OUTLINE "#000000")
set(POPUP_FOREGROUND "#ffffff")
set(POPUP_BACKGROUND "#484741")

## this stays the same for all files
set(CURRENTTHEME "../${THIS_THEME}/${THIS_THEME}")
set(THEME_230 "../2.3.0/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-2.3.2+themes.in ${THEME_230})
configure_file(../all-new-themes.in ${CURRENTTHEME})
### SETUP OLD THEME NAMES
set(OLD_THEME "../old/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-old-themes.in ${OLD_THEME})
