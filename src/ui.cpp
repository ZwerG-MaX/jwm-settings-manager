
#include "../include/ui.h"
//These functions simply call the UI

//shutdown
int UI::jwmShutdown(){
    shutdown shut;
    shut.make_window()->show();
    return Fl::run();
}

//main window
int UI::showSettings(){
    SettingsUI uiSettings;
    uiSettings.make_window()->show();
return Fl::run();
}

//panel
int UI::showPanel(){
    PanelUI uiPanel;
    uiPanel.make_window()->show();
return Fl::run();
}

//desktop
int UI::showDesktop(){
    DesktopUI uiDesktop;
    uiDesktop.make_window()->show();
return Fl::run();
}

//windows
int UI::showWindow(){
    WindowUI uiWindow;
    uiWindow.make_window()->show();
    return Fl::run();
}

//Autostart
int UI::showAutostart(){
    AutostartUI uiAutostart;
    uiAutostart.make_window()->show();
return Fl::run();
}

//fonts
int UI::showFonts(){
    FontUI uiFonts;
    uiFonts.make_window()->show();
return Fl::run();
}

//keyboard
int UI::showKeyboard(){
    KeyboardUI uiKeyboard;
    uiKeyboard.make_window()->show();
return Fl::run();
}

//Themes
int UI::showThemes(){
    ThemesUI uiThemes;
    uiThemes.make_window()->show();
return Fl::run();
}

//icons
int UI::showIcons(){
    IconsUI uiIcons;
    uiIcons.make_window()->show();
return Fl::run();
}

//mouse
int UI::showMouse(){
    MouseUI uiMouse;
    uiMouse.make_window()->show();
return Fl::run();
}

