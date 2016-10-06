## Variables in the configure (*.in) files
#####################################################################################
set(THIS_THEME "DarkGnome2")
#####################################################################################
set(TRAY "${DEFAULT_TRAY}")
set (OLD_TRAY "${OLD_DEFAULT_TRAY}")
set(MENUS_LIST "${REGULAR_MENUS_LIST}")

set(TASK_ACTIVE_FOREGROUND "#ffffff" )
set(TASK_ACTIVE_BACKGROUND "#A5A5A5" )
set(TASK_BACKGROUND "#595959" )
set(TASK_FOREGROUND "#BFBFBF")

set(TRAY_FOREGROUND "#ffffff")
set(TRAY_BACKGROUND "#464646" )
set(TRAY_OPACITY "0.75")

set(TRAY_BUTTON_FOREGROUND "#ffffff")
set(TRAY_BUTTON_BACKGROUND "#464646" )

set(PAGER_OUTLINE "#000000" )
set(PAGER_FOREGROUND "#ffffff" )
set(PAGER_BACKGROUND "#58564D" )
set(PAGER_ACTIVE_FOREGROUND "#ffffff")
set(PAGER_ACTIVE_BACKGROUND "#406477")

set(MENU_FOREGROUND "#ffffff")
set(MENU_BACKGROUND "#58564D" )
set(MENU_ACTIVE_FOREGROUND "#ffffff")
set(MENU_ACTIVE_BACKGROUND "#406477")
set(MENU_OPACITY "0.85")

set(WINDOW_ACTIVE_FOREGROUND "#ffffff")
set(WINDOW_ACTIVE_BACKGROUND "#58564D:#383838")
set(WINDOW_ACTIVE_OUTLINE "#353535")
set(WINDOW_ACTIVE_OPACITY "1.0")
set(WINDOW_FOREGROUND "#A1A1A1")
set(WINDOW_BACKGROUND "#58564D:#46443F")
set(WINDOW_OUTLINE "#353535")
set(WINDOW_OPACITY "0.7")

set(POPUP_OUTLINE "#000000")
set(POPUP_FOREGROUND "#ffffff")
set(POPUP_BACKGROUND "#464646")

## this stays the same for all files
set(CURRENTTHEME "../${THIS_THEME}/${THIS_THEME}")
set(THEME_230 "../2.3.0/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-2.3.2+themes.in ${THEME_230})
configure_file(../all-new-themes.in ${CURRENTTHEME})
### SETUP OLD THEME NAMES
set(OLD_THEME "../old/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-old-themes.in ${OLD_THEME})
