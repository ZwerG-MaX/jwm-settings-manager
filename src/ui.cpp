
#include "../include/ui.h"
//These functions simply call the UI
UI::UI(){
}
UI::~UI(){
    exit(0);
}
//main window
int UI::showSettings(){
#ifdef DEBUG_TRACK
    std::cerr<<"Settings UI activated"<<std::endl;
#endif // DEBUG
    SettingsUI uiSettings;
    uiSettings.make_window()->xclass("jwm-settings-manager");
    uiSettings.make_window()->show();
return Fl::run();
}

//panel
int UI::showPanel(){
#ifdef DEBUG_TRACK
    std::cerr<<"Panel UI activated"<<std::endl;
#endif // DEBUG
    PanelUI uiPanel;
    uiPanel.make_window()->xclass("jsm-panel");
    uiPanel.make_window()->show();
return Fl::run();
}
//clock
int UI::showClock(){
#ifdef DEBUG_TRACK
    std::cerr<<"Clock UI activated"<<std::endl;
#endif // DEBUG
    PanelUI uiPanel;
    uiPanel.make_window()->xclass("jsm-panel");
    uiPanel.make_window()->show();
    uiPanel.config_clock_window()->show();
return Fl::run();
}
//desktop
int UI::showDesktop(){
#ifdef DEBUG_TRACK
    std::cerr<<"Desktop UI activated"<<std::endl;
#endif // DEBUG
    DesktopUI uiDesktop;
    uiDesktop.make_window()->xclass("jsm-desktop");
    uiDesktop.make_window()->show();
return Fl::run();
}

//windows
int UI::showWindow(){
#ifdef DEBUG_TRACK
    std::cerr<<"Window UI activated"<<std::endl;
#endif // DEBUG
    WindowUI uiWindow;
    uiWindow.make_window()->xclass("jsm-windows");
    uiWindow.make_window()->show();
    return Fl::run();
}

//Autostart
int UI::showAutostart(){
#ifdef DEBUG_TRACK
    std::cerr<<"Autostart UI activated"<<std::endl;
#endif // DEBUG
    AutostartUI uiAutostart;
    uiAutostart.make_window()->xclass("jsm-autostart");
    uiAutostart.make_window()->show();
return Fl::run();
}

//fonts
int UI::showFonts(){
#ifdef DEBUG_TRACK
    std::cerr<<"Font UI activated"<<std::endl;
#endif // DEBUG
    FontUI uiFonts;
    uiFonts.make_window()->xclass("jsm-fonts");
    uiFonts.make_window()->show();
return Fl::run();
}

//keyboard
int UI::showKeyboard(){
#ifdef DEBUG_TRACK
    std::cerr<<"Keyboard UI activated"<<std::endl;
#endif // DEBUG
    KeyboardUI uiKeyboard;
    uiKeyboard.make_window()->xclass("jsm-keyboard");
    uiKeyboard.make_window()->show();
return Fl::run();
}

//Themes
int UI::showThemes(){
#ifdef DEBUG_TRACK
    std::cerr<<"Themes UI activated"<<std::endl;
#endif // DEBUG
    ThemesUI uiThemes;
    uiThemes.make_window()->xclass("jsm-theme");
    uiThemes.make_window()->show();
return Fl::run();
}

//icons
int UI::showIcons(){
#ifdef DEBUG_TRACK
    std::cerr<<"Icons UI activated"<<std::endl;
#endif // DEBUG
    IconsUI uiIcons;
    uiIcons.make_window()->xclass("jsm-icons");
    uiIcons.make_window()->show();
return Fl::run();
}

//mouse
int UI::showMouse(){
#ifdef DEBUG_TRACK
    std::cerr<<"Mouse UI activated"<<std::endl;
#endif // DEBUG
    MouseUI uiMouse;
    uiMouse.make_window()->xclass("jsm-mouse");
    uiMouse.make_window()->show();
return Fl::run();
}
//menu
int UI::showMenu(){
#ifdef DEBUG_TRACK
    std::cerr<<"Menu UI activated"<<std::endl;
#endif // DEBUG
    MenuUI Menu;
    Menu.make_window()->xclass("jsm-panel");
    Menu.make_window()->show();
return Fl::run();
}
//Shortcuts
int UI::showShortcuts(){
#ifdef DEBUG_TRACK
    std::cerr<<"Shortcuts UI activated"<<std::endl;
#endif // DEBUG
    PanelUI uiPanel;
    uiPanel.make_window()->xclass("jsm-panel");
    uiPanel.make_window()->show();
    uiPanel.config_clock_window()->show();
return Fl::run();
}


