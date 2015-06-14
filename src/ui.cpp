
#include "../include/ui.h"
//#include "../data/icons/jwm-settings-manager.xpm"
//These functions simply call the UI
UI::UI(){
}
UI::~UI(){
    exit(0);
}
//main window
int UI::showSettings(){
    SettingsUI uiSettings;
   /* static Pixmap p;
    Pixmap mask;
    XpmCreatePixmapFromData(fl_display, DefaultRootWindow(fl_display), (char **)jsm,&p,&mask,0);
    uiSettings.settings_window->icon((char *)p);
    */
    //uiSettings.make_window()->icon(Get_Fl_Icon(jsm));
    //fl_open_display();
    //Pixmap p = XCreateBitmapFromData(fl_display, DefaultRootWindow(fl_display), (char *)jsm,48,48);
    //uiSettings.settings_window->icon((char *)p);
    uiSettings.make_window()->xclass("jwm-settings-manager");
    uiSettings.make_window()->show();
return Fl::run();
}

//panel
int UI::showPanel(){
    PanelUI uiPanel;
    uiPanel.make_window()->xclass("jsm-panel");
    uiPanel.make_window()->show();
return Fl::run();
}
//clock
int UI::showClock(){
    PanelUI uiPanel;
    uiPanel.make_window()->xclass("jsm-panel");
    uiPanel.make_window()->show();
    uiPanel.config_clock_window()->show();
return Fl::run();
}
//desktop
int UI::showDesktop(){
    DesktopUI uiDesktop;
    uiDesktop.make_window()->xclass("jsm-desktop");
    uiDesktop.make_window()->show();
return Fl::run();
}

//windows
int UI::showWindow(){
    WindowUI uiWindow;
    uiWindow.make_window()->xclass("jsm-windows");
    uiWindow.make_window()->show();
    return Fl::run();
}

//Autostart
int UI::showAutostart(){
    AutostartUI uiAutostart;
    uiAutostart.make_window()->xclass("jsm-autostart");
    uiAutostart.make_window()->show();
return Fl::run();
}

//fonts
int UI::showFonts(){
    FontUI uiFonts;
    uiFonts.make_window()->xclass("jsm-fonts");
    uiFonts.make_window()->show();
return Fl::run();
}

//keyboard
int UI::showKeyboard(){
    KeyboardUI uiKeyboard;
    uiKeyboard.make_window()->xclass("jsm-keyboard");
    uiKeyboard.make_window()->show();
return Fl::run();
}

//Themes
int UI::showThemes(){
    ThemesUI uiThemes;
    uiThemes.make_window()->xclass("jsm-theme");
    uiThemes.make_window()->show();
return Fl::run();
}

//icons
int UI::showIcons(){
    IconsUI uiIcons;
    uiIcons.make_window()->xclass("jsm-icons");
    uiIcons.make_window()->show();
return Fl::run();
}

//mouse
int UI::showMouse(){
    MouseUI uiMouse;
    uiMouse.make_window()->xclass("jsm-mouse");
    uiMouse.make_window()->show();
return Fl::run();
}
//mouse
int UI::showMenu(){
    MenuUI Menu;
    Menu.make_window()->xclass("jsm-panel");
    Menu.make_window()->show();
return Fl::run();
}
#if 0
char* UI::Get_Fl_Icon(const char** pIcon){
    /* Set icon for Linux:
     * This function must be initialised once by assigning an icon with parameter pIcon.
     * For sequential setting of icon to subwindows, this function can be called several
     * times without assigning an icon every time.
     *
     * Code from Vincent on FLTK forums 2015 Feb 10
     */
     std::cout<< "in the icon code"<<std::endl;

    Pixmap p=XCreateBitmapFromData(fl_display, DefaultRootWindow(fl_display),(char*) pIcon, 48, 48);
    return (char*) p;
}
#endif
