#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
//FLTK stuff
#include "../fltk/jwm-settings.h"
#include "../fltk/jwm-shutdown.h"
#include "tinyxml2.h"
//#include <X11/xpm.h>
//#include <FL/x.H>
class UI {
    public:
    int jwmShutdown();
    int showPanel();
    int showDesktop();
    int showThemes();
    int showWindow();
    int showIcons();
    int showFonts();
    int showKeyboard();
    int showMouse();
    int showAutostart();
    int showSettings();
    //char* Get_Fl_Icon(char const** pIcon);
    UI();
    virtual ~UI();
};
#endif
