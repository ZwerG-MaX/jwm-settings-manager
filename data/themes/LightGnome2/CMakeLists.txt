## Variables in the configure (*.in) files
#####################################################################################
set(THIS_THEME "LightGnome2")
#####################################################################################
set(TRAY "${DEFAULT_TRAY}")
set (OLD_TRAY "${OLD_DEFAULT_TRAY}")
set(MENUS_LIST "${REGULAR_MENUS_LIST}")

set(TASK_ACTIVE_FOREGROUND "#000000" )
set(TASK_ACTIVE_BACKGROUND "#C2C2BE" )
set(TASK_BACKGROUND "#E2E2DE" )
set(TASK_FOREGROUND "#BFBFBF")

set(TRAY_FOREGROUND "#000000")
set(TRAY_BACKGROUND "#E2E2DE" )
set(TRAY_OPACITY "0.75")

set(TRAY_BUTTON_FOREGROUND "#000000")
set(TRAY_BUTTON_BACKGROUND "#E2E2DE" )

set(PAGER_OUTLINE "#000000" )
set(PAGER_FOREGROUND "#ffffff" )
set(PAGER_BACKGROUND "#353535" )
set(PAGER_ACTIVE_FOREGROUND "#ffffff")
set(PAGER_ACTIVE_BACKGROUND "#406477")

set(MENU_FOREGROUND "#000000")
set(MENU_BACKGROUND "#E2E2DE" )
set(MENU_ACTIVE_FOREGROUND "#000000")
set(MENU_ACTIVE_BACKGROUND "#406477")
set(MENU_OPACITY "0.85")

set(WINDOW_ACTIVE_FOREGROUND "#000000")
set(WINDOW_ACTIVE_BACKGROUND "#E2E2DE:#CCCCCC")
set(WINDOW_ACTIVE_OUTLINE "#989898")
set(WINDOW_ACTIVE_OPACITY "1.0")
set(WINDOW_FOREGROUND "#2E2E2E")
set(WINDOW_BACKGROUND "#E2E2DE:#979797")
set(WINDOW_OUTLINE "#353535")
set(WINDOW_OPACITY "0.7")

set(POPUP_OUTLINE "#000000")
set(POPUP_FOREGROUND "#000000")
set(POPUP_BACKGROUND "#353535")

## this stays the same for all files
set(CURRENTTHEME "../${THIS_THEME}/${THIS_THEME}")
set(THEME_230 "../2.3.0/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-2.3.2+themes.in ${THEME_230})
configure_file(../all-new-themes.in ${CURRENTTHEME})
### SETUP OLD THEME NAMES
set(OLD_THEME "../old/${THIS_THEME}/${THIS_THEME}")
configure_file(../all-old-themes.in ${OLD_THEME})
