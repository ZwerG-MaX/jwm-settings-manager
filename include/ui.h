#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
//FLTK stuff
#include "../fltk/jwm-settings.h"
#include "../fltk/jwm-menu.h"
#include "tinyxml2.h"
//#include <X11/xpm.h>
//#include <FL/x.H>
class UI {
    public:
    int showPanel();
    int showClock();
    int showDesktop();
    int showThemes();
    int showWindow();
    int showIcons();
    int showFonts();
    int showKeyboard();
    int showMouse();
    int showMenu();
    int showAutostart();
    int showSettings();
    //char* Get_Fl_Icon(char const** pIcon);
    UI();
    virtual ~UI();
};
#endif
