## Variables in the configure (*.in) files
#####################################################################################
set(THIS_THEME "Numix")
#####################################################################################
set(TRAY "${DEFAULT_TRAY}")
set (OLD_TRAY "${OLD_DEFAULT_TRAY}")
set(MENUS_LIST "${REGULAR_MENUS_LIST}")
set(CORNER "0")
set(BUTTONS "<ButtonClose>/usr/share/themes/Numix/unity/close_focused_prelight.png</ButtonClose>
    <ButtonMax>/usr/share/themes/Numix/unity/maximize_focused_normal.png</ButtonMax>
    <ButtonMaxActive>/usr/share/themes/Numix/unity/unmaximize.png</ButtonMaxActive>
    <ButtonMin>/usr/share/themes/Numix/unity/minimize.png</ButtonMin>")
set(TASK_ACTIVE_FOREGROUND "#f9f9f9" )
set(TASK_ACTIVE_BACKGROUND "#d64937" )
set(TASK_BACKGROUND "#2d2d2d" )
set(TASK_FOREGROUND "#dcdcdc")

set(TRAY_FOREGROUND "#dcdcdc")
set(TRAY_BACKGROUND "#2d2d2d" )
set(TRAY_OPACITY "1.0")

set(TRAY_BUTTON_FOREGROUND "#dcdcdc")
set(TRAY_BUTTON_BACKGROUND "#2d2d2d" )

set(PAGER_OUTLINE "#000000" )
set(PAGER_FOREGROUND "#2d2d2d" )
set(PAGER_BACKGROUND "#888888" )
set(PAGER_ACTIVE_FOREGROUND "#f9f9f9")
set(PAGER_ACTIVE_BACKGROUND "#d64937")

set(MENU_FOREGROUND "#dcdcdc")
set(MENU_BACKGROUND "#2d2d2d" )
set(MENU_ACTIVE_FOREGROUND "#f9f9f9")
set(MENU_ACTIVE_BACKGROUND "#d64937")
set(MENU_OPACITY "1.0")

set(W_HEIGHT "30")
set(WINDOW_ACTIVE_FOREGROUND "#dcdcdc")
set(WINDOW_ACTIVE_BACKGROUND "#2d2d2d")
set(WINDOW_ACTIVE_OUTLINE "#484848")
set(WINDOW_ACTIVE_OPACITY "1.0")
set(WINDOW_FOREGROUND "#888888")
set(WINDOW_BACKGROUND "#2d2d2d")
set(WINDOW_OUTLINE "#393939")
set(WINDOW_OPACITY "1.0")

set(POPUP_OUTLINE "#484848")
set(POPUP_FOREGROUND "#2d2d2d")
set(POPUP_BACKGROUND "#2d2d2d")

## this stays the same for all files
set(CURRENTTHEME "../${THIS_THEME}/${THIS_THEME}")
set(THEME_230 "../2.3.0/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-2.3.2+themes.in ${THEME_230})
configure_file(../all-new-themes.in ${CURRENTTHEME})
### SETUP OLD THEME NAMES
set(OLD_THEME "../old/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-old-themes.in ${OLD_THEME})
